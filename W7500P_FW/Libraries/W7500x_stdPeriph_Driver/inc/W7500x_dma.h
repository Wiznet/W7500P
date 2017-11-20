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
  * @file    W7500x_stdPeriph_Driver/inc/W7500x_dma.h
  * @author  IOP Team
  * @version V1.0.0
  * @date    01-May-2015
  * @brief   This file contains all the functions prototypes for the DMA 
  *          firmware library.
  ******************************************************************************
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __W7500X_DMA_H
#define __W7500X_DMA_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "W7500x.h"

/*------------- DMA --------------------------------------*/
/** @addtogroup W7500 DMA 
  @{
*/
typedef struct
{
  __I    uint32_t  DMA_STATUS;           /*!< Offset: 0x000 DMA status Register (R/W) */
  __O    uint32_t  DMA_CFG;              /*!< Offset: 0x004 DMA configuration Register ( /W) */
  __IO   uint32_t  CTRL_BASE_PTR;        /*!< Offset: 0x008 Channel Control Data Base Pointer Register  (R/W) */
  __I    uint32_t  ALT_CTRL_BASE_PTR;    /*!< Offset: 0x00C Channel Alternate Control Data Base Pointer Register  (R/ ) */
  __I    uint32_t  DMA_WAITONREQ_STATUS; /*!< Offset: 0x010 Channel Wait On Request Status Register  (R/ ) */
  __O    uint32_t  CHNL_SW_REQUEST;      /*!< Offset: 0x014 Channel Software Request Register  ( /W) */
  __IO   uint32_t  CHNL_USEBURST_SET;    /*!< Offset: 0x018 Channel UseBurst Set Register  (R/W) */
  __O    uint32_t  CHNL_USEBURST_CLR;    /*!< Offset: 0x01C Channel UseBurst Clear Register  ( /W) */
  __IO   uint32_t  CHNL_REQ_MASK_SET;    /*!< Offset: 0x020 Channel Request Mask Set Register  (R/W) */
  __O    uint32_t  CHNL_REQ_MASK_CLR;    /*!< Offset: 0x024 Channel Request Mask Clear Register  ( /W) */
  __IO   uint32_t  CHNL_ENABLE_SET;      /*!< Offset: 0x028 Channel Enable Set Register  (R/W) */
  __O    uint32_t  CHNL_ENABLE_CLR;      /*!< Offset: 0x02C Channel Enable Clear Register  ( /W) */
  __IO   uint32_t  CHNL_PRI_ALT_SET;     /*!< Offset: 0x030 Channel Primary-Alterante Set Register  (R/W) */
  __O    uint32_t  CHNL_PRI_ALT_CLR;     /*!< Offset: 0x034 Channel Primary-Alterante Clear Register  ( /W) */
  __IO   uint32_t  CHNL_PRIORITY_SET;    /*!< Offset: 0x038 Channel Priority Set Register  (R/W) */
  __O    uint32_t  CHNL_PRIORITY_CLR;    /*!< Offset: 0x03C Channel Priority Clear Register  ( /W) */
         uint32_t  RESERVED0[3];
  __IO   uint32_t  ERR_CLR;              /*!< Offset: 0x04C Bus Error Clear Register  (R/W) */

} DMA_TypeDef;

#define DMA_CHNL_BITS 0

#define DMA_STATUS_MSTREN_Pos          0                                              /*!<  DMA STATUS: MSTREN Position */
#define DMA_STATUS_MSTREN_Msk          (0x00000001ul << DMA_STATUS_MSTREN_Pos)        /*!<  DMA STATUS: MSTREN Mask */

#define DMA_STATUS_STATE_Pos           0                                              /*!<  DMA STATUS: STATE Position */
#define DMA_STATUS_STATE_Msk           (0x0000000Ful << DMA_STATUS_STATE_Pos)         /*!<  DMA STATUS: STATE Mask */

#define DMA_STATUS_CHNLS_MINUS1_Pos    0                                              /*!<  DMA STATUS: CHNLS_MINUS1 Position */
#define DMA_STATUS_CHNLS_MINUS1_Msk    (0x0000001Ful << DMA_STATUS_CHNLS_MINUS1_Pos)  /*!<  DMA STATUS: CHNLS_MINUS1 Mask */

#define DMA_STATUS_TEST_STATUS_Pos     0                                              /*!<  DMA STATUS: TEST_STATUS Position */
#define DMA_STATUS_TEST_STATUS_Msk     (0x00000001ul << DMA_STATUS_TEST_STATUS_Pos)   /*!<  DMA STATUS: TEST_STATUS Mask */

#define DMA_CFG_MSTREN_Pos             0                                              /*!<  DMA CFG: MSTREN Position */
#define DMA_CFG_MSTREN_Msk             (0x00000001ul << DMA_CFG_MSTREN_Pos)           /*!<  DMA CFG: MSTREN Mask */

#define DMA_CFG_CPCCACHE_Pos           2                                              /*!<  DMA CFG: CPCCACHE Position */
#define DMA_CFG_CPCCACHE_Msk           (0x00000001ul << DMA_CFG_CPCCACHE_Pos)         /*!<  DMA CFG: CPCCACHE Mask */

#define DMA_CFG_CPCBUF_Pos             1                                              /*!<  DMA CFG: CPCBUF Position */
#define DMA_CFG_CPCBUF_Msk             (0x00000001ul << DMA_CFG_CPCBUF_Pos)           /*!<  DMA CFG: CPCBUF Mask */

#define DMA_CFG_CPCPRIV_Pos            0                                              /*!<  DMA CFG: CPCPRIV Position */
#define DMA_CFG_CPCPRIV_Msk            (0x00000001ul << DMA_CFG_CPCPRIV_Pos)          /*!<  DMA CFG: CPCPRIV Mask */

#define CTRL_BASE_PTR_Pos              PL230_DMA_CHNL_BITS + 5                        /*!<  STATUS: BASE_PTR Position */
#define CTRL_BASE_PTR_Msk              (0x0FFFFFFFul << CTRL_BASE_PTR_Pos)            /*!<  STATUS: BASE_PTR Mask */

#define ALT_CTRL_BASE_PTR_Pos          0                                              /*!<  STATUS: MSTREN Position */
#define ALT_CTRL_BASE_PTR_Msk          (0xFFFFFFFFul << ALT_CTRL_BASE_PTR_Pos)        /*!<  STATUS: MSTREN Mask */

#define DMA_WAITONREQ_STATUS_Pos       0                                              /*!<  DMA_WAITONREQ_STATUS: DMA_WAITONREQ_STATUS Position */
#define DMA_WAITONREQ_STATUS_Msk       (0xFFFFFFFFul << DMA_WAITONREQ_STATUS_Pos)     /*!<  DMA_WAITONREQ_STATUS: DMA_WAITONREQ_STATUS Mask */

#define CHNL_SW_REQUEST_Pos            0                                              /*!<  CHNL_SW_REQUEST: CHNL_SW_REQUEST Position */
#define CHNL_SW_REQUEST_Msk            (0xFFFFFFFFul << CHNL_SW_REQUEST_Pos)          /*!<  CHNL_SW_REQUEST: CHNL_SW_REQUEST Mask */

#define CHNL_USEBURST_SET_Pos          0                                              /*!<  CHNL_USEBURST: SET Position */
#define CHNL_USEBURST_SET_Msk          (0xFFFFFFFFul << CHNL_USEBURST_SET_Pos)        /*!<  CHNL_USEBURST: SET Mask */

#define CHNL_USEBURST_CLR_Pos          0                                              /*!<  CHNL_USEBURST: CLR Position */
#define CHNL_USEBURST_CLR_Msk          (0xFFFFFFFFul << CHNL_USEBURST_CLR_Pos)        /*!<  CHNL_USEBURST: CLR Mask */

#define CHNL_REQ_MASK_SET_Pos          0                                              /*!<  CHNL_REQ_MASK: SET Position */
#define CHNL_REQ_MASK_SET_Msk          (0xFFFFFFFFul << CHNL_REQ_MASK_SET_Pos)        /*!<  CHNL_REQ_MASK: SET Mask */

#define CHNL_REQ_MASK_CLR_Pos          0                                              /*!<  CHNL_REQ_MASK: CLR Position */
#define CHNL_REQ_MASK_CLR_Msk          (0xFFFFFFFFul << CHNL_REQ_MASK_CLR_Pos)        /*!<  CHNL_REQ_MASK: CLR Mask */

#define CHNL_ENABLE_SET_Pos            0                                              /*!<  CHNL_ENABLE: SET Position */
#define CHNL_ENABLE_SET_Msk            (0xFFFFFFFFul << CHNL_ENABLE_SET_Pos)          /*!<  CHNL_ENABLE: SET Mask */

#define CHNL_ENABLE_CLR_Pos            0                                              /*!<  CHNL_ENABLE: CLR Position */
#define CHNL_ENABLE_CLR_Msk            (0xFFFFFFFFul << CHNL_ENABLE_CLR_Pos)          /*!<  CHNL_ENABLE: CLR Mask */

#define CHNL_PRI_ALT_SET_Pos           0                                              /*!<  CHNL_PRI_ALT: SET Position */
#define CHNL_PRI_ALT_SET_Msk           (0xFFFFFFFFul << CHNL_PRI_ALT_SET_Pos)         /*!<  CHNL_PRI_ALT: SET Mask */

#define CHNL_PRI_ALT_CLR_Pos           0                                              /*!<  CHNL_PRI_ALT: CLR Position */
#define CHNL_PRI_ALT_CLR_Msk           (0xFFFFFFFFul << CHNL_PRI_ALT_CLR_Pos)         /*!<  CHNL_PRI_ALT: CLR Mask */

#define CHNL_PRIORITY_SET_Pos          0                                              /*!<  CHNL_PRIORITY: SET Position */
#define CHNL_PRIORITY_SET_Msk          (0xFFFFFFFFul << CHNL_PRIORITY_SET_Pos)        /*!<  CHNL_PRIORITY: SET Mask */

#define CHNL_PRIORITY_CLR_Pos          0                                              /*!<  CHNL_PRIORITY: CLR Position */
#define CHNL_PRIORITY_CLR_Msk          (0xFFFFFFFFul << CHNL_PRIORITY_CLR_Pos)        /*!<  CHNL_PRIORITY: CLR Mask */

#define ERR_CLR_Pos                    0                                              /*!<  ERR: CLR Position */
#define ERR_CLR_Msk                    (0x00000001ul << ERR_CLR_Pos)                  /*!<  ERR: CLR Mask */


/*@}*/ /* end of group DMA */


/******************************************************************************/
/*                         Peripheral declaration                             */
/******************************************************************************/

/** @addtogroup CMSDK_PeripheralDecl CMSDK Peripheral Declaration
  @{
*/
#define DMA_BASE        (0x41004000ul)
#define DMA             ((DMA_TypeDef  *)DMA_BASE) 
/*@}*/ /* end of group CMSDK_PeripheralDecl */


/* Maximum to 6 DMA channel */
#define MAX_NUM_OF_DMA_CHANNELS   6
#define CHANNEL_NUM			DMA_CHANNEL_MAX

/* SRAM in example system is 64K bytes */
#define RAM_ADDRESS_MAX       0x2000FFFF

typedef struct /* 4 words */
{
  volatile unsigned long SrcEndPointer;
  volatile unsigned long DestEndPointer;
  volatile unsigned long Control;
  volatile unsigned long unused;
} dma_channel_data;

typedef enum{
	DMA_SSP0  =0,
	DMA_SSP1  =1,
	DMA_UART0 =2,
	DMA_UART1 =3,
	DMA_M2M4  =4,
	DMA_M2M5  =5,
}dma_channel;


typedef enum{
	byte = 0,
	hword = 1,
	word = 2,
	rsv = 3,
}dma_size;

typedef enum{
	M2M	= 0,
	M2P = 1,
	P2M = 2,
	P2P	= 3,
}dma_type;


typedef struct /* 8 words per channel */
{ /* only one channel in the example uDMA setup */
  volatile dma_channel_data Primary[MAX_NUM_OF_DMA_CHANNELS];
  volatile dma_channel_data Alternate[MAX_NUM_OF_DMA_CHANNELS];
} dma_data_structure;



void dma_memory_copy (uint32_t chnl_num, unsigned int src, unsigned int dest, unsigned int size, unsigned int num);
void dma_m2p_copy (uint32_t chnl_num, unsigned int src, unsigned int dest, unsigned int size, unsigned int num);
void dma_data_struct_init(void);
void dma_init(void);

//void dma_memory_copy_rx (unsigned int src, unsigned int dest, unsigned int size, unsigned int num);
//void dma_init_rx(void);
//int  dma_detect(void);
//int  ID_Check(const unsigned int id_array[], unsigned int offset);


//for test
#define EXPECTED_BE             0


#ifdef __cplusplus
    }
#endif
#endif //__W7500X_DMA_H
