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
	
