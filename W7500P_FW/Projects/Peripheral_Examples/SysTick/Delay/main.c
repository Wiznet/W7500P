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
  * @file    SYSTEM/Systick/main.c 
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
#include "W7500x_gpio.h"
#include "W7500x_crg.h"


/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
static __IO uint32_t TimingDelay;
uint32_t sysclock;

/* Private function prototypes -----------------------------------------------*/
void GPIO_Setting(void);
void delay(__IO uint32_t milliseconds);
void TimingDelay_Decrement(void);

/* Private functions ---------------------------------------------------------*/

/**
  * @brief   Main program
  * @param  None
  * @retval None
  */
int main()
{

    /* External Clock */
    CRG_PLL_InputFrequencySelect(CRG_OCLK);


    /* Set Systme init */
    SystemInit();

    /* CPIO configuration */
    GPIO_Setting();

    /* Get System Clock */
    sysclock = GetSystemClock();     

    /* SysTick_Config */
    SysTick_Config((sysclock/1000));

    while(1)
    {
        delay(1000);
        /* RED LED toggled */
        if(GPIO_ReadOutputDataBit(GPIOC,GPIO_Pin_0) != (uint32_t)Bit_RESET)
            GPIO_ResetBits(GPIOC, GPIO_Pin_0);
        else
            GPIO_SetBits(GPIOC, GPIO_Pin_0);
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
  * @brief  Configure the GPIO Pins.
  * @param  None
  * @retval None
  */
void GPIO_Setting(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    
     /* GPIO Configuration for red LED */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0; ///< Connecting GPIO_Pin_0(LED(R))
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT; ///< Set to GPIO Mode to Output Port
    GPIO_Init(GPIOC, &GPIO_InitStructure);
    PAD_AFConfig(PAD_PC, GPIO_Pin_0, PAD_AF1); ///< PAD Config - LED used 2nd Function
}

