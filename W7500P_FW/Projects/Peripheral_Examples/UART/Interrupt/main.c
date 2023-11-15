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
  * @file    Uart/Interrupt/main.c 
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
#include <stdio.h>

#include "W7500x_gpio.h"
#include "W7500x_uart.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
// This variables are initialized at W7500x_it.c
extern uint32_t uart0_tx_cnt, uart0_rx_cnt;
extern uint32_t uart1_tx_cnt, uart1_rx_cnt;

UART_InitTypeDef UART_InitStructure;
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/**
  * @brief   Main program
  * @param  None
  * @retval None
  *
*/

// For using this test code, W7500 must connect UART0 with UART1
// PA13(UTXD0) <----> PB03(URXD1), PA14(U_RXD0) <----> PB02(U_TXD1)
// UART2 is used for monitoring in this test code PB10(U_TXD2), PB11(U_RXD2)

int main()
{
    uint32_t i;  
    
//    *(volatile uint32_t *)(0x41001014) = 0x0060100; //clock setting 48MHz
    
    /*System clock configuration*/
	SystemInit();

    
    /* CLK OUT Set */
//    PAD_AFConfig(PAD_PA,GPIO_Pin_2, PAD_AF2); // PAD Config - CLKOUT used 3nd Function
    
    GPIO_Configuration(GPIOA, GPIO_Pin_7, GPIO_Mode_IN,PAD_AF1); // CTS1(DSR) 
    GPIO_Configuration(GPIOA, GPIO_Pin_8, GPIO_Mode_OUT,PAD_AF1); // RTS1(DTR)
    GPIO_ResetBits(GPIOA, GPIO_Pin_8); // RTS1(DTR)        
             
    GPIO_Configuration(GPIOA, GPIO_Pin_9, GPIO_Mode_AF,PAD_AF2); // TXD1
    GPIO_Configuration(GPIOA, GPIO_Pin_10, GPIO_Mode_AF,PAD_AF2); // RXD1


    /*using debugging*/
    S_UART_Init(115200);
    /* UART0 and UART1 configuration*/
    UART_StructInit(&UART_InitStructure);
    /* Configure UART0 */
    UART_Init(UART0,&UART_InitStructure);
    /* Configure UART1 */
    UART_Init(UART1,&UART_InitStructure);
    /* Configure Uart0 Interrupt Enable*/
    UART_ITConfig(UART0, (UART_IT_FLAG_TXI|UART_IT_FLAG_RXI),ENABLE);
    /* NVIC configuration */
    NVIC_ClearPendingIRQ(UART0_IRQn);
    NVIC_EnableIRQ(UART0_IRQn);
    /* Configure Uart1 Interrupt Enable*/
    UART_ITConfig(UART1,(UART_IT_FLAG_TXI|UART_IT_FLAG_RXI),ENABLE);
     /* NVIC configuration */
    NVIC_ClearPendingIRQ(UART1_IRQn);
    NVIC_EnableIRQ(UART1_IRQn);
    /*send the data from UART0 to UART1*/    
    printf("Send UART0\r\n");
    for(i=0;i<99;i++)
    {
        UartPutc(UART0,(uint8_t)i);
    }
    /*send the data from UART1 to UART0*/    
    printf("Send UART1\r\n");
    for(i=0;i<99;i++)
    {
        UartPutc(UART1,(uint8_t)i);
    }
    /*confirm the rx/tx data counter of Uart0,1 using Uart2*/    
    printf("Press Any Key\r\n");
    while( S_UartGetc() != 0 )
    {
        printf("uart0_rx_cnt = %d, uart0_tx_cnt = %d\r\n",uart0_rx_cnt, uart0_tx_cnt);
        printf("uart1_rx_cnt = %d, uart1_tx_cnt = %d\r\n",uart1_rx_cnt, uart1_tx_cnt);
    }
  
}

