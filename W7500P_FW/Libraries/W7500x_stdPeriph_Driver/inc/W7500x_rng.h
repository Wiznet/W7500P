/**
  ******************************************************************************
  * @file    W7500x_stdPeriph_Driver/inc/W7500x_rng.h
  * @author  IOP Team
  * @version V1.0.0
  * @date    26-AUG-2015
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
