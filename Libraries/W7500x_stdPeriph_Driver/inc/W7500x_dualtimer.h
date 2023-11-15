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
  * @file    W7500x_stdPeriph_Driver/inc/W7500x_dualtimer.h
  * @author  IOP Team
  * @version V1.0.0
  * @date    01-May-2015
  * @brief   This file contains all the functions prototypes for the dualtimer 
  *          firmware library.
  ******************************************************************************
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __W7500X_DUALTIMER_H
#define __W7500X_DUALTIMER_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "W7500x.h"

/**********************************************************************************************/
/**********************************************************************************************/
//                This structure and define must be in W7500x.h
/**********************************************************************************************/
/**********************************************************************************************/


/** @addtogroup W7500x_Periph_Driver
  * @{
  */

/** @addtogroup Dualtimer
  * @{
  */ 
  
typedef struct
{
    uint32_t TimerLoad;
    uint32_t TimerControl_Mode;
    uint32_t TimerControl_Pre;
    uint32_t TimerControl_Size;
    uint32_t TimerControl_OneShot;    
}DUALTIMER_InitTypDef;


#define IS_DUALTIMER_TimerMode(MODE)        (MODE <= 1) 
#define IS_DUALTIMER_TimerPre(PRE)         (PRE <= 2) 
#define IS_DUALTIMER_TimerSize(SIZE)        (SIZE <= 1) 
#define IS_DUALTIMER_OneShot(ONESHOT)       (ONESHOT <= 1)






#define DUALTIMER_Int_Clear                 0x1ul

#define DUALTIMER_Clock_Enable              0x1ul
#define DUALTIMER_Clock_Disable             ~DUALTIMER_Clock_Enable


#define IS_DUALTIMER_ALL_CH(CH)            ((CH == DUALTIMER0_0) || \
                                            (CH == DUALTIMER0_1) || \
                                            (CH == DUALTIMER1_0) || \
                                            (CH == DUALTIMER1_1)) 



void DUALTIMER_ClockEnable(DUALTIMER_TypeDef* DUALTIMERn);
void DUALTIMER_ClockDisable(DUALTIMER_TypeDef* DUALTIMERn);
void DUALTIMER_DeInit(DUALTIMER_TypeDef* DUALTIMERn);
void DUALTIMER_Init(DUALTIMER_TypeDef* DUALTIMERn, DUALTIMER_InitTypDef* DUALTIMER_InitStruct);
void DUALTIMER_IntConfig(DUALTIMER_TypeDef* DUALTIMERn, FunctionalState state);
void DUALTIMER_IntClear(DUALTIMER_TypeDef* DUALTIMERn);
ITStatus DUALTIMER_GetIntStatus(DUALTIMER_TypeDef* DUALTIMERn);
FlagStatus DUALTIMER_GetIntEnableStatus(DUALTIMER_TypeDef* DUALTIMERn);
void DUALTIMER_Start(DUALTIMER_TypeDef* DUALTIMERn);
void DUALTIMER_Stop(DUALTIMER_TypeDef* DUALTIMERn);
uint32_t DUALTIMER_GetTimerLoad(DUALTIMER_TypeDef* DUALTIMERn);
void DUALTIMER_SetTimerLoad(DUALTIMER_TypeDef* DUALTIMERn, uint32_t TimerLoad);
uint32_t DUALTIMER_GetTimerValue(DUALTIMER_TypeDef* DUALTIMERn);
uint32_t DUALTIMER_GetTimerControl(DUALTIMER_TypeDef* DUALTIMERn);
void DUALTIMER_SetTimerControl(DUALTIMER_TypeDef* DUALTIMERn, uint32_t TimerControl);
uint32_t DUALTIMER_GetTimerRIS(DUALTIMER_TypeDef* DUALTIMERn);
uint32_t DUALTIMER_GetTimerMIS(DUALTIMER_TypeDef* DUALTIMERn);
uint32_t DUALTIMER_GetTimerBGLoad(DUALTIMER_TypeDef* DUALTIMERn);
void DUALTIMER_SetTimerBGLoad(DUALTIMER_TypeDef* DUALTIMERn, uint32_t TimerBGLoad);



//======================= Interrupt handler ==============================
//void DUALTIMER0_Handler();
//void DUALTIMER1_Handler();

#ifdef __cplusplus
} 
#endif

#endif //__W7500X_DUALTIMER_H
/**
  * @}
  */

/**
  * @}
  */
