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
  * @file    W7500x_stdPeriph_Driver/inc/W7500x_exti.h
  * @author  IOP Team
  * @version V1.0.0
  * @date    01-May-2015
  * @brief   This file contains all the functions prototypes for the EXTI 
  *          firmware library.
  ******************************************************************************
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __W7500X_EXTI_H
#define __W7500X_EXTI_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "W7500x.h"


/** @addtogroup W7500x_Periph_Driver
  * @{
  */

/** @addtogroup EXTI
  * @{
  */ 
  
  
/** 
  * @brief  EXTI mode enumeration  
  */

typedef enum
{
  EXTI_Mode_Disable = 0x00,
  EXTI_Mode_Interrupt = 0x02
}EXTIMode_TypeDef;

#define IS_EXTI_MODE(MODE) (((MODE) == EXTI_Mode_Rising) || \
                            ((MODE) == EXTI_Mode_Interrupt)) 

/** 
  * @brief  EXTI Trigger enumeration  
  */

typedef enum
{
  EXTI_Trigger_Rising = 0x00,
  EXTI_Trigger_Falling = 0x01  
}EXTITrigger_TypeDef;

#define IS_EXTI_TRIGGER(TRIGGER) (((TRIGGER) == EXTI_Trigger_Rising) || \
                                  ((TRIGGER) == EXTI_Trigger_Falling))

/** 
  * @brief  EXTI Init Structure definition  
  */

typedef struct
{
  uint32_t EXTI_Line;               /*!< Specifies the EXTI lines to be enabled or disabled.
                                         This parameter can be any combination of @ref EXTI_Lines */
   
  EXTIMode_TypeDef EXTI_Mode;       /*!< Specifies the mode for the EXTI lines.This parameter can be a value of @ref EXTIMode_TypeDef */

  EXTITrigger_TypeDef EXTI_Trigger; /*!< Specifies the trigger signal active edge for the EXTI lines.
                                         This parameter can be a value of @ref EXTIMode_TypeDef */

}EXTI_InitTypeDef;

/**
  * @}
  */

void EXTI_DeInit(void);
void EXTI_Init(PAD_Type Px, EXTI_InitTypeDef* EXTI_InitStruct);
void EXTI_Polarity_Set(PAD_Type Px, uint16_t GPIO_Pin, uint16_t Polarity );
void EXTI_StructInit(EXTI_InitTypeDef* EXTI_InitStruct);
uint16_t EXTI_Px_GetEXTEN(PAD_Type Px);
uint16_t EXTI_Px_GetEXTINTPOL(PAD_Type Px);


#ifdef __cplusplus
}
#endif


#endif //__W7500X_EXTI_H
/**
  * @}
  */

/**
  * @}
  */
