/**
  ******************************************************************************
  * @file    /ADC/Illumination_RGBLED/retarget.c 
  * @author  IOP Team
  * @version V1.0.0
  * @date    01-May-2015
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
