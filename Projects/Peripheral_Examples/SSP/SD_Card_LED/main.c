/*******************************************************************************************************************************************************
 * Copyright �� 2016 <WIZnet Co.,Ltd.> 
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the ��Software��), 
 * to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, 
 * and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

 * THE SOFTWARE IS PROVIDED ��AS IS��, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. 
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, 
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*********************************************************************************************************************************************************/
/**
  ******************************************************************************
  * @file    SSP/SD_Card_LED/main.c 
  * @author  IOP Team
  * @version V1.0.0
  * @date    26-AUG-2015
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
#include <stdio.h>
#include "W7500x_gpio.h"
#include "W7500x_ssp.h"
#include "W7500x_uart.h"
#include "mmc_sd.h"

/* Private typedef -----------------------------------------------------------*/
typedef enum {FAILED = 0, PASSED = !FAILED} TestStatus;

/* Private define ------------------------------------------------------------*/
#define BLOCK_SIZE            511 /* Block Size in Bytes */

#define NUMBER_OF_BLOCKS      8  /* For Multi Blocks operation (Read/Write) */
#define MULTI_BUFFER_SIZE    (BLOCK_SIZE * NUMBER_OF_BLOCKS)

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
UART_InitTypeDef UART_InitStructure;
uint8_t Buffer_Block_Tx[BLOCK_SIZE]={1};
uint8_t Buffer_Block_Rx[BLOCK_SIZE];
uint8_t Buffer_MultiBlock_Tx[MULTI_BUFFER_SIZE]={1};
uint8_t Buffer_MultiBlock_Rx[MULTI_BUFFER_SIZE];
volatile TestStatus EraseStatus = FAILED;
volatile TestStatus TransferStatus1 = FAILED;
volatile TestStatus TransferStatus2 = FAILED;

/* Private function prototypes -----------------------------------------------*/
void SD_SingleBlockTest(void);
void SD_MultiBlockTest(void);
void delay_ms(__IO uint32_t nCount);
TestStatus Buffercmp(uint8_t* pBuffer1, uint8_t* pBuffer2, uint32_t BufferLength);
TestStatus eBuffercmp(uint8_t* pBuffer, uint32_t BufferLength);

/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Main Function
  */
int main()
{
    /* Set Systme init */
    SystemInit();
    /*SD_GPIO_Initailization*/
    bsp_sd_gpio_init();

    /*SD_Initialization*/
    SD_Init();

    /*Single Block Test*/
    SD_SingleBlockTest();

    /*Multi(32) Block Test*/
    SD_MultiBlockTest();
            
	while(1)
	{
	}
}

/**
  * @brief  Tests the SD card Single Blocks operations.
  * @param  None
  * @retval None
  */
void SD_SingleBlockTest(void)
{    
  /* Write block of 512 bytes on address 0 */
  SD_WriteSingleBlock (0x00, Buffer_Block_Tx);

  /* Read block of 512 bytes on address 0 */
  SD_ReadSingleBlock (0x00, Buffer_Block_Rx);

  /* Check the correctness of written data */
  TransferStatus1 = Buffercmp(Buffer_Block_Tx, Buffer_Block_Rx, BLOCK_SIZE);

  if(TransferStatus1 == PASSED)
  {
    GPIO_ResetBits(GPIOC, GPIO_Pin_5); //Blue LED ON
  }
  else
  {
    GPIO_ResetBits(GPIOC, GPIO_Pin_8); //Red LED ON
  }
  delay_ms(1000);
  GPIO_SetBits(GPIOC, GPIO_Pin_5); //Blue LED off
  GPIO_SetBits(GPIOC, GPIO_Pin_8); //Red LED off
  delay_ms(1000);
}

/**
  * @brief  Tests the SD card Single Blocks operations.
  * @param  None
  * @retval None
  */
void SD_MultiBlockTest(void)
{
    
  /* Write block of 512 bytes on address 0 */
  SD_WriteMultiBlock (0x00, Buffer_MultiBlock_Tx, NUMBER_OF_BLOCKS);

  /* Read block of 512 bytes on address 0 */
  SD_ReadMultiBlock (0x00, Buffer_MultiBlock_Rx, NUMBER_OF_BLOCKS);

  /* Check the correctness of written data */
  TransferStatus2 = Buffercmp(Buffer_MultiBlock_Tx, Buffer_MultiBlock_Rx, BLOCK_SIZE);

  if(TransferStatus2 == PASSED)
  {
    GPIO_ResetBits(GPIOC, GPIO_Pin_9);//Green LED ON
  }
  else
  {
    GPIO_ResetBits(GPIOC, GPIO_Pin_8);//Red LED ON
  }
  delay_ms(1000);
  GPIO_SetBits(GPIOC, GPIO_Pin_9);//Green LED off
  GPIO_SetBits(GPIOC, GPIO_Pin_8);//Red LED off
  delay_ms(1000);
}

/**
  * @brief  Compares two buffers.
  * @param  pBuffer1, pBuffer2: buffers to be compared.
  * @param  BufferLength: buffer's length
  * @retval PASSED: pBuffer1 identical to pBuffer2
  *         FAILED: pBuffer1 differs from pBuffer2
  */
TestStatus Buffercmp(uint8_t* pBuffer1, uint8_t* pBuffer2, uint32_t BufferLength)
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
  * @brief  Checks if a buffer has all its values are equal to zero.
  * @param  pBuffer: buffer to be compared.
  * @param  BufferLength: buffer's length
  * @retval PASSED: pBuffer values are zero
  *         FAILED: At least one value from pBuffer buffer is different from zero.
  */
TestStatus eBuffercmp(uint8_t* pBuffer, uint32_t BufferLength)
{
  while (BufferLength--)
  {
    /* In some SD Cards the erased state is 0xFF, in others it's 0x00 */
    if ((*pBuffer != 0xFF) && (*pBuffer != 0x00))
    {
      return FAILED;
    }

    pBuffer++;
  }

  return PASSED;
}

/**
  * @brief  Delay Function
  */
void delay_ms(__IO uint32_t nCount)
{
    volatile uint32_t delay = nCount * 2500; // approximate loops per ms at 24 MHz, Debug config
    for(; delay != 0; delay--)
        __NOP();
}
