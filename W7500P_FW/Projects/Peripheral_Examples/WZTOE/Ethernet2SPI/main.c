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
  * @file    WZTOE/Ethernet2SPI/main.c 
  * @author  IOP Team
  * @version V1.0.1
  * @date    16-Mar-2016
  * @brief   Main program body
  ******************************************************************************
  * @attention
  * @par Revision history
  *    <2016/03/16> 1st Release
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, WIZnet SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2016 WIZnet Co.,Ltd.</center></h2>
  ******************************************************************************
  */ 
/* Includes ------------------------------------------------------------------*/
#include <stdio.h>
#include "W7500x_gpio.h"
#include "W7500x_uart.h"
#include "W7500x_crg.h"
#include "W7500x_wztoe.h"
#include "W7500x_miim.h"
#include "W7500x_ssp.h"
#include "socket.h"

/* Private typedef -----------------------------------------------------------*/
UART_InitTypeDef UART_InitStructure;
SSP_InitTypeDef SSP0_InitStructure;
SSP_InitTypeDef SSP1_InitStructure;
GPIO_InitTypeDef GPIO_InitDef;
typedef enum {FAILED = 0, PASSED = !FAILED} TestStatus;

/* Private define ------------------------------------------------------------*/
#define __DEF_USED_MDIO__ 
#define __DEF_USED_IC101AG__ //for W7500 Test main Board V001

#define BufferSize  8

#define SOCK_NUM	0
#define DATA_BUF_SIZE			8
/* Private function prototypes -----------------------------------------------*/
void delay(__IO uint32_t milliseconds); //Notice: used ioLibray
void TimingDelay_Decrement(void);

TestStatus Buffercmp(uint16_t* pBuffer1, uint16_t* pBuffer2, uint16_t BufferLength);
void delay_ms(__IO uint32_t nCount);

void SSP0_Initialize(void);
void SSP1_Initialize(void);
void GPIO_Initialize(void);
/* Private variables ---------------------------------------------------------*/
static __IO uint32_t TimingDelay;
uint8_t test_buf[8];

uint8_t SSP0_Buffer_Tx[BufferSize] = {0x02, 0x04, 0x06, 0x08, 0x0A, 0x0C, 0x0E, 0x10};
uint8_t SSP1_Buffer_Rx[BufferSize];
uint32_t TxIdx = 0;
uint32_t RxIdx = 0;
volatile TestStatus TransferStatus = FAILED;

/**
  * @brief   Main program
  * @param  None
  * @retval None
  */
int main()
{
    //uint8_t tx_size[8] = { 2, 2, 2, 2, 2, 2, 2, 2 };
    //uint8_t rx_size[8] = { 2, 2, 2, 2, 2, 2, 2, 2 };
    uint8_t mac_addr[6] = {0x00, 0x08, 0xDC, 0x01, 0x02, 0x03}; 
    uint8_t src_addr[4] = {192, 168,  0,  9};
    uint8_t gw_addr[4]  = {192, 168,  0,  1};
    uint8_t sub_addr[4] = {255, 255, 255,  0};		
    //uint8_t dns_server[4] = {8, 8, 8, 8};           // for Example domain name server
    uint8_t tmp[8];
		
		int32_t ret;
		uint16_t port=5000, size = 0, sentsize=0;
		uint8_t destip[4];
		uint16_t destport;

		*(volatile uint32_t *)(0x41001014) = 0x0060100; //clock setting 48MHz
		
		/* External Clock */
    //CRG_PLL_InputFrequencySelect(CRG_OCLK);

    /* Set Systme init */
    SystemInit();
		
		SSP0_Initialize();
		SSP1_Initialize();
		GPIO_Initialize();	

		GPIO_SetBits(GPIOC, GPIO_Pin_8); // LED red off
		GPIO_SetBits(GPIOC, GPIO_Pin_9); // LED green off
		GPIO_ResetBits(GPIOC, GPIO_Pin_6); // Test off

    /* UART Init */
    UART_StructInit(&UART_InitStructure);
    UART_Init(UART1,&UART_InitStructure);

    /* SysTick_Config */
    SysTick_Config((GetSystemClock()/1000));

    /* Set WZ_100US Register */
    setTIC100US((GetSystemClock()/10000));
    //getTIC100US();	
    //printf(" GetSystemClock: %X, getTIC100US: %X, (%X) \r\n", 
    //      GetSystemClock, getTIC100US(), *(uint32_t *)TIC100US);        


#ifdef __DEF_USED_IC101AG__ //For using IC+101AG
    *(volatile uint32_t *)(0x41003068) = 0x64; //TXD0 - set PAD strengh and pull-up
    *(volatile uint32_t *)(0x4100306C) = 0x64; //TXD1 - set PAD strengh and pull-up
    *(volatile uint32_t *)(0x41003070) = 0x64; //TXD2 - set PAD strengh and pull-up
    *(volatile uint32_t *)(0x41003074) = 0x64; //TXD3 - set PAD strengh and pull-up
    *(volatile uint32_t *)(0x41003050) = 0x64; //TXE  - set PAD strengh and pull-up
#endif	
    printf("PHY is linked. \r\n"); 
#ifdef __DEF_USED_MDIO__ 
    /* mdio Init */
    mdio_init(GPIOB, MDC, MDIO );
    /* PHY Link Check via gpio mdio */
    while( link() == 0x0 )
    {
        printf(".");  
        delay(500);
    }
    printf("PHY is linked. \r\n");  
#else
    delay(1000);
    delay(1000);
#endif

    /* Network Configuration */
    setSHAR(mac_addr);
    setSIPR(src_addr);
    setGAR(gw_addr);
    setSUBR(sub_addr);

    getSHAR(tmp);
    printf(" MAC ADDRESS : %.2X:%.2X:%.2X:%.2X:%.2X:%.2X\r\n",tmp[0],tmp[1],tmp[2],tmp[3],tmp[4],tmp[5]); 
    getSIPR(tmp);
    printf("IP ADDRESS : %d.%d.%d.%d\r\n",tmp[0],tmp[1],tmp[2],tmp[3]); 
    getGAR(tmp);
    printf("GW ADDRESS : %d.%d.%d.%d\r\n",tmp[0],tmp[1],tmp[2],tmp[3]); 
    getSUBR(tmp);
    printf("SN MASK: %d.%d.%d.%d\r\n",tmp[0],tmp[1],tmp[2],tmp[3]); 
   
    /* Set Network Configuration */
    //wizchip_init(tx_size, rx_size);

    printf(" TEST- START \r\n");  
		
    while(1)
    {
        switch(getSn_SR(SOCK_NUM))
				{
					case SOCK_ESTABLISHED:
					if(getSn_IR(SOCK_NUM) & Sn_IR_CON)
					{
						getSn_DIPR(SOCK_NUM, destip);
						destport = getSn_DPORT(SOCK_NUM);
						printf("%d:Connected - %d.%d.%d.%d : %d\r\n",SOCK_NUM, destip[0], destip[1], destip[2], destip[3], destport);
						setSn_IR(SOCK_NUM,Sn_IR_CON);
					}
					if((size = getSn_RX_RSR(SOCK_NUM)) > 0) // Don't need to check SOCKERR_BUSY because it doesn't not occur.
					{
						if(size > DATA_BUF_SIZE) size = DATA_BUF_SIZE;
						ret = recv(SOCK_NUM, test_buf, size);

						if(ret <= 0) return ret;      // check SOCKERR_BUSY & SOCKERR_XXX. For showing the occurrence of SOCKERR_BUSY.
						
						 /* Send only data to SSP1 */ 
						for (TxIdx=0; TxIdx<size; TxIdx++)
						{
							SSP_SendData(SSP0, test_buf[TxIdx]);
							while( SSP_GetFlagStatus(SSP0, SSP_FLAG_BSY) );
						}
						
						/* Receive only data from SSP0 */
						while(SSP_GetFlagStatus(SSP1, SSP_FLAG_RNE))
						{
							SSP1_Buffer_Rx[RxIdx] = SSP_ReceiveData(SSP1);
							RxIdx++;
						} 
						RxIdx=0;
						
						sentsize = 0;

						while(size != sentsize)
						{
							ret = send(SOCK_NUM, SSP1_Buffer_Rx+sentsize, size-sentsize);
							if(ret < 0)
							{
								close(SOCK_NUM);
								return ret;
							}
							sentsize += ret; // Don't care SOCKERR_BUSY, because it is zero.
						}
					}
						break;
					case SOCK_CLOSE_WAIT:
						printf("%d:CloseWait\r\n",SOCK_NUM);
						if((ret = disconnect(SOCK_NUM)) != SOCK_OK) return ret;
						printf("%d:Socket Closed\r\n", SOCK_NUM);

						break;
					case SOCK_INIT:
						printf("%d:Listen, TCP server loopback, port [%d]\r\n", SOCK_NUM, port);
						if( (ret = listen(SOCK_NUM)) != SOCK_OK) return ret;
						break;
					
					case SOCK_CLOSED:
						
						printf("%d:TCP server loopback start\r\n",SOCK_NUM);
						if((ret = socket(SOCK_NUM, Sn_MR_TCP, port, 0x00)) != SOCK_NUM) return ret;
						printf("%d:Socket opened\r\n",SOCK_NUM);
					
						break;
					
					default:
						break;
					
				}
    }

}

/**
  * @brief  Inserts a delay time.
  * @param  nTime: specifies the delay time length, in milliseconds.
  * @retval None
  */
void delay(__IO uint32_t milliseconds)
{
  TimingDelay = milliseconds;

  while(TimingDelay != 0);
}

/**
  * @brief  Decrements the TimingDelay variable.
  * @param  None
  * @retval None
  */
void TimingDelay_Decrement(void)
{
  if (TimingDelay != 0x00)
  { 
    TimingDelay--;
  }
}
/**
  * @brief  Compares two buffers.
  * @param  pBuffer1, pBuffer2: buffers to be compared.
  * @param  BufferLength: buffer's length
  * @retval PASSED: pBuffer1 identical to pBuffer2
  *         FAILED: pBuffer1 differs from pBuffer2
  */
TestStatus Buffercmp(uint16_t* pBuffer1, uint16_t* pBuffer2, uint16_t BufferLength)
{
  while (BufferLength--)
  {
    if (*pBuffer1 != *pBuffer2)
    {
      return FAILED;
    }

    pBuffer1++;
    pBuffer2++;
  }

  return PASSED;
}

/**
  * @brief  Delay Function
  */
void delay_ms(__IO uint32_t nCount)
{
    volatile uint32_t delay = nCount * 2500;  // approximate loops per ms at 24 MHz, Debug config
    for(; delay != 0; delay--)
        __NOP();
}

void SSP0_Initialize(void) //Master
{
	SSP_StructInit(&SSP0_InitStructure);
	SSP0_InitStructure.SSP_FrameFormat  = SSP_FrameFormat_MO; // Motorora SPI mode
	SSP0_InitStructure.SSP_DataSize = SSP_DataSize_8b;
	//SSP0_InitStructure.SSP_BaudRatePrescaler = SSP_BaudRatePrescaler_4;
	SSP_Init(SSP0,&SSP0_InitStructure);
}
void SSP1_Initialize(void)	//Slave
{
	SSP_StructInit(&SSP1_InitStructure);
	SSP1_InitStructure.SSP_DataSize = SSP_DataSize_8b;
	SSP1_InitStructure.SSP_Mode = SSP_Mode_Slave; // SSP1 = Slave
	SSP_Init(SSP1,&SSP1_InitStructure);
}
void GPIO_Initialize(void)
{
	/* GPIO LED(R) Setting */
	GPIO_InitDef.GPIO_Pin = GPIO_Pin_8; 								// Connecting GPIO_Pin_8(LED(R))
	GPIO_InitDef.GPIO_Mode = GPIO_Mode_OUT; 		// Set to GPIO Mode to Output Port
	GPIO_Init(GPIOC, &GPIO_InitDef); 											// Set to GPIOC
	PAD_AFConfig(PAD_PC,GPIO_Pin_8, PAD_AF1); // PAD Config - LED used 2nd Function

	/* GPIO LED(G) Setting */
	GPIO_InitDef.GPIO_Pin = GPIO_Pin_9; 								// Connecting GPIO_Pin_9(LED(G))
	GPIO_InitDef.GPIO_Mode = GPIO_Mode_OUT; 		// Set to GPIO Mode to Output Port
	GPIO_Init(GPIOC, &GPIO_InitDef); 											// Set to GPIOC
	PAD_AFConfig(PAD_PC,GPIO_Pin_9, PAD_AF1); // PAD Config - LED used 2nd Function
}
