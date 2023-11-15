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
  * @file    Flash/IAP_Example/main.c 
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
#include "W7500x.h"

/* Private typedef -----------------------------------------------------------*/
typedef enum { FAILED = 0, PASSED = !FAILED} TestStatus;

/* Private define ------------------------------------------------------------*/
#define IAP_ENTRY 0x1FFF1001            // Because Thum code
#define IAP_ERAS            0x010
#define IAP_ERAS_DAT0       (IAP_ERAS + 0)
#define IAP_ERAS_DAT1       (IAP_ERAS + 1)
#define IAP_ERAS_SECT       (IAP_ERAS + 2)              
#define IAP_ERAS_BLCK       (IAP_ERAS + 3)  
#define IAP_ERAS_CHIP       (IAP_ERAS + 4)  
#define IAP_ERAS_MASS       (IAP_ERAS + 5)  
#define IAP_PROG            0x022
#define DAT0_START_ADDR     0x0003FE00
#define DAT1_START_ADDR     0x0003FF00
#define CODE_TEST_ADDR      0x0001F000
#define BLOCK_SIZE      4096
#define SECT_SIZE          256

/* Private macro -------------------------------------------------------------*/
#define __DEBUG

#ifdef __DEBUG
    #include "W7500x_uart.h"
    #define USING_UART  UART1
    UART_InitTypeDef UART_InitStructure;
#endif

/* Private variables ---------------------------------------------------------*/
volatile TestStatus TransferStatus = FAILED;
uint8_t save_buff[BLOCK_SIZE];

/* Private function prototypes -----------------------------------------------*/
TestStatus Buffercmp(uint8_t* pBuffer1, uint8_t* pBuffer2, uint16_t BufferLength);
void DO_IAP( uint32_t id, uint32_t dst_addr, uint8_t* src_addr, uint32_t size);

/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Main Function
  */
int main()
{
    uint32_t i,result;

	SystemInit();
//    *(volatile uint32_t *)(0x41001014) = 0x0060100; //clock setting 48MHz
    
    /* CLK OUT Set */
//    PAD_AFConfig(PAD_PA,GPIO_Pin_2, PAD_AF2); // PAD Config - CLKOUT used 3nd Function
#ifdef __DEBUG
    UART_StructInit(&UART_InitStructure);
    UART_Init(USING_UART,&UART_InitStructure);
    UartPuts(USING_UART,"Test Start\r\n");
#endif


    // Make Dummy Data for Flash Write Test
    for(i=0;i<SECT_SIZE;i++)
    {
        save_buff[i] = i;
    }

    // Step 1 DATA0 Erase, Read, Write Test
    DO_IAP(IAP_ERAS_DAT0,0,0,0);
    DO_IAP(IAP_PROG,DAT0_START_ADDR,save_buff,SECT_SIZE);
    result = Buffercmp((uint8_t*)save_buff,((volatile uint8_t *)(DAT0_START_ADDR)),SECT_SIZE);
#ifdef __DEBUG
    if(result == PASSED)
        UartPuts(USING_UART,"Step1 Test Passed\r\n");
    else
        UartPuts(USING_UART,"Step1 Test Falied\r\n");
#endif


    // Step 2 DATA1 Erase, Read, Write Test
    DO_IAP(IAP_ERAS_DAT1,0,0,0);
    DO_IAP(IAP_PROG,DAT1_START_ADDR,save_buff,SECT_SIZE);
    result = Buffercmp((uint8_t*)save_buff,((volatile uint8_t *)(DAT1_START_ADDR)),SECT_SIZE);
#ifdef __DEBUG
    if(result == PASSED)
        UartPuts(USING_UART,"Step2 Test Passed\r\n");
    else
        UartPuts(USING_UART,"Step2 Test Falied\r\n");
#endif

    // Step 3 Code Flash Block Erase, Read, Write Test
    for(i=0;i<BLOCK_SIZE;i++)
    {
        save_buff[i] = i;
    }

    DO_IAP(IAP_ERAS_BLCK,CODE_TEST_ADDR,0,0);
    DO_IAP(IAP_PROG, CODE_TEST_ADDR,save_buff,BLOCK_SIZE);
    result = Buffercmp((uint8_t*)save_buff,((volatile uint8_t *)(CODE_TEST_ADDR)),BLOCK_SIZE);
#ifdef __DEBUG
    if(result == PASSED)
        UartPuts(USING_UART,"Step3 Test Passed\r\n");
    else
        UartPuts(USING_UART,"Step3 Test Falied\r\n");
#endif
}


/**
  * @brief  DO IAP Function
  */
void DO_IAP( uint32_t id, uint32_t dst_addr, uint8_t* src_addr, uint32_t size)
{
    uint32_t temp_interrupt;

    // Backup Interrupt Set Pending Register
    temp_interrupt = (NVIC->ISPR[0]);
    (NVIC->ISPR[0]) = (uint32_t)0xFFFFFFFF;
    
    // Call IAP Function
    ((void(*)(uint32_t,uint32_t,uint8_t*,uint32_t))IAP_ENTRY)( id,dst_addr,src_addr,size);

    // Restore Interrupt Set Pending Register
    (NVIC->ISPR[0]) = temp_interrupt;
}

/**
  * @brief  Compares two buffers.
  * @param  pBuffer1, pBuffer2: buffers to be compared.
  * @param  BufferLength: buffer's length
  * @retval PASSED: pBuffer1 identical to pBuffer2
  *         FAILED: pBuffer1 differs from pBuffer2
  */
TestStatus Buffercmp(uint8_t* pBuffer1, uint8_t* pBuffer2, uint16_t BufferLength)
{
    while(BufferLength--)
    {   
        if(*pBuffer1 != *pBuffer2)
        {
            return FAILED;
        }
    
        pBuffer1++;
        pBuffer2++;
    }   

    return PASSED;  
}

