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
  * @file    RTC/RTC_interrupt/main.c 
  * @author  Peter / Team Platform
  * @version V1.0.0
  * @date    12-FEB-2018
  * @brief   RTC Example main
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
#include "W7500x_uart.h"
#include "W7500x_rtc.h"
/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/
GPIO_InitTypeDef GPIO_InitDef;

/* Private function prototypes -----------------------------------------------*/
void RTC_Configuration(void);
void RTC_test(void);
void delay_ms(__IO uint32_t nCount);

/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Main Function
  */
int main()
{
    /* Set Systme init */
    SystemInit();
	  /* Init UART2 for debug message*/
		S_UART_Init(115200);
    printf("Hello RTC!\r\n");
	
		/* RTC configuration */
	  RTC_Configuration();
	
    while(1)
    {
		    //do nothing
    }
}

void RTC_Configuration(void)
{
	  RTC_TIME_Type tmp_t;

    RTC_Init(RTC);

    /* Configuring RTC initial value */
    tmp_t.SEC = 0x50;
    tmp_t.MIN = 0x59;
    tmp_t.HOUR = 0x23;
    tmp_t.DOW = 0x01;
    tmp_t.DOM = 0x31;
    tmp_t.MONTH = 0x12;	
    tmp_t.YEAR = 0x1999;
    RTC_SetFullTime(RTC, &tmp_t);

    /* Enable the RTC Interrupt */
    NVIC_ClearPendingIRQ(RTC_IRQn); // Pending bit Clear
    NVIC_EnableIRQ(RTC_IRQn);       // RTC Interrupt Enable
    RTC_EnableINT(RTC);
    RTC_SetINTMask(RTC, RTC_INTMASK_SECOND);

    /*Set RTC Alarm */
    tmp_t.SEC = 0x00;
    tmp_t.MIN = 0x00;
    tmp_t.HOUR = 0x00;
    tmp_t.DOW = 0x02;
    tmp_t.DOM = 0x01;
    tmp_t.MONTH = 0x01;
    tmp_t.YEAR = 0x2000;
    RTC_SetFullAlarmTime(RTC, &tmp_t);
    RTC_SetAlarmMask(RTC, RTC_INTMASK_ALARM);
}

void RTC_Test(void)
{
	  char date_t[8];
	  char current_t[6];
	
	  RTC_TIME_Type cur_t;
	
    RTC_GetFullTime(RTC, &cur_t);
	
	  sprintf(date_t, "%04x%02x%02x", cur_t.YEAR, cur_t.MONTH, cur_t.DOM);
	  sprintf(current_t, "%02x%02x%02x", cur_t.HOUR, cur_t.MIN, cur_t.SEC);

    printf("RTC DATE: %s [%01x] TIME : %s \r\n", date_t, cur_t.DOW, current_t);
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
