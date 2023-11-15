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
  * @file    RNG/Random_number_generation/retarget.c
  * @author  IOP Team
  * @version V1.0.0
  * @date    26-AUG-2015
  * @brief   Using for printf function
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
#include <stdio.h>
#include "W7500x_uart.h"

#define USING_UART2

#if defined (USING_UART0)
    #define UART_SEND_BYTE(ch)  UartPutc(UART0,ch)
    #define UART_RECV_BYTE()    UartGetc(UART0)
#elif defined (USING_UART1)
    #define UART_SEND_BYTE(ch)  UartPutc(UART1,ch)
    #define UART_RECV_BYTE()    UartGetc(UART1)
#elif defined (USING_UART2)
    #define UART_SEND_BYTE(ch)  S_UartPutc(ch)
    #define UART_RECV_BYTE()    S_UartGetc()
#endif


#if defined ( __CC_ARM   )
/******************************************************************************/
/* Retarget functions for ARM DS-5 Professional / Keil MDK                                 */
/******************************************************************************/
#include <time.h>
#include <rt_misc.h>
#pragma import(__use_no_semihosting_swi)

struct __FILE { int handle; /* Add whatever you need here */ };
FILE __stdout;
FILE __stdin;

int fputc(int ch, FILE *f) {
    return (UART_SEND_BYTE(ch));
}

int fgetc(FILE *f) {
    return (UART_SEND_BYTE(UART_RECV_BYTE()));
}

int ferror(FILE *f) {
    /* Your implementation of ferror */
    return EOF;
}

void _ttywrch(int ch) {
    UART_SEND_BYTE(ch);
}

void _sys_exit(int return_code) {
   label:  goto label;  /* endless loop */
}

#elif defined (__GNUC__)
/******************************************************************************/
/* Retarget functions for GNU Tools for ARM Embedded Processors               */
/******************************************************************************/
#include <sys/stat.h>

__attribute__ ((used))  int _write (int fd, char *ptr, int len)
{
  size_t i;
  for (i=0; i<len;i++) {
    UART_SEND_BYTE(ptr[i]); // call character output function
    }
  return len;
}
#else //using TOOLCHAIN_IAR

int putchar(int ch)
{
    return (UART_SEND_BYTE(ch));
}

int getchar(void)
{
    return (UART_SEND_BYTE(UART_RECV_BYTE()));
}

#endif
