/**
  ******************************************************************************
  * @file    PWM/TimerMode/main.c 
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
#include "W7500x.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
PWM_TimerModeInitTypeDef TimerModeStructure;
uint32_t PrescalerValue = 0;

/* Private function prototypes -----------------------------------------------*/
void PWM0_Handler(void);
void GPIO_Setting(void);
void NVIC_Configuration(void);
/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Main program
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

    /* Timer mode configuration */
    PrescalerValue = ((SystemCoreClock / 1000000) / 10); // Prescale is 2 for 10MHz
    TimerModeStructure.PWM_CHn_PR = PrescalerValue - 1;
    TimerModeStructure.PWM_CHn_MR = 600000;
    TimerModeStructure.PWM_CHn_LR = 1200000;
    TimerModeStructure.PWM_CHn_UDMR = PWM_CHn_UDMR_UpCount;
    TimerModeStructure.PWM_CHn_PDMR = PWM_CHn_PDMR_Periodic;
    
    PWM_TimerModeInit(PWM_CH0, &TimerModeStructure); 

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
    
     /* GPIO Configuration for green LED */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4; ///< Connecting GPIO_Pin_8(LED(G))
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT; ///< Set to GPIO Mode to Output Port
    GPIO_Init(GPIOC, &GPIO_InitStructure);
    PAD_AFConfig(PAD_PC, GPIO_Pin_4, PAD_AF1); ///< PAD Config - LED used 2nd Function
    
    /* GPIO Configuration for blue LED */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5; ///< Connecting GPIO_Pin_5(LED(B))
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT; ///< Set to GPIO Mode to Output Port
    GPIO_Init(GPIOC, &GPIO_InitStructure);
    PAD_AFConfig(PAD_PC, GPIO_Pin_5, PAD_AF1); ///< PAD Config - LED used 2nd Function
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



	
	
