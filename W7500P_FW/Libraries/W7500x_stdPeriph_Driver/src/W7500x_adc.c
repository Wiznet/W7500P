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
  * @file    W7500x_stdPeriph_Driver/src/W7500x_adc.c    
  * @author  IOP Team
  * @version v1.0.0
  * @date    01-May-2015
  * @brief   This file contains all the functions prototypes for the adc 
  *          firmware library.
  ******************************************************************************
  *
  * 
  *  @verbatim
  *
  *          ===================================================================
  *                                 How to use this driver
  *          ===================================================================       
  *          In order to read the conversion data, follow steps below:
	*           1. Initializes the ADC using ADC_Init()
  *           2. Select the ADC Channel(ADC_CH0..7 and 15) using ADC_ChannelSelect()
  * 							and Connect the analog device you want to read to the pin to map the channel.
  *           3. Start the ADC using ADC_Start() - Peripherals alternate function:
  *           4. After wait until End of Conversion using ADC_IsEOC(), Read the data using ADC_ReadData(). 
  *             
  *  @endverbatim        
  ******************************************************************************
  */

/*include -------------------------------------*/
#include "W7500x_adc.h"


/** @addtogroup W7500x_Periph_Driver
  * @{
  */
	

/** @defgroup ADC
  * @brief ADC driver modules
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/** @defgroup ADC_Private_Functions
  * @{
  */ 



/**
  * @brief  Initializes the Analog-to-Digital Converter.
	* @param  None
  * @retval None
  */
void ADC_Init (void)
{
	// ADC_CLK on
	ADC_PowerDownEnable(DISABLE);
	//ADC_ChannelSelect(num);
}


/**
  * @brief  Deinitializes the Analog-to-Digital Converter.
  * @param  None
  * @retval None
  */
void ADC_DeInit (void)
{
	// ADC_CLK off
	ADC_PowerDownEnable(ENABLE);
	ADC_InterruptMask(DISABLE);
}





/**
  * @brief  Set or Clear to enable/disable power down mode.
  * @param  NewState: Specifies the ADC powerdown state.
  *          This parameter can be one of the FunctionalState enum values:
  *            @arg DISABLE: to set powerdown disable
  *            @arg ENABLE: to set powerdown enable
  * @retval None
  */
void ADC_PowerDownEnable (FunctionalState NewState)
{
	if (NewState != DISABLE)    ADC->ADC_CTR = ADC_CTR_PWD_PD; /* Set ADC Control register to Power down  */
	else                        ADC->ADC_CTR = ADC_CTR_PWD_NRMOP; /* Set ADC Control register to Active Operation  */
}



/**
  * @brief  Select the ADC Channel to be converted.
  * @param  num: specifies the channel value to be select.
  *          This parameter can be one of the ADC_CH enum values:
	*            @arg ADC_CH0 : PC_15 
	*            @arg ADC_CH1 : PC_14
	*            @arg ADC_CH2 : PC_13
	*            @arg ADC_CH3 : PC_12
	*            @arg ADC_CH4 : PC_11
	*            @arg ADC_CH5 : PC_10
	*            @arg ADC_CH6 : PC_09
	*            @arg ADC_CH7 : PC_08
	*            @arg ADC_CH15 : internal LDO(1.5v) voltage.
  * @retval None
  */
void ADC_ChannelSelect (ADC_CH num)
{
	 /* Check the parameters */
	assert_param(IS_ADC_CH_NUM(num));
	
	
	ADC->ADC_CHSEL = num;
}


/**
  * @brief  Start the ADC for conversion.
  * @param  None
  * @retval None
  */
void ADC_Start (void)
{
	ADC->ADC_START = ADC_START_START;
}


/**
  * @brief  Reads the ADC conversion result data of last converted channel.
  * @param  None
  * @retval The ADC conversion result data.
  */
uint16_t ADC_ReadData (void)
{
	return ((uint16_t)ADC->ADC_DATA);
}



/**
  * @brief  Set or Clear to enable/disable ADC Interrupt mask.
  * @param  NewState: Specifies Interrupt mask state.
  *          This parameter can be one of the FunctionalState enum values:
  *            @arg DISABLE: to set interrupt mask.
  *            @arg ENABLE: to clear interrupt mask.
  * @retval None
  */
void ADC_InterruptMask (FunctionalState NewState)
{
	if (NewState != DISABLE)    ADC->ADC_INT = ADC_INT_MASK_ENA; /* interrupt mask enable */
	else                        ADC->ADC_INT = ADC_INT_MASK_DIS; /* interrupt mask disable */
}



/**
  * @brief  Check whether the conversion is done or not.
  * @param  None
  * @retval The value that tells whether the conversion is done or not.
  */
uint8_t ADC_IsEOC (void)
{
	return (((uint8_t)ADC->ADC_INT && 0x01ul));
}


/**
  * @brief  Set to clear interrupt signal.
	* @note This bit clear automatically after clear interrupt and is write-only.
  * @param  None
  * @retval None
  */
void ADC_InterruptClear (void)
{
	ADC->ADC_INTCLR = ADC_INTCLEAR;
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
