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
  * @file    PWM/PWMoutput/main.c 
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
PWM_TimerModeInitTypeDef TimerModeStructure;
uint32_t PrescalerValue = 0;

/* Private function prototypes -----------------------------------------------*/
void GPIO_Setting(void);
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
    /* CPIO configuration */
    GPIO_Setting();

    /* Timer mode configuration for PWM3*/
    PrescalerValue = (SystemCoreClock / 1000000) / 10; // Prescale is 2 for 10MHz
    TimerModeStructure.PWM_CHn_PR = PrescalerValue - 1;
    TimerModeStructure.PWM_CHn_MR = 80000;
    TimerModeStructure.PWM_CHn_LR = 100000; // 80% duty cycle
    TimerModeStructure.PWM_CHn_UDMR = PWM_CHn_UDMR_UpCount;
    TimerModeStructure.PWM_CHn_PDMR = PWM_CHn_PDMR_Periodic;
    
    PWM_TimerModeInit(PWM_CH3, &TimerModeStructure);
    
    /* Timer mode configuration for PWM4*/
    TimerModeStructure.PWM_CHn_PR = PrescalerValue - 1;
    TimerModeStructure.PWM_CHn_MR = 30000;
    TimerModeStructure.PWM_CHn_LR = 100000; // 30% duty cycle
    TimerModeStructure.PWM_CHn_UDMR = PWM_CHn_UDMR_UpCount;
    TimerModeStructure.PWM_CHn_PDMR = PWM_CHn_PDMR_Periodic;
    
    PWM_TimerModeInit(PWM_CH4, &TimerModeStructure);
    
    /* Timer mode configuration for PWM5*/
    TimerModeStructure.PWM_CHn_PR = PrescalerValue - 1;
    TimerModeStructure.PWM_CHn_MR = 4294900000UL;
    TimerModeStructure.PWM_CHn_LR =  4294800000UL;
    TimerModeStructure.PWM_CHn_UDMR = PWM_CHn_UDMR_DownCount;
    TimerModeStructure.PWM_CHn_PDMR = PWM_CHn_PDMR_Oneshot;
    
    PWM_TimerModeInit(PWM_CH5, &TimerModeStructure);
    

    /* PWM output enable */
    PWM_CtrlPWMOutputEnable(PWM_CH3);
    PWM_CtrlPWMOutputEnable(PWM_CH4);
    PWM_CtrlPWMOutputEnable(PWM_CH5);

    /* PWM start */
    PWM_CHn_Start(PWM_CH3);
    PWM_CHn_Start(PWM_CH4);
    PWM_CHn_Start(PWM_CH5);

    while(1);
}

/**
  * @brief  Configure the GPIO Pins.
  * @param  None
  * @retval None
  */
void GPIO_Setting(void)
{
    PAD_AFConfig(PAD_PA, GPIO_Pin_6, PAD_AF3); ///< PAD Configuration for PWM3 output
    PAD_AFConfig(PAD_PA, GPIO_Pin_7, PAD_AF3); ///< PAD Configuration for PWM4 output
    PAD_AFConfig(PAD_PA, GPIO_Pin_8, PAD_AF3); ///< PAD Configuration for PWM5 output
}

