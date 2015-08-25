/**
  ******************************************************************************
  * @file    GPIO/Interrupt/W7500x_it.h 
  * @author  IOP Team
  * @version V1.0.6
  * @date    05-June-2015
  * @brief   This file contains the headers of the interrupt handlers.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __W7500X_IT_H
#define __W7500X_IT_H

#ifdef __cplusplus
 extern "C" {
#endif 

/* Includes ------------------------------------------------------------------*/
#include "W7500x.h"

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

void NMI_Handler(void);
void HardFault_Handler(void);
void SVC_Handler(void);
void PendSV_Handler(void);
void SysTick_Handler(void);

void SSP0_Handler(void);
void SSP1_Handler(void);
void UART0_Handler(void);
void UART0_Handler(void);
void UART1_Handler(void);
void UART2_Handler(void);
void I2C0_Handler(void);
void I2C1_Handler(void);
void PORT0_Handler(void);
void PORT1_Handler(void);
void PORT2_Handler(void);
void DMA_Handler(void);
void DUALTIMER0_Handler(void);
void DUALTIMER1_Handler(void);
void PWM0_Handler(void);
void PWM1_Handler(void);
void PWM2_Handler(void);
void PWM3_Handler(void);
void PWM4_Handler(void);
void PWM5_Handler(void);
void PWM6_Handler(void);
void PWM7_Handler(void);
void ADC_Handler(void);
void WZTOE_Handler(void);
void EXTI_Handler(void);






					 
#endif /* __W7500X_IT_H */

/******************* (C) COPYRIGHT 2015 WIZnet Co.,Ltd. *****END OF FILE****/
