/**
  ******************************************************************************
  * @file    W7500x_stdPeriph_Driver/src/W7500x_rng.c    
  * @author  IOP Team
  * @version v1.0.0
  * @date    26-AUG-2015
  * @brief   This file contains all the functions prototypes for the rng 
  *          firmware library.
  ******************************************************************************
  *
  ******************************************************************************
  */

/*include ----------------------------------------------------------*/
#include "W7500x_rng.h"

void RNG_Run (FunctionalState NewState)
{
	if (NewState != DISABLE)    RNG->RNG_RUN = RNG_RUN_RUN;
	else			    RNG->RNG_RUN = RNG_RUN_STOP;
}

void RNG_SetSeedvalue (uint32_t value)
{
	RNG->RNG_SEED = value;
}

void RNG_SetClockSource (RNG_CLK_SOURCE src)
{
	assert_param(IS_RNG_CLK_SRC(src));
	RNG->RNG_CLKSEL = src;
}

void RNG_ManualRunEn (FunctionalState NewState)
{
	if (NewState != DISABLE)    RNG->RNG_MODE = RNG_MANUAL_ENABLE;
	else			    RNG->RNG_MODE = RNG_MANUAL_DISABLE;
}

uint32_t RNG_ReadRandomNumber (void)
{
	return ((uint32_t)RNG->RNG_RN);
}

void RNG_SetPolynomial (uint32_t value)
{
	RNG->RNG_POLY = value;
}

void RNG_Init (void)
{
	// RNG_CLK on
	RNG_ManualRunEn(ENABLE);
}

void RNG_Deint (void)
{
	// RNG_CLK off
	RNG_ManualRunEn(DISABLE);
}
	
