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
  * @file    Uart/Uart_HardwareFlowControl/main.c 
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
#include "W7500x_uart.h"
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define TxBufferSize   (countof(TxBuffer) - 1)
#define RxBufferSize   0x10
/* Private macro -------------------------------------------------------------*/
#define countof(a)   (sizeof(a) / sizeof(*(a)))
/* Private variables ---------------------------------------------------------*/
uint32_t uart0_tx_cnt;
uint32_t uart0_rx_cnt;
uint32_t uart1_tx_cnt;
uint32_t uart1_rx_cnt;
uint8_t TxBuffer[] = "W7500 UART TEST!!\r\n";
uint8_t RxBuffer[RxBufferSize];
uint32_t DataToRead = TxBufferSize;
uint8_t TxCounter = 0;
uint8_t RxCounter = 0;
UART_InitTypeDef UART_InitStructure;
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
void SetUartIFLS(UART_TypeDef* UARTx, uint8_t RxSel, uint8_t TxSel);
/* Example description
 * For using this test code, W7500 must connect UART0 with UART1
 * PA13(UART0_TXD) ----> PB03(UART1_RXD), PA14(UART0_RXD) <---- PB02(UART1_TXD)
 * PA11(UART0_CTS) <---- PB01(UART1_RTS), PA12(UART0_RTS) ----> PB00(UART1_CTS)
 * UART2 is used for monitoring in this test code PB10(U_TXD2), PB11(U_RXD2)
 * When the RTS flow control is '1', nUARTRTS is asserted until the receive FIFO is filled up to the programmed
 * watermark level, When the CTS flow control is enaled, the transmitter cn onlt transmit data when nUARTCTS is asserted.
*/
/**
  * @brief   Main program
  * @param  None
  * @retval None
  *
*/

int main()
{
    uint32_t i;
    uint8_t idx;
  

	/*System clock configuration*/
	SystemInit();
    /* UART0 and UART1 configuration*/
    UART_StructInit(&UART_InitStructure);
    /*Hardware Flow Control use(RTS/CTS).*/
    UART_InitStructure.UART_HardwareFlowControl = UART_HardwareFlowControl_RTS_CTS;
    /*Transmit and receive FIFO buffers are enable(FIFO mode)*/
    UART0->LCR_H |=UART_LCR_H_FEN;
    UART1->LCR_H |=UART_LCR_H_FEN;
    /*UART FIFO Level Select  - TX/RX  level select 1/4 full. */
    SetUartIFLS(UART0,UART_IFLS_RXIFLSEL1_4,UART_IFLS_TXIFLSEL1_4);
    SetUartIFLS(UART1,UART_IFLS_RXIFLSEL1_4,UART_IFLS_TXIFLSEL1_4);
    /* Configure UART0 */
    UART_Init(UART0,&UART_InitStructure);
    /* Configure UART1 */
    UART_Init(UART1,&UART_InitStructure);

#ifdef UART2_DEBUG
    S_UART_Init(115200);
#endif


#ifdef UART2_DEBUG
printf("TxBufferSize= %x\r\n",TxBufferSize);
#endif 
    /* The data of TXbuffer send from UART0 to UART1.*/
    for(idx=0; idx<= TxBufferSize-1; idx++)
    {
     /*Check the RTS of UART1 bit*/
       if((UART0->FR &UART_FR_CTS )!=0)
       {         
            UART0->DR = TxBuffer[idx];
       /*If this bit is set to 1, the UART is busy transmitting data. 
        * This bitt remains set until the complete byte, including all the stop bits, has been sent from the shift register,*/
            while(UART0->FR & UART_FR_BUSY);
#ifdef UART2_DEBUG 
            printf("idx = %x\r\n",idx);
#endif            
       }
    }
#ifdef UART2_DEBUG     
    printf("\r\n");   
    printf("Read DATA : \r\n");
#endif
    
    /*Check the  data of RXbuffer(from UART0 to UART1)*/
    for(i=0; i<=idx-2 ;i++)
    {
        /*Confirm the RX FIFO Empty flag*/
        if((UART1->FR & UART_FR_RXFE)==0)
        {
            RxBuffer[i] = (UART1->DR & 0xFF);
 #ifdef UART2_DEBUG 
            printf("%x = %c\r\n",i,RxBuffer[i]);
 #endif
        }
    }
}

/*Set interrupt FIFO level select register*/
void SetUartIFLS(UART_TypeDef* UARTx, uint8_t RxSel, uint8_t TxSel)
{
    UARTx ->IFLS &= ~0xFFFF;
    UARTx ->IFLS |= RxSel|TxSel;
}
