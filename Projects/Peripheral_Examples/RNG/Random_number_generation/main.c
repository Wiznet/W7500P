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
  * @file    RNG/Random_number_generation/main.c
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
#include "W7500x_rng.h"
#include "W7500x_uart.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
uint32_t rng_data;
	
/* Private function prototypes -----------------------------------------------*/
void UART_Configuration(void);

/* Private functions ---------------------------------------------------------*/

/**
  * @brief   Main program
  * @param  None
  * @retval None
  */

int main()
{

    /*System clock configuration*/
    SystemInit();
    /* UART configuration */
    UART_Configuration();
   
    printf("*****W7500 RNG TEST*****\r\n");

	  // Read Power up random value
    rng_data = RNG_ReadRandomNumber();
	printf("Initial random number = %d\r\n", rng_data);
	
	// RNG Initialize : Change RNG mode to manual RUN
	RNG_Init ();
	  
	// RNG RUN & STOP
	RNG_Run(ENABLE);
		__NOP();
		__NOP();
	RNG_Run(DISABLE);
		
		// Read Manual RUN RNG Data
	rng_data = RNG_ReadRandomNumber();
	printf("manual run & stop random number = %d\r\n", rng_data);
	
	  // Change Seed value & polynimials
    RNG_SetSeedvalue(0x30002001);
	RNG_SetPolynomial(0x90001011);
		
	// RNG RUN & STOP again
	RNG_Run(ENABLE);
		__NOP();
		__NOP();
	RNG_Run(DISABLE);
		
		// Read 2nd Manual RUN RNG data
	rng_data = RNG_ReadRandomNumber();
	printf("updated polynomial & seed value\r\n");
	printf("manual run & stop random number = %d\r\n", rng_data);
	printf("\r\n");
}

void UART_Configuration(void)
{
     UART_InitTypeDef UART_InitStructure;

     /* UART Configuration for UART1*/
     UART_StructInit(&UART_InitStructure);
     UART_Init(UART1,&UART_InitStructure);
	  /* UART Configuration for UART2*/
 	 S_UART_Init(115200);
}	

