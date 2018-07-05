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
#include <stdio.h>
#include "W7500x_miim.h"
#ifdef __W7500P__
           // PB_05, PB_12 pull down
           //*(volatile uint32_t *)(0x41003070) = 0x61;
           //*(volatile uint32_t *)(0x41003054) = 0x61;
#endif

#define __DEF_DBG_LEVEL1__


extern void delay(__IO uint32_t nCount);


uint32_t PHY_ADDR_IP101G; //(phy_id())
uint32_t PHY_ADDR;// PHY_ADDR_IP101G

uint32_t link(void)
{
    uint32_t phy_status = mdio_read(GPIOB, PHYREG_STATUS);  
    uint32_t phy_status_link;
    
    phy_status_link = (phy_status>>2)&0x01;
    
    return phy_status_link; 
}

void set_link(SetLink_Type mode)
{
   uint32_t val=0;
   assert_param(IS_SETLINK_TYPE(mode));
   
   if( mode == CNTL_AUTONEGO)
   {    
      val = CNTL_AUTONEGO; 
   }
   else
   {
        val = (mode & (CNTL_SPEED|CNTL_DUPLEX)); 
   }

    mdio_write(GPIOB, PHYREG_CONTROL, val);

}


void mdio_init(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin_MDC, uint16_t GPIO_Pin_MDIO)
{
    /* Set GPIOs for MDIO and MDC */
    GPIO_InitTypeDef GPIO_InitDef;  
	GPIO_StructInit(&GPIO_InitDef); // init the structure	
    GPIO_InitDef.GPIO_Pin = GPIO_Pin_MDC | GPIO_Pin_MDIO;
    GPIO_InitDef.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_Init(GPIOx, &GPIO_InitDef);

    PAD_AFConfig(PAD_PB, GPIO_Pin_MDIO, PAD_AF1);  
    PAD_AFConfig(PAD_PB, GPIO_Pin_MDC, PAD_AF1);  
    
    PHY_ADDR = (phy_id());
}
/* need verify...
void mdio_error_check(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin_MDC, uint16_t GPIO_Pin_MDIO)
{
    mdio_init(GPIOB, MDC, MDIO);
    mdio_write(GPIOx,20,16); //Phy ID read
    //printf("@ 16P_29 : 0x%X\r\n",mdio_read(GPIOB,29));
    if((mdio_read(GPIOx,29) != 0x882) && (mdio_read(GPIOx,29) != 0x782) && (mdio_read(GPIOx,29) != 0x382))
    {
        delay(1000);
        mdio_write(GPIOx,20,1); mdio_write(GPIOx,22,0xA020); // LDO disable
        mdio_write(GPIOx,20,1); mdio_write(GPIOx,22,0x2020); // LDO enalble
        mdio_init(GPIOx, GPIO_Pin_MDC, GPIO_Pin_MDIO);
        while( link() == 0x0) printf(".");
        mdio_write(GPIOx,20,16); mdio_write(GPIOx,29,0x882); // Change PHY id to 0x882
        mdio_init(GPIOx, GPIO_Pin_MDC, GPIO_Pin_MDIO);
    }
    while( link() == 0x0) printf(".");
    printf("PHY is linked. \r\n");  
}*/


void output_MDIO(GPIO_TypeDef* GPIOx, uint32_t val, uint32_t n)
{
    for(val <<= (32-n); n; val<<=1, n--)
    {
        if(val & 0x80000000)
            GPIO_SetBits(GPIOx, MDIO); 
        else
            GPIO_ResetBits(GPIOx, MDIO);

        delay(1);
        GPIO_SetBits(GPIOx, MDC); 
        delay(1);
        GPIO_ResetBits(GPIOx, MDC);
    }
}

uint32_t input_MDIO( GPIO_TypeDef* GPIOx )
{
    uint32_t i, val=0; 
    for(i=0; i<16; i++)
    {
        val <<=1;
        GPIO_SetBits(GPIOx, MDC); 
        delay(1);
        GPIO_ResetBits(GPIOx, MDC);
        delay(1);
        val |= GPIO_ReadInputDataBit(GPIOx, MDIO);
    }
    return (val);
}

void turnaround_MDIO( GPIO_TypeDef* GPIOx)
{

    GPIOx->OUTENCLR = MDIO ;

    delay(1);
    GPIO_SetBits(GPIOx, MDC); 
    delay(1);
    GPIO_ResetBits(GPIOx, MDC);
    delay(1);
}

void idle_MDIO( GPIO_TypeDef* GPIOx )
{

    GPIOx->OUTENSET = MDIO ;

    GPIO_SetBits(GPIOx,MDC); 
    delay(1);
    GPIO_ResetBits(GPIOx, MDC);
    delay(1);
}
uint32_t mdio_read(GPIO_TypeDef* GPIOx, uint32_t PhyRegAddr)
{
    uint32_t val =0;

    /* 32 Consecutive ones on MDO to establish sync */
    //printf("mdio read - sync \r\n");
    output_MDIO(GPIOx, 0xFFFFFFFF, 32);

    /* start code 01, read command (10) */
    //printf("mdio read - start \r\n");
    output_MDIO(GPIOx, 0x06, 4);

    /* write PHY address */
    //printf("mdio write- PHY address \r\n");
    output_MDIO(GPIOx, PHY_ADDR, 5);

    //printf("mdio read - PHY REG address \r\n");
    output_MDIO(GPIOx, PhyRegAddr, 5);

    /* turnaround MDO is tristated */
    //printf("mdio read - turnaround \r\n");
    turnaround_MDIO(GPIOx);

    /* Read the data value */
    //printf("mdio read - read the data value \r\n");
    val = input_MDIO(GPIOx );
    //printf("mdio read - val : %X\r\n", val );

    /* turnaround MDO is tristated */
    //printf("mdio read - idle \r\n");
    idle_MDIO(GPIOx);

    return val;
}

void mdio_write(GPIO_TypeDef* GPIOx, uint32_t PhyRegAddr, uint32_t val)
{
    /* 32 Consecutive ones on MDO to establish sync */
    //printf("mdio write- sync \r\n");
    output_MDIO(GPIOx, 0xFFFFFFFF, 32);

    /* start code 01, write command (01) */
    //printf("mdio write- start \r\n");
    output_MDIO(GPIOx, 0x05, 4);

    /* write PHY address */
    //printf("mdio write- PHY address \r\n");
    output_MDIO(GPIOx, PHY_ADDR, 5);
    
    //printf("mdio read - PHY REG address \r\n");
    output_MDIO(GPIOx, PhyRegAddr, 5);

    /* turnaround MDO */
    //printf("mdio write- turnaround (1,0)\r\n");
    output_MDIO(GPIOx, 0x02, 2);

    /* Write the data value */
    //printf("mdio writeread - read the data value \r\n");
    output_MDIO(GPIOx, val, 16);

    /* turnaround MDO is tristated */
    //printf("mdio write- idle \r\n");
    idle_MDIO(GPIOx);
}

int32_t phy_id(void)
{
    int32_t data;
    int i=0;
		while(1) {
    for(i=0; i<8; i++)
    {
        /* 32 Consecutive ones on MDO to establish sync */
        //printf("mdio read - sync \r\n");
        output_MDIO(GPIOB, 0xFFFFFFFF, 32);

        /* start code 01, read command (10) */
        //printf("mdio read - start \r\n");
        output_MDIO(GPIOB, 0x06, 4);

        /* write PHY address */
        //printf("mdio read - PHY address \r\n");
        output_MDIO(GPIOB, i, 5);

        //printf("mdio read - PHY REG address \r\n");
        output_MDIO(GPIOB, PHYREG_STATUS, 5);

        /* turnaround MDO is tristated */
        //printf("mdio read - turnaround \r\n");
        turnaround_MDIO(GPIOB);

        /* Read the data value */
        //printf("mdio read - read the data value \r\n");
        data = input_MDIO(GPIOB);
        //printf("mdio read - val : %X\r\n", val );

        /* turnaround MDO is tristated */
        //printf("mdio read - idle \r\n");
        idle_MDIO(GPIOB);
				
         /*For DEBUG*/        
        printf("\r\nPHY_ID = %d , STATUS = %x",i,data);  //right : 0x7869				
        if((data != 0x0000)&&(data != 0xFFFF)) return i;
    }
    printf("\r\nphy id detect error!!\r\n");
	}
    
   // return 0;
    
}


void PHY_Init(void)
{   
#ifdef __DEF_USED_IC101AG__ // For using W7500 + (IC+101AG PHY)
    *(volatile uint32_t *)(0x41003068) = 0x64; //TXD0 - set PAD strengh and pull-up
    *(volatile uint32_t *)(0x4100306C) = 0x64; //TXD1 - set PAD strengh and pull-up
    *(volatile uint32_t *)(0x41003070) = 0x64; //TXD2 - set PAD strengh and pull-up
    *(volatile uint32_t *)(0x41003074) = 0x64; //TXD3 - set PAD strengh and pull-up
    *(volatile uint32_t *)(0x41003050) = 0x64; //TXE  - set PAD strengh and pull-up
#endif
#ifdef __W7500P__ // W7500P only
    // PB_05, PB_12 pull down
    *(volatile uint32_t *)(0x41003070) = 0x61; // RXDV - set pull down (PB_12)
    *(volatile uint32_t *)(0x41002054) = 0x01; // PB 05 AFC
    *(volatile uint32_t *)(0x41003054) = 0x61; // COL  - set pull down (PB_05)
    *(volatile uint32_t *)(0x41002058) = 0x01; // PB 06 AFC
    *(volatile uint32_t *)(0x41003058) = 0x61; // DUP  - set pull down (PB_06)
    
    // PHY reset pin pull-up
    *(volatile uint32_t *)(0x410020D8) = 0x01; // PD 06 AFC[00 : zero / 01 : PD06]
    *(volatile uint32_t *)(0x410030D8) = 0x02; // PD 06 PADCON
    *(volatile uint32_t *)(0x45000004) = 0x40; // GPIOD DATAOUT [PD06 output 1]
   *(volatile uint32_t *)(0x45000010) = 0x40; // GPIOD OUTENSET    
#endif
#ifdef __DEF_USED_MDIO__     
    mdio_init(GPIOB, MDC, MDIO);                // MDIO Init
    mdio_write(GPIOB, PHYREG_CONTROL, CNTL_RESET);   // PHY Reset
#endif
}

