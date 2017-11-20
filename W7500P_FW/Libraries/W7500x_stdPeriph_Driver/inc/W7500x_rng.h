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
  * @file    W7500x_stdPeriph_Driver/inc/W7500x_rng.h
  * @author  IOP Team
  * @version V1.0.0
  * @date    01-May-2015
  * @brief   This file contains all the functions prototypes for the RNG 
  *          firmware library.
  ******************************************************************************
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef W7500x_RNG_H
#define W7500x_RNG_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "W7500x.h"


/** @addtogroup W7500x_Periph_Driver
  * @{
  */

/** @addtogroup RNG
  * @{
  */        
  
  
typedef enum { RNG_CLK_RNGCLK = 0, RNG_CLK_APBCLK } RNG_CLK_SOURCE;

#define IS_RNG_CLK_SRC(SRC)               (((SRC) == RNG_CLK_RNGCLK || (SRC) == RNG_CLK_APBCLK))

void RNG_Init (void);
void RNG_Deinit (void);
void RNG_Run (FunctionalState NewState);
void RNG_SetSeedvalue (uint32_t value);
void RNG_SetClockSource (RNG_CLK_SOURCE src);
void RNG_ManualRunEn (FunctionalState NewState);
uint32_t RNG_ReadRandomNumber (void);
void RNG_SetPolynomial (uint32_t value);

#ifdef __cplusplus
}
#endif

#endif /* __W7500X_RNG_H */
/**
  * @}
  */

/**
  * @}
  */
