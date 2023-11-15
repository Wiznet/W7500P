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
  * @file    W7500x_stdPeriph_Driver/inc/W7500x_adc.h
  * @author  IOP Team
  * @version V1.0.0
  * @date    01-May-2015
  * @brief   This file contains all the functions prototypes for the ADC 
  *          firmware library.
  ******************************************************************************
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __W7500X_ADC_H
#define __W7500X_ADC_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "W7500x.h"


/** @addtogroup W7500x_Periph_Driver
  * @{
  */

/** @addtogroup WDT
  * @{
  */ 
  
  
  
typedef enum { ADC_CH0 = 0, 
	       ADC_CH1 = 1,
	       ADC_CH2 = 2, 
	       ADC_CH3 = 3,
	       ADC_CH4 = 4,
	       ADC_CH5 = 5,
	       ADC_CH6 = 6,
	       ADC_CH7 = 7,
	       ADC_CH15 = 15} ADC_CH;

#define IS_ADC_CH_NUM(NUM)                (((NUM) == ADC_CH0) || \
		                           ((NUM) == ADC_CH1) || \
		                           ((NUM) == ADC_CH2) || \
		                           ((NUM) == ADC_CH3) || \
		                           ((NUM) == ADC_CH4) || \
		                           ((NUM) == ADC_CH5) || \
		                           ((NUM) == ADC_CH6) || \
		                           ((NUM) == ADC_CH7) || \
		                           ((NUM) == ADC_CH15))

void ADC_Init(void); 
void ADC_DeInit(void);
void ADC_PowerDownEnable (FunctionalState NewState);
void ADC_ChannelSelect (ADC_CH num);
void ADC_Start (void);
uint16_t ADC_ReadData (void);
void ADC_InterruptMask (FunctionalState NewState);
uint8_t ADC_IsEOC (void);
void ADC_InterruptClear (void);

#ifdef __cplusplus
 }
#endif

#endif  //__W7500X_ADC_H


/**
  * @}
  */

/**
  * @}
  */
