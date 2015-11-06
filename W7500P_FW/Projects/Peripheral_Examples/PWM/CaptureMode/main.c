/**
  ******************************************************************************
  * @file    PWM/CaptureMode/main.c 
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
PWM_CaptureModeInitTypeDef CaptureModeStruct;
uint32_t PrescalerValue = 0;
uint32_t CaptureValue = 0;

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
    PrescalerValue = (SystemCoreClock / 1000000) / 10; // Prescale is 2 for 10MHz
    CaptureModeStruct.PWM_CHn_PR = PrescalerValue - 1;
    CaptureModeStruct.PWM_CHn_MR = 600000;
    CaptureModeStruct.PWM_CHn_LR = 1200000;
    CaptureModeStruct.PWM_CHn_UDMR = PWM_CHn_UDMR_UpCount;
    CaptureModeStruct.PWM_CHn_PDMR = PWM_CHn_PDMR_Periodic;
    CaptureModeStruct.PWM_CHn_CMR = PWM_CHn_CMR_RisingEdge;

    PWM_CaptureModeInit(PWM_CH0, &CaptureModeStruct);

    /* PWM interrupt configuration :*/
    PWM_IntConfig(PWM_CH0, ENABLE);
    PWM_CHn_IntConfig(PWM_CH0, PWM_CHn_IER_CIE, ENABLE);

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
    GPIO_InitTypeDef GPIO_InitStruct;

    /* GPIO Configuration for red LED */
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_8; ///< Connecting GPIO_Pin_8(LED(R))
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT; ///< Set GPIO Mode as Output Port
    GPIO_Init(GPIOC, &GPIO_InitStruct);
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

