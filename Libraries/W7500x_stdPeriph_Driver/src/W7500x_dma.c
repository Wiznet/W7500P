/*******************************************************************************************************************************************************
 * Copyright ¨Ï 2016 <WIZnet Co.,Ltd.> 
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the ¡°Software¡±), 
 * to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, 
 * and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

 * THE SOFTWARE IS PROVIDED ¡°AS IS¡±, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. 
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, 
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*********************************************************************************************************************************************************/
/**
  ******************************************************************************
  * @file    W7500x_stdPeriph_Driver/src/W7500x_dma.c    
  * @author  IOP Team
  * @version v1.0.0
  * @date    01-May-2015
  * @brief   This file contains all the functions prototypes for the dma 
  *          firmware library.
  ******************************************************************************
  *
  ******************************************************************************
  */

/*include ------------------------------------------------*/
#include <stdio.h>
#include "W7500x_dma.h"

#define HW32_REG(ADDRESS)  (*((volatile unsigned long  *)(ADDRESS)))
dma_data_structure *dma_data;

/* --------------------------------------------------------------- */
/*  Initialize DMA data structure                                  */
/* --------------------------------------------------------------- */
void dma_data_struct_init(void)
{
  int          i;   /* loop counter */
  unsigned int ptr;

  int          ch_num;         /* number of channels */
  unsigned int blksize;        /* Size of DMA data structure in bytes */
  unsigned int blkmask;        /* address mask */


  ch_num  = (((DMA->DMA_STATUS) >> 16) & 0x7)+1; // chnls_minus1 = 5 (101b)
  blksize = ch_num * 32;
  if      (ch_num > 4)  blkmask = 0x0FF; /*  5 to 8 */
  else if (ch_num > 2)  blkmask = 0x07F; /*  3 to 4 */
  else if (ch_num > 1)  blkmask = 0x07F; /*       2 */
  else                  blkmask = 0x03F; /*       1 */

  /* Create DMA data structure in RAM after stack
  In the linker script, a 1KB memory stack above stack is reserved
  so we can use this space for putting the DMA data structure.
  */
  ptr = HW32_REG(0);                     /* Read Top of Stack */

  /* the DMA data structure must be aligned to the size of the data structure */
  if ((ptr & blkmask) != 0x0)
    ptr = (ptr + blksize) & ~blkmask;

  if ((ptr + blksize) > (RAM_ADDRESS_MAX + 1)) 
  {
    printf("ERROR : Not enough RAM space for DMA data structure.");
  }

  /* Set pointer to the reserved space */
  dma_data = (dma_data_structure *) ptr;
  ptr = (unsigned int) &dma_data->Primary->SrcEndPointer;

  printf ("dma structure block address = %x\r\n", ptr);

  for (i=0; i<ch_num; i++) {
    dma_data->Primary[i].SrcEndPointer  = 0;
    dma_data->Primary[i].DestEndPointer = 0;
    dma_data->Primary[i].Control        = 0;
    dma_data->Alternate[i].SrcEndPointer  = 0;
    dma_data->Alternate[i].DestEndPointer = 0;
    dma_data->Alternate[i].Control        = 0;
    }

  return;
}

/* --------------------------------------------------------------- */
/*  Initialize DMA PL230                                           */
/* --------------------------------------------------------------- */
void dma_init(void)
{
    unsigned int current_state;
    printf("Initialize DMA");
    current_state = DMA->DMA_STATUS;
    printf ("- # of channels allowed : %d\r\n",(((current_state) >> 16) & 0x7)+1);

    /* Wait until current DMA complete */
    current_state = (DMA->DMA_STATUS >> 4)  & 0xF;
    if (!((current_state==0) || (current_state==0x8) || (current_state==0x9))) 
    {
        printf ("- wait for DMA IDLE/STALLED/DONE");
        current_state = (DMA->DMA_STATUS >> 4)  & 0xF;
        printf ("- Current status        : %x\n",(((current_state) >> 4)  & 0xF));

    }
    while (!((current_state==0) || (current_state==0x8) || (current_state==0x9)))
    {
        /* Wait if not IDLE/STALLED/DONE */
        current_state = (DMA->DMA_STATUS >> 4)  & 0xF;
        printf ("- Current status        : %x\n",(((current_state) >> 4)  & 0xF));
    }
    DMA->DMA_CFG = 0; /* Disable DMA controller for initialization */
    DMA->CTRL_BASE_PTR = (unsigned int) &dma_data->Primary->SrcEndPointer;
    /* Set DMA data structure address */
    DMA->CHNL_ENABLE_CLR = 0x3F;   /* Disable all channels */
    //DMA->CHNL_ENABLE_SET = (1<<0); /* Enable channel 0 */
    DMA->DMA_CFG = 1;              /* Enable DMA controller */

    return;
}

/* --------------------------------------------------------------- */
/*  DMA memory copy                                                */
/* --------------------------------------------------------------- */
void dma_memory_copy (uint32_t chnl_num, unsigned int src, unsigned int dest, unsigned int size, unsigned int num)
//void dma_M2P_copy (uint32_t chnl_num, unsigned int src, unsigned int dest, unsigned int size, unsigned int num)
{
  
    unsigned long src_end_pointer =  src + ((1<<size)*(num-1));
    unsigned long dst_end_pointer = dest + ((1<<size)*(num-1));
    unsigned long control         = (1<< 30) |  /* dst_inc */
                                    (size << 28) |  /* dst_size */
                                    (size << 26) |  /* src_inc */
                                    (size << 24) |  /* src_size */
                                    (size << 21) |  /* dst_prot_ctrl - HPROT[3:1] */
                                    (size << 18) |  /* src_prot_ctrl - HPROT[3:1] */
                                    (0    << 14) |  /* R_power */
                                    ((num-1)<< 4) | /* n_minus_1 */
                                    (0    <<  3) |  /* next_useburst */
                                    (2   <<  0) ;  /* cycle_ctrl - auto */
                                    //(1    <<  3) |  /* next_useburst */
                                    //(7   <<  0) ;  /* cycle_ctrl - auto */
   
  /* By default the PL230 is little-endian; if the processor is configured
   * big-endian then the configuration data that is written to memory must be
   * byte-swapped before being written.  This is also true if the processor is
   * little-endian and the PL230 is big-endian.
   * Remove the __REV usage if the processor and PL230 are configured with the
   * same endianness
   * */
 #if 0
  dma_data->Alternate[chnl_num].SrcEndPointer  = (EXPECTED_BE) ? __REV(src_end_pointer) : (src_end_pointer);
  dma_data->Alternate[chnl_num].DestEndPointer = (EXPECTED_BE) ? __REV(dst_end_pointer) : (dst_end_pointer);
  dma_data->Alternate[chnl_num].Control        = (EXPECTED_BE) ? __REV(control        ) : (control        );
  /* Debugging printfs: */
  printf ("SrcEndPointer  = %x\r\n", dma_data->Alternate[chnl_num].SrcEndPointer);
  printf ("DestEndPointer = %x\r\n", dma_data->Alternate[chnl_num].DestEndPointer);
  #else
  
  dma_data->Primary[chnl_num].SrcEndPointer  = (EXPECTED_BE) ? __REV(src_end_pointer) : (src_end_pointer);
  dma_data->Primary[chnl_num].DestEndPointer = (EXPECTED_BE) ? __REV(dst_end_pointer) : (dst_end_pointer);
  dma_data->Primary[chnl_num].Control        = (EXPECTED_BE) ? __REV(control        ) : (control        );
/* Debugging printfs: */
  printf ("SrcEndPointer  = %x\r\n", dma_data->Primary[chnl_num].SrcEndPointer);
  printf ("DestEndPointer = %x\r\n", dma_data->Primary[chnl_num].DestEndPointer);
  #endif

#if 1
  DMA->CHNL_ENABLE_SET = (1<<chnl_num); /* Enable channel */
  DMA->CHNL_SW_REQUEST = (1<<chnl_num); /* request channel DMA */
#endif



  return;
}

/* --------------------------------------------------------------- */
/*  DMA memory to periph copy                                                */
/* --------------------------------------------------------------- */
void dma_m2p_copy (uint32_t chnl_num, unsigned int src, unsigned int dest, unsigned int size, unsigned int num)
//void dma_M2P_copy (uint32_t chnl_num, unsigned int src, unsigned int dest, unsigned int size, unsigned int num)
{
  
    unsigned long src_end_pointer =  src + ((1<<size)*(num-1));
    unsigned long dst_end_pointer = dest;
    unsigned long control         = (1<< 30) |  /* dst_inc */
                                    (size << 28) |  /* dst_size */
                                    (size << 26) |  /* src_inc */
                                    (size << 24) |  /* src_size */
                                    (size << 21) |  /* dst_prot_ctrl - HPROT[3:1] */
                                    (size << 18) |  /* src_prot_ctrl - HPROT[3:1] */
                                    (0    << 14) |  /* R_power */
                                    ((num-1)<< 4) | /* n_minus_1 */
                                    (0    <<  3) |  /* next_useburst */
                                    (2   <<  0) ;  /* cycle_ctrl - auto */
                                    //(1    <<  3) |  /* next_useburst */
                                    //(7   <<  0) ;  /* cycle_ctrl - auto */
   
  /* By default the PL230 is little-endian; if the processor is configured
   * big-endian then the configuration data that is written to memory must be
   * byte-swapped before being written.  This is also true if the processor is
   * little-endian and the PL230 is big-endian.
   * Remove the __REV usage if the processor and PL230 are configured with the
   * same endianness
   * */
 #if 0
  dma_data->Alternate[chnl_num].SrcEndPointer  = (EXPECTED_BE) ? __REV(src_end_pointer) : (src_end_pointer);
  dma_data->Alternate[chnl_num].DestEndPointer = (EXPECTED_BE) ? __REV(dst_end_pointer) : (dst_end_pointer);
  dma_data->Alternate[chnl_num].Control        = (EXPECTED_BE) ? __REV(control        ) : (control        );
  /* Debugging printfs: */
  printf ("SrcEndPointer  = %x\r\n", dma_data->Alternate[chnl_num].SrcEndPointer);
  printf ("DestEndPointer = %x\r\n", dma_data->Alternate[chnl_num].DestEndPointer);
  #else
  
  dma_data->Primary[chnl_num].SrcEndPointer  = (EXPECTED_BE) ? __REV(src_end_pointer) : (src_end_pointer);
  dma_data->Primary[chnl_num].DestEndPointer = (EXPECTED_BE) ? __REV(dst_end_pointer) : (dst_end_pointer);
  dma_data->Primary[chnl_num].Control        = (EXPECTED_BE) ? __REV(control        ) : (control        );
/* Debugging printfs: */
  printf ("SrcEndPointer  = %x\r\n", dma_data->Primary[chnl_num].SrcEndPointer);
  printf ("DestEndPointer = %x\r\n", dma_data->Primary[chnl_num].DestEndPointer);
  #endif

#if 1
  DMA->CHNL_ENABLE_SET = (1<<chnl_num); /* Enable channel */
  DMA->CHNL_SW_REQUEST = (1<<chnl_num); /* request channel DMA */
#endif



  return;
}

#if 0
void dma_memory_copy_tx (unsigned int src, unsigned int dest, unsigned int size, unsigned int num)
{
  unsigned long src_end_pointer; 
  unsigned long dst_end_pointer; 
  unsigned long control        ; 
  src_end_pointer =  src + ((1<<size)*(num-1));
  dst_end_pointer = dest + ((1<<size)*(num-1));
  //printf("src_end_pointer: %x, dst_end_pointer:%x\r\n", src_end_pointer, dst_end_pointer);
  control         = (size << 30) |  /* dst_inc */
                    (size << 28) |  /* dst_size */
                    (size << 26) |  /* src_inc */
                    (size << 24) |  /* src_size */
                    (size << 21) |  /* dst_prot_ctrl - HPROT[3:1] */
                    (size << 18) |  /* src_prot_ctrl - HPROT[3:1] */
                    (0    << 14) |  /* R_power */
                    ((num-1)<< 4) | /* n_minus_1 */
                    (0    <<  3) |  /* next_useburst */
                    (2    <<  0) ;  /* cycle_ctrl - auto */
  /* By default the PL230 is little-endian; if the processor is configured
   * big-endian then the configuration data that is written to memory must be
   * byte-swapped before being written.  This is also true if the processor is
   * little-endian and the PL230 is big-endian.
   * Remove the __REV usage if the processor and PL230 are configured with the
   * same endianness
   * */
  dma_data->Primary[ch_num].SrcEndPointer  = (EXPECTED_BE) ? __REV(src_end_pointer) : (src_end_pointer);
  dma_data->Primary[ch_num].DestEndPointer = (EXPECTED_BE) ? __REV(dst_end_pointer) : (dst_end_pointer);
  dma_data->Primary[ch_num].Control        = (EXPECTED_BE) ? __REV(control        ) : (control        );
  /* Debugging printfs: */
  /*printf ("SrcEndPointer  = %x\n", dma_data->Primary->SrcEndPointer);*/
  /*printf ("DestEndPointer = %x\n", dma_data->Primary->DestEndPointer);*/

  DMA->CHNL_ENABLE_SET = (1<<4); /* Enable channel 4 */
  DMA->CHNL_SW_REQUEST = (1<<4); /* request channel 4 DMA */

  return;
}
void dma_init_rx(void)
{
  unsigned int current_state;
  printf("Initialize DMA");
  current_state = DMA->DMA_STATUS;
  printf ("- # of channels allowed : %d\n",(((current_state) >> 16) & 0x1F)+1);
  /* Debugging printfs: */
  /*printf ("- Current status        : %x\n",(((current_state) >> 4)  & 0xF));*/
  /*printf ("- Current master enable : %x\n",(((current_state) >> 0)  & 0x1));*/

  /* Wait until current DMA complete */
  current_state = (DMA->DMA_STATUS >> 4)  & 0xF;
  if (!((current_state==0) || (current_state==0x8) || (current_state==0x9))) {
    printf ("- wait for DMA IDLE/STALLED/DONE");
    current_state = (DMA->DMA_STATUS >> 4)  & 0xF;
    printf ("- Current status        : %x\n",(((current_state) >> 4)  & 0xF));

    }
  while (!((current_state==0) || (current_state==0x8) || (current_state==0x9))){
    /* Wait if not IDLE/STALLED/DONE */
    current_state = (DMA->DMA_STATUS >> 4)  & 0xF;
    printf ("- Current status        : %x\n",(((current_state) >> 4)  & 0xF));
    }
  DMA->DMA_CFG = 0; /* Disable DMA controller for initialization */
  DMA->CTRL_BASE_PTR = (unsigned int) &dma_data->Primary->SrcEndPointer;
                           /* Set DMA data structure address */
  DMA->CHNL_ENABLE_CLR = 0xFFFFFFFF; /* Disable all channels */
  DMA->CHNL_ENABLE_SET = (1<<5); /* Enable channel 0 */
  DMA->DMA_CFG = 1;              /* Enable DMA controller */

  return;
}
void dma_memory_copy_rx (unsigned int src, unsigned int dest, unsigned int size, unsigned int num)
{
  unsigned long src_end_pointer =  src + ((1<<size)*(num-1));
  unsigned long dst_end_pointer = dest + ((1<<size)*(num-1));
  unsigned long control         = (size << 30) |  /* dst_inc */
                                  (size << 28) |  /* dst_size */
                                  (size << 26) |  /* src_inc */
                                  (size << 24) |  /* src_size */
                                  (size << 21) |  /* dst_prot_ctrl - HPROT[3:1] */
                                  (size << 18) |  /* src_prot_ctrl - HPROT[3:1] */
                                  (0    << 14) |  /* R_power */
                                  ((num-1)<< 4) | /* n_minus_1 */
                                  (0    <<  3) |  /* next_useburst */
                                  (2    <<  0) ;  /* cycle_ctrl - auto */
  /* By default the PL230 is little-endian; if the processor is configured
   * big-endian then the configuration data that is written to memory must be
   * byte-swapped before being written.  This is also true if the processor is
   * little-endian and the PL230 is big-endian.
   * Remove the __REV usage if the processor and PL230 are configured with the
   * same endianness
   * */
  dma_data->Primary->SrcEndPointer  = (EXPECTED_BE) ? __REV(src_end_pointer) : (src_end_pointer);
  dma_data->Primary->DestEndPointer = (EXPECTED_BE) ? __REV(dst_end_pointer) : (dst_end_pointer);
  dma_data->Primary->Control        = (EXPECTED_BE) ? __REV(control        ) : (control        );
  /* Debugging printfs: */
  printf ("SrcEndPointer  = %x\n", dma_data->Primary->SrcEndPointer);
  printf ("DestEndPointer = %x\n", dma_data->Primary->DestEndPointer);

  DMA->CHNL_ENABLE_SET = (1<<0); /* Enable channel 0 */
  DMA->CHNL_SW_REQUEST = (1<<0); /* request channel 0 DMA */

  return;
}
#endif
