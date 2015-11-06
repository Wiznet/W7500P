/**
  ******************************************************************************
  * @file    GPIO/Interrupt/main.c 
  * @author  IOP Team
  * @version V1.0.5
  * @date    05-June-2015
  * @brief   Main program body
  ******************************************************************************
  * @par Revision history
  *    <2015/06/05> 1st Release
  *
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

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/

/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Main program.
  */
int main()
{
    /* set system */
    SystemInit();

    /* GPIO Configuration */
    GPIO_Configuration(GPIOC, GPIO_Pin_0, GPIO_Mode_OUT,PAD_AF1); // LED_R
    GPIO_Configuration(GPIOC, GPIO_Pin_4, GPIO_Mode_OUT,PAD_AF1); // LED_G
	
    GPIO_ResetBits(GPIOC, GPIO_Pin_0); // LED_R off
    GPIO_ResetBits(GPIOC, GPIO_Pin_4); // LED_G off
    
    /* GPIO Interrupt Configuration */
    GPIO_INT_Configuration(GPIOC, GPIO_Pin_6, Rising);
	  NVIC_EnableIRQ(PORT2_IRQn); // GPIOC IRQ enable
    
    while(1)
    {
        ; // wait for GPIO Interrupt!!    
	}
}
