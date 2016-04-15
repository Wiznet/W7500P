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
  * @file    PWM/CounterMode/main.c 
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
#include "W7500x_pwm.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
PWM_CounterModeInitTypeDef CounterModeStruct;

/* Private function prototypes -----------------------------------------------*/
void GPIO_Setting(void);
void NVIC_Configuration(void);
/* Private functions ---------------------------------------------------------*/

/**
  * @brief   Main program
  * @param  None
  * @retval None
  */
int main(void)
{
    /*System clock configuration*/
    SystemInit();
    /* NVIC configuration */
    NVIC_Configuration();

    /* CPIO configuration */
    GPIO_Setting();

    /* Time base configuration */
    CounterModeStruct.PWM_CHn_MR = 10;
    CounterModeStruct.PWM_CHn_LR = 20;
    CounterModeStruct.PWM_CHn_UDMR = PWM_CHn_UDMR_UpCount;
    CounterModeStruct.PWM_CHn_PDMR = PWM_CHn_PDMR_Periodic;
    CounterModeStruct.PWM_CHn_TCMR = PWM_CHn_TCMR_RisingCounterMode;

    PWM_CounterModeInit(PWM_CH0, &CounterModeStruct);

    /* PWM interrupt configuration */
    PWM_IntConfig(PWM_CH0, ENABLE);
    PWM_CHn_IntConfig(PWM_CH0, PWM_CHn_IER_MIE | PWM_CHn_IER_OIE, ENABLE);

    /* PWM channel 0 start */
    PWM_CHn_Start(PWM_CH0);

    while(1);
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
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5; ///< Connecting GPIO_Pin_8(LED(R))
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT; ///< Set GPIO Mode as Output Port
    GPIO_Init(GPIOC, &GPIO_InitStructure);
    PAD_AFConfig(PAD_PC, GPIO_Pin_5, PAD_AF1); ///< PAD Config - LED used 2nd Function
 
    /* GPIO Configuration for green LED */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4; ///< Connecting GPIO_Pin_9(LED(G))
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT; ///< Set to GPIO Mode to Output Port
    GPIO_Init(GPIOC, &GPIO_InitStructure);
    PAD_AFConfig(PAD_PC, GPIO_Pin_4, PAD_AF1); ///< PAD Config - LED used 2nd Function

    /* PAD configuration for PWM0 input */
    PAD_AFConfig(PAD_PC, GPIO_Pin_0, PAD_AF2);
}

/**
  * @brief  Configure the nested vectored interrupt controller.
  * @param  None
  * @retval None
  */
void NVIC_Configuration(void)
{
    NVIC_EnableIRQ(PWM0_IRQn);
}

