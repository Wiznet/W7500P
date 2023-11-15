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
  * @file    W7500x_stdPeriph_Driver/src/W7500x_wdt.c    
  * @author  IOP Team
  * @version v1.0.0
  * @date    01-May-2015
  * @brief   This file contains all the functions prototypes for the watchdog timer
  *          firmware library.
	*								- Initialization and Configuration
	*								- Interrupts and flags management   
	*								- Specific interface management
  ******************************************************************************
  *  @verbatim  
  *  
  *          ===================================================================
  *                                     WDT features
  *          ===================================================================
  *    
  *          - 32-bit down counter.
	*					- Internally resets chip if not periodically reloaded.
	*					- The watchdog timer has lock register to prevent rogue software from disabling the
	*					- watchdog timer functionality.
	*					- The watchdog timer clock(WDTCLK) and system clock(PCLK) are synchronous.
  *          - The wdt interrupt is connected to a NMI(non-maskable interrupt), unlike other ferries.
	*							So, you don't neet to configure NVIC.
  *          ===================================================================
  *                                 How to use this driver
  *          ===================================================================  
  *              
  *          In order to use an I/O pin as an external interrupt source, follow
  *          steps below:
  *            1- Configure the WDT structrue according to the specified
  *         				parameters in the WDT_InitStruct.
  *            2-  Initializes  the Watchdog Timer using WDT_Init() with configured structure 
  *                 and Start the WDT() using WDT_Start(). 
  *          
  *  @endverbatim          
  ******************************************************************************
  */
  
/* Includes -------------------------------------------*/
#include "W7500x_wdt.h"




/** @addtogroup W7500x_Periph_Driver
  * @{
  */

/** @defgroup WDT
  * @brief WDT driver modules
  * @{
  */


/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/** @defgroup WDT_Private_Functions
  * @{
  */ 

/** @defgroup WDT_Group1 Initialization and Configuration
 *  @brief   Initialization and Configuration
 *
@verbatim   
 ===============================================================================
                        Initialization and Configuration
 ===============================================================================  

@endverbatim
  * @{
  */



/**
  * @brief  Deinitializes the Watchdog Timer peripheral registers to their default reset values.
	* @param  None
  * @retval None
  */
void WDT_DeInit(void)
{
    WDT_Unlock();
		
	/* Set Watchdog Timer Load Register value */
    WDT->WDTLoad      = 0xFFFFFFFF;
	
	/* Set Watchdog Timer Control Register value */
    WDT->WDTControl   = 0;
}


/**
  * @brief  Initializes the Watchdog Timer peripheral according to the specified
  *         parameters in the WDT_InitStruct.
	* @param  WDT_InitStruct: pointer to a WDT_InitTypeDef structure
  *         that contains the configuration information for the WDT peripheral.
  * @retval None
  */
void WDT_Init(WDT_InitTypeDef* WDT_InitStruct)
{
    /* Check the parameters */
    assert_param(IS_WDT_CTRL_RSTEN(WDT_InitStruct->WDTControl_RstEn));
   
    WDT_Stop();
    
		/* Set Watchdog Timer Load Register value*/
    WDT->WDTLoad      = WDT_InitStruct->WDTLoad;
		
		/* Enable/Disable the watchdog reset output */
    WDT->WDTControl   = (WDT_InitStruct->WDTControl_RstEn << WDTControl_RstEn_Pos);

    WDT_Lock();
}



/**
  * @brief			Start the Watchdog Timer.
	* @note			Reloads the counter from the value in WDTLoad, after previously being disabled.
	* 								In case of Watchdog Timer, Start the moment you enable the interrupt.
  * @param  None
  * @retval		None
  */
void WDT_Start(void)
{
    WDT_Unlock();
			
		/* Enable the counter and the interrupt */
    WDT->WDTControl |= (WDTControl_IntEnable << WDTControl_IntEn_Pos); 
    
    WDT_Lock();
}



/**
  * @brief   	Stop the Watchdog timer. 
  * @param  None
  * @retval None
  */
void WDT_Stop(void)
{
    WDT_Unlock();
    
		/* Disable the counter and the interrupt */
    WDT->WDTControl &= ~(WDTControl_IntEnable << WDTControl_IntEn_Pos); 
}


/**
  * @brief   Unlock the Watchdog Timer.
	* @note		This register disables write accesses to all other registers. This is to prevent rogue
	*							software from disabling the watchdog functionality. Writing a value of 0x1ACCE551 
  * @param  None
  * @retval None
  */
void WDT_Unlock(void)
{
		/* Unlock the Watchdog Timer */
    WDT->WDTLock = 0x1ACCE551;
}




/**
  * @brief   Disable the counter and the interrupt. 
  * @param  None
  * @retval None
  */
void WDT_Lock(void)
{
		/* Lock the Watchdog Timer */
    WDT->WDTLock = 0x1;
}
/**
  * @}
  */



/** @defgroup WDT_Group2 Interrupts and flags management   
 *  @brief   Interrupts and flags management   
 *
@verbatim   
 ===============================================================================
                        Interrupts and flags management   
 ===============================================================================  

@endverbatim
  * @{
  */


/**
  * @brief   Clear the Watchdog Timer Interrupt.
	* @note		A write of 1 to the Interrupt Clear register clears the watchdog interrupt, and reloads the
	*							counter from the value in WDTLoad.
  * @param  None
  * @retval 		None
  */
void WDT_IntClear(void)
{
    WDT_Unlock();
    WDT->WDTIntClr = 0x1;
    WDT_Lock();
}


//D20170131  BECKY  WDT_GetWDTMISÁßº¹
/*

  * @brief			Get the Watchdog timer's masked interrupt status.
	* @note			Interrupts must be enabled to obtain this value.
  * @param 	None
  * @retval		The masked interrupt status value.
 
ITStatus WDT_GetIntStatus(void)
{
		 Return the Watchdog Timer Masked Interrupt Status Register value 
    return (ITStatus)WDT->WDTMIS;
}

*/



/**
  * @brief  Set or Clear interrupt enable for the selected data port.
  * @param  SetValue: specifies the value to be set to the WDT Interrupt Enable state.
  *          This parameter can be one of the FunctionalState enum values:
  *            @arg DISABLE: to clear interrupt enable
  *            @arg ENABLE: to set interrupt enable
  * @retval None
  */
void WDT_INT_Enable(FunctionalState SetValue) {

				assert_param(IS_FUNCTIONAL_STATE(SetValue));
	
				WDT_Unlock();		
    
		/* Set the Watchdog Timer Control Register value */
		if(SetValue==ENABLE)
		WDT->WDTControl |= 0x01ul;
    else
			WDT->WDTControl &= 0xFFFFFFFE;
		
			WDT_Lock();
}



/**
  * @brief			Get the Watchdog timer's raw interrupt status.
	* @note			This value is ANDed with the timer interrupt enable bit
	*								to create the masked interrupt.
	* @param 	None
  * @retval		The raw interrupt status value.
  */
ITStatus WDT_GetWDTRIS(void)
{
		/* Return the Watchdog Timer Raw Interrupt Status Register value */
    return (ITStatus)WDT->WDTRIS;
}


/**
  * @brief			Get the Watchdog timer's masked interrupt status.
	* @note			Interrupts must be enabled to obtain this value.
  * @param 	None
  * @retval		The masked interrupt status value.
  */
ITStatus WDT_GetWDTMIS(void)
{
    return (ITStatus)WDT->WDTMIS;
}
/**
  * @}
  */



/** @defgroup WDT_Group3 Specific interface management
 *  @brief   Specific interface management
 *
@verbatim   
 ===============================================================================
                        Specific interface management
 ===============================================================================  

@endverbatim
  * @{
  */


/**
  * @brief			Get the Watchdog timer Load value.
	* @param 	None
  * @retval		The Timer Load value from which the counter is to decrement.
  */
uint32_t WDT_GetWDTLoad(void)
{
		/* Return the Watchdog Timer Load Register value */
    return WDT->WDTLoad;
}


/**
  * @brief			Set the Watchdog timer Load value.
	* @note			 When the Load register is written to, the count is immediately restarted from the
	*									new value. The minimum valid value for WDTLoad is 1.
	* @param 	specifies the value to be written to the watchdogtimer control register.
  * @retval		None
  */
void WDT_SetWDTLoad(uint32_t Load)
{
    WDT_Unlock();
	
		/* Set the Watchdog Timer Load Register value */
    WDT->WDTLoad = Load;
    WDT_Lock();
}


/**
  * @brief			Get the Watchdog timer value.
	* @param 	None
  * @retval		 The current value of the decrementing counter.
  */
uint32_t WDT_GetWDTValue(void)
{
		/* Return the Watchdog Timer value */
    return WDT->WDTValue;
}



/**
  * @brief			Get the Watchdog timer Control Register value.
	* @param 	None
  * @retval		The Watchdog timer Control Register value.
	*									[0] IEN - Interrupt Enable.
	*																	0 : Disable the counter and the interrupt.
	*																	1 : Enable the counter and the interrupt. Reloads the counter from the value
	*																			in WDTLoad, after previously being disabled.
	*									[1] REN - Reset Request Enable.
	*																	0 : Disable watchdog reset output.
	*																	1 : Enable watchdog reset output.
  */
uint32_t WDT_GetWDTControl(void)
{
		/* Return the Watchdog Timer Control Register value */
    return WDT->WDTControl;
}




/**
  * @brief			Set the Watchdog timer Control Register value.
	* @param 	specifies the value to be written to the watchdogtimer control register.
	*									[0] IEN - Interrupt Enable.
	*																	0 : Disable the counter and the interrupt.
	*																	1 : Enable the counter and the interrupt. Reloads the counter from the value
	*																			in WDTLoad, after previously being disabled.
	*									[1] REN - Reset Request Enable.
	*																	0 : Disable watchdog reset output.
	*																	1 : Enable watchdog reset output.
	* @retval 	None
  */
void WDT_SetWDTControl(uint32_t Control)
{
    /* Check the parameters */
    assert_param(IS_WDT_CONTROL(CONTROL));

    WDT_Unlock();
    
		/* Set the Watchdog Timer Control Register value */
		WDT->WDTControl = Control;
    
		WDT_Lock();
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

/**
  * @}
  */

