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
  * @date    01-May-2015
  * @brief   This file contains all the functions prototypes for the rng 
  *        		  firmware library.
  ******************************************************************************
  *	@par	Revision history
	*	@verbatim
	*
	*								===================================================================
	*																											RNG specific features
	*								===================================================================
	*
	*								RNG is a 32-bit random number generator. RNG generates power on random number when power on reset.
	*								RNG can run/stop by software. RNG seed value and polynomial of RNG can be modified by software.
	*								RNG features
	*								- 32-bit pseudo random number generator
	*								- Formula of pseudo random number generator (polynomial) can be modified.
	*								- Seed value of random generator can be modified.
	*								- Support power on reset random value.
	*								- Random value can be obtains by control start/stop by software.
	*
	*	@endverbatim
	*
	*	@verbatim	
	*								===================================================================
	*																											How to use this driver
	*								===================================================================
	*				
	*								
	*																																Write
	*
	*	@endverbatim
  ******************************************************************************

  */

/*include ----------------------------------------------------------*/
#include "W7500x_rng.h"

/** @addtogroup W7500x_Periph_Driver
  * @{
  */

/** @defgroup RNG
  * @brief RNG driver modules
  * @{
  */


/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/** @defgroup RNG_Private_Functions
  * @{
  */ 
	
/**
  * @brief  		Random Number Generator the NewState peripheral registers 
	* @param	NewState: 0(Disable), 1(Enable)
  * @retval 		None
  */
void RNG_Run (FunctionalState NewState)
{
	if (NewState != DISABLE) 
		/* Set RNG_RUN: RNG_RUN_RUN (0x1 ul) */
		RNG->RNG_RUN = RNG_RUN_RUN;
	else
		/* Set RNG_RUN: RNG_RUN_STOP (0x0 ul) */
		RNG->RNG_RUN = RNG_RUN_STOP;
}

/**
  * @brief  		Random Number Generator set seed value 
	* @param	value: Seed value(32-bit) of random number generator shift register
  * @retval 		None
  */
void RNG_SetSeedvalue (uint32_t value)
{
	/* Set RNG SEED: value */
	RNG->RNG_SEED = value;
}

/**
  * @brief  		Random Number Generator set clock source 
	* @param	src: 0 (RNG clock), 1(PCLK)
  * @retval 		None
  */
void RNG_SetClockSource (RNG_CLK_SOURCE src)
{
	/*	Check the parameters	*/
	assert_param(IS_RNG_CLK_SRC(src));
	/* Set RNG CLKSEL: src */
	RNG->RNG_CLKSEL = src;
}

/**
  * @brief  		Random Number Generator manuial run enable
	* @param	NewState: 0(run/stop by PLL_LOCK signal), 1(run/stop by RNG_RUN register)
  * @retval 		None
  */
void RNG_ManualRunEn (FunctionalState NewState)
{
	if (NewState != DISABLE)    
		/* Set RNG_MODE = RNG_MANUAL_ENABLE */
		RNG->RNG_MODE = RNG_MANUAL_ENABLE;
	else
		/* Set RNG_MODE = RNG_MANUAL_DISABLE */
		RNG->RNG_MODE = RNG_MANUAL_DISABLE;
}

/**
  * @brief  		Random Number Generator read random number
	* @param	None
	* @retval 		RNG_RN: Random number of RNG shift register. These bits are read only registers.
  */
uint32_t RNG_ReadRandomNumber (void)
{
	return ((uint32_t)RNG->RNG_RN);
}

/**
  * @brief  		Random Number Generator POLY
	* @param	value: POLY-32bit polynomial of random number generator
  * @retval 		None
  */
void RNG_SetPolynomial (uint32_t value)
{
	RNG->RNG_POLY = value;
}

/**
  * @brief  		Random Number Generator Initialize
	* @param	None
  * @retval 		None
  */
void RNG_Init (void)
{
	/* RNG_CLK on */
	RNG_ManualRunEn(ENABLE);
}

/**
  * @brief  		Random Number Generator De-Initialize
	* @param	None
  * @retval 		None
  */
void RNG_Deint (void)
{
	/* RNG_CLK off */
	RNG_ManualRunEn(DISABLE);
}

/**
  * @}
  */


/**
  * @}
  */


/**
  * @}
  */
	
