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
  * @file    SSP/Loopback/main.c 
  * @author  IOP Team
  * @version V1.0.0
  * @date    01-May-2015
  * @brief   Main program body
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, WIZnet SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2015 WIZnet Co.,Ltd.</center></h2>
  ******************************************************************************
  */ 

/* Includes ------------------------------------------------------------------*/
#include "W7500x_gpio.h"
#include "W7500x_ssp.h"

/* Private typedef -----------------------------------------------------------*/
typedef enum {FAILED = 0, PASSED = !FAILED} TestStatus;

/* Private define ------------------------------------------------------------*/
#define BufferSize  8

/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/
//UART_InitTypeDef UART_InitStructure;
SSP_InitTypeDef SSP0_InitStructure;
SSP_InitTypeDef SSP1_InitStructure;
GPIO_InitTypeDef GPIO_InitDef;
uint16_t SSP0_Buffer_Tx[BufferSize] = {0x0102, 0x0304, 0x0506, 0x0708, 0x090A, 0x0B0C,
                                  0x0D0E, 0x0F10};
uint16_t SSP1_Buffer_Rx[BufferSize];
uint32_t TxIdx = 0;
uint32_t RxIdx = 0;
volatile TestStatus TransferStatus = FAILED;
                                  
/* Private function prototypes -----------------------------------------------*/
TestStatus Buffercmp(uint16_t* pBuffer1, uint16_t* pBuffer2, uint16_t BufferLength);
void delay_ms(__IO uint32_t nCount);
                                  
/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Main Function
  */
int main()
{

    /* Set Systme init */
    SystemInit();
//    *(volatile uint32_t *)(0x41001014) = 0x0060100; //clock setting 48MHz
    
    /* CLK OUT Set */
//    PAD_AFConfig(PAD_PA,GPIO_Pin_2, PAD_AF2); // PAD Config - CLKOUT used 3nd Function
    /* < SSP_StructInit default values
       SSP_InitStructure.SSP_SerialClockRate   = 0x00;
       SSP_InitStructure.SSP_FrameFormat       = SSP_FrameFormat_MO; 
       SSP_InitStructure.SSP_CPHA              = SSP_CPHA_1Edge;   
       SSP_InitStructure.SSP_CPOL              = SSP_CPOL_Low;
       SSP_InitStructure.SSP_DataSize          = SSP_DataSize_8b;
       SSP_InitStructure.SSP_SOD               = SSP_SOD_RESET;
       SSP_InitStructure.SSP_Mode              = SSP_Mode_Master;
       SSP_InitStructure.SSP_NSS               = SSP_NSS_Hard;
       SSP_InitStructure.SSP_LBM               = SSP_LBM_RESET;
       SSP_InitStructure.SSP_SSE               = SSP_SSE_SET;
       SSP_InitStructure.SSP_BaudRatePrescaler = SSP_BaudRatePrescaler_2;
    */

    /* SSP0 Init -- SSP Master */ 
    SSP_StructInit(&SSP0_InitStructure);
    SSP0_InitStructure.SSP_FrameFormat  = SSP_FrameFormat_MO; // Motorora SPI mode
    SSP0_InitStructure.SSP_DataSize = SSP_DataSize_16b;
    SSP_Init(SSP0,&SSP0_InitStructure);

    /* SSP1 Init -- SSP Slave */
    SSP_StructInit(&SSP1_InitStructure);
    SSP1_InitStructure.SSP_DataSize = SSP_DataSize_16b;
    SSP1_InitStructure.SSP_Mode = SSP_Mode_Slave; // SSP1 = Slave
    SSP_Init(SSP1,&SSP1_InitStructure);
        
    /* GPIO LED(R) Setting */
    GPIO_InitDef.GPIO_Pin = GPIO_Pin_8; // Connecting GPIO_Pin_8(LED(R))
    GPIO_InitDef.GPIO_Mode = GPIO_Mode_OUT; // Set to GPIO Mode to Output Port
    GPIO_Init(GPIOC, &GPIO_InitDef); // Set to GPIOC
	PAD_AFConfig(PAD_PC,GPIO_Pin_8, PAD_AF1); // PAD Config - LED used 2nd Function

    /* GPIO LED(G) Setting */
    GPIO_InitDef.GPIO_Pin = GPIO_Pin_9; // Connecting GPIO_Pin_9(LED(G))
    GPIO_InitDef.GPIO_Mode = GPIO_Mode_OUT; // Set to GPIO Mode to Output Port
    GPIO_Init(GPIOC, &GPIO_InitDef); // Set to GPIOC
	PAD_AFConfig(PAD_PC,GPIO_Pin_9, PAD_AF1); // PAD Config - LED used 2nd Function
            
    GPIO_SetBits(GPIOC, GPIO_Pin_8); // LED red off
    GPIO_SetBits(GPIOC, GPIO_Pin_9); // LED green off
        
    /* Send only data to SSP1 */ 
    for (TxIdx=0; TxIdx<BufferSize; TxIdx++)
    {
        SSP_SendData(SSP0, SSP0_Buffer_Tx[TxIdx]);
        while( SSP_GetFlagStatus(SSP0, SSP_FLAG_BSY) );
    }
    
    /* Receive only data from SSP0 */ 
    while(SSP_GetFlagStatus(SSP1, SSP_FLAG_RNE))
    {
        SSP1_Buffer_Rx[RxIdx] = (uint16_t)SSP_ReceiveData(SSP1);
        RxIdx++;
    }
    
    /* Check the received data with the send ones */
    TransferStatus = Buffercmp(SSP0_Buffer_Tx, SSP1_Buffer_Rx, BufferSize);
    /* TransferStatus = PASSED, if the data transmitted and received are correct */
    /* TransferStatus = FAILED, if the data transmitted and received are different */
    
    if(TransferStatus == PASSED)
    {
        GPIO_ResetBits(GPIOC, GPIO_Pin_9); //Received are correct == LED green On
    }
    else if(TransferStatus == FAILED)
    {
        GPIO_ResetBits(GPIOC, GPIO_Pin_8); //Received are different == LED red On
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
