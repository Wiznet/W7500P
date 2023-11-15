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
  * @file    W7500x_stdPeriph_Driver/src/W7500x_dualtimer.c    
  * @author  IOP Team
  * @version v1.0.0
  * @date    01-May-2015
  * @brief   This file contains all the functions prototypes for the dualtimer 
  *          firmware library.
	*            - Initialization and Configuration 
  *            - Timer Interrupt
  *            - Timer Operation setting
  ******************************************************************************
  *  @verbatim
  *  
  *          ===================================================================
  *                                 How to use this driver
  *          ===================================================================
	*
  *          1. Configure enable the Dualtimer IRQ channel using NVIC_EnableIRQ(DUALTIMERx_IRQn).
	*
	*					2.  Enable clock dualtimer using DUALTIMER_ClockEnable();
	*
  *          3. Configure the DUALTIMER_InitTypDef structure to operate the dualtimer .
  *              - TimerLoad: The specified value from which the counter is to decrement(0..0xFFFF_FFFF).
  *              - TimerControl_Mode : Timer Mode
	*																									DUALTIMER_TimerControl_FreeRunning
	*																									DUALTIMER_TimerControl_Periodic							
  *              - TimerControl_Pre:	Timer prescale
	*																									DUALTIMER_TimerControl_Pre_1     
	*																									DUALTIMER_TimerControl_Pre_16           
	*																									DUALTIMER_TimerControl_Pre_256          
  *              - TimerControl_Size: Timer size
	*																									DUALTIMER_TimerControl_Size_16 
	*																									DUALTIMER_TimerControl_Size_32    
  *              - TimerControl_OneShot: One-shot Count
	*																									DUALTIMER_TimerControl_Wrapping
	*																									DUALTIMER_TimerControl_OneShot 
  *                 
  *          4. Initializes the dualtimer using DUALTIMER_Init().
  *                   
  *          5. Enable the dualtimer Interrupt DUALTIMER_IntConfig().
	*
	*					6. Implement the function you want using DUALTIMERn_Handler() in W7500x_it.c
	*							When the timer reaches 0 and interrupt is occured, the handler is called
	*							(If one of the pair timer's interrupt is occureed, it is excuted).
	*					
	*					7. Start the dualtimer operation using DUALTIMER_Start().
  *   
  *  @endverbatim        
  ******************************************************************************
  */

/* Includes -------------------------------------------*/
#include "W7500x_dualtimer.h"



/** @addtogroup W7500x_Periph_Driver
  * @{
  */
	

/** @defgroup Dualtimer
  * @brief Dualtimer driver modules
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/** @defgroup Dualtimer_Private_Functions
  * @{
  */ 


/** @defgroup Dualtimer_Group1 Initialization and Configuration
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
  * @brief  Set timer clock enable.
  * @param  DUALTIMERn: where n can be 0_0, 0_1, 1_0 and 1_1 to select the Timer peripheral.
  * @retval None
  */
void DUALTIMER_ClockEnable(DUALTIMER_TypeDef* DUALTIMERn)
{
    /* Check the parameters */
    assert_param(IS_DUALTIMER_ALL_CH(DUALTIMERn));
	
		/* Set Timer Clock Enable */
    if(DUALTIMERn == DUALTIMER0_0)
        TIMCLKEN0_0 = DUALTIMER_Clock_Enable;
    else if(DUALTIMERn == DUALTIMER0_1)
        TIMCLKEN0_1 = DUALTIMER_Clock_Enable;
    else if(DUALTIMERn == DUALTIMER1_0)
        TIMCLKEN1_0 = DUALTIMER_Clock_Enable;
    else if(DUALTIMERn == DUALTIMER1_1)
        TIMCLKEN1_1 = DUALTIMER_Clock_Enable;
}


/**
  * @brief  Set timer clock disable.
  * @param  DUALTIMERn: where n can be 0_0, 0_1, 1_0 and 1_1 to select the Timer peripheral.
  * @retval None
  */
void DUALTIMER_ClockDisable(DUALTIMER_TypeDef* DUALTIMERn)
{
    /* Check the parameters */
    assert_param(IS_DUALTIMER_ALL_CH(DUALTIMERn));

		/* Set Timer Clock Disable */
    if(DUALTIMERn == DUALTIMER0_0)
        TIMCLKEN0_0 = DUALTIMER_Clock_Disable;
    else if(DUALTIMERn == DUALTIMER0_1)
        TIMCLKEN0_1 = DUALTIMER_Clock_Disable;
    else if(DUALTIMERn == DUALTIMER1_0)
        TIMCLKEN1_0 = DUALTIMER_Clock_Disable;
    else if(DUALTIMERn == DUALTIMER1_1)
        TIMCLKEN1_1 = DUALTIMER_Clock_Disable;
}



/**
  * @brief  Deinitializes the DUALTIMERn peripheral registers to their default reset values.
  * @param  DUALTIMERn: where n can be 0_0, 0_1, 1_0 and 1_1 to select the Timer peripheral.
  * @retval None

  */
void DUALTIMER_DeInit(DUALTIMER_TypeDef* DUALTIMERn)
{
    /* Check the parameters */
    assert_param(IS_DUALTIMER_ALL_CH(DUALTIMERn));
		
		/* Stop the timer */
    DUALTIMER_Stop(DUALTIMERn);

    DUALTIMERn->TimerLoad = 0x0;
    DUALTIMERn->TimerControl = 0x20;
    DUALTIMERn->TimerBGLoad = 0x0;
}


/**
  * @brief  Initializes the DUALTIMER Unit peripheral according to 
  *         the specified parameters in the TIM_TimeBaseInitStruct.
  * @param  DUALTIMERn: where n can be 0_0, 0_1, 1_0 and 1_1 to select the Timer peripheral.
  * @param  DUALTIMER_InitStruct: pointer to a DUALTIMER_InitTypDef structure
  *         that contains the configuration information for the specified DUALTIMER peripheral.
  * @retval None
  */
void DUALTIMER_Init(DUALTIMER_TypeDef* DUALTIMERn, DUALTIMER_InitTypDef* DUALTIMER_InitStruct)
{
    uint32_t tmp = 0;
    /* Check the parameters */
    assert_param(IS_DUALTIMER_ALL_CH(DUALTIMERn));
    assert_param(IS_DUALTIMER_TimerMode(DUALTIMER_InitStruct->TimerControl_Mode));
    assert_param(IS_DUALTIMER_TimerPre(DUALTIMER_InitStruct->TimerControl_Pre));
    assert_param(IS_DUALTIMER_TimerSize(DUALTIMER_InitStruct->TimerControl_Size));
    assert_param(IS_DUALTIMER_OneShot(DUALTIMER_InitStruct->TimerControl_OneShot));
    
		/* Stop the DUALTIMER */
    DUALTIMER_Stop(DUALTIMERn);
		
		/* Set Timer Load Value */
    DUALTIMERn->TimerLoad = DUALTIMER_InitStruct->TimerLoad;

		/* Store timer control value in tmp */
    tmp = DUALTIMERn->TimerControl;
    tmp |= (DUALTIMER_InitStruct->TimerControl_Mode << DUALTIMER_TimerControl_TimerMode_Pos);
    tmp |= (DUALTIMER_InitStruct->TimerControl_Pre << DUALTIMER_TimerControl_Pre_Pos); 
    tmp |= (DUALTIMER_InitStruct->TimerControl_Size << DUALTIMER_TimerControl_Size_Pos);
    tmp |= (DUALTIMER_InitStruct->TimerControl_OneShot << DUALTIMER_TimerControl_OneShot_Pos);
    /* Reset values not used */
    tmp &= 0xEF;

		/* Set timer control value */
    DUALTIMERn->TimerControl = tmp;
}









/**
  * @}
  */

/** @defgroup Dualtimer_Group2 Timer Interrupts and flags management
 *  @brief   Dualtimer Interrupts and flags management
 *
@verbatim   
 ===============================================================================
                              Dualtimer Interrupts and flags management
 ===============================================================================  

@endverbatim
  * @{
  */




/**
  * @brief  Initializes the DUALTIMER Interrupt Enable.
	* @note	DUALTIMERx_0, DUALTIMERx_1	
  * @param  DUALTIMERn: where n can be 0_0, 0_1, 1_0 and 1_1 to select the Timer peripheral.
  * @param  state: specifies the value of timer interrupt enable/disable.
  * @retval None
  */
void DUALTIMER_IntConfig(DUALTIMER_TypeDef* DUALTIMERn, FunctionalState state)
{
    /* Check the parameters */
    assert_param(IS_DUALTIMER_ALL_CH(DUALTIMERn));
		
		/* Set timer control enable*/
    if(state == ENABLE)
        DUALTIMERn->TimerControl |= (DUALTIMER_TimerControl_IntEnable << DUALTIMER_TimerControl_IntEnable_Pos);
    
		/* Set timer control disable */
		else 
        DUALTIMERn->TimerControl &= ~(DUALTIMER_TimerControl_IntEnable << DUALTIMER_TimerControl_IntEnable_Pos);
}






/**
  * @brief Set to the DUALTIMERn clears the interrupt output from the counter.
	* @note	You must clear the interrupt to read the next interrupt.
  * @param  DUALTIMERn: where n can be 0_0, 0_1, 1_0 and 1_1 to select the Timer peripheral.
  * @retval None
  */
void DUALTIMER_IntClear(DUALTIMER_TypeDef* DUALTIMERn)
{
    /* Check the parameters */
    assert_param(IS_DUALTIMER_ALL_CH(DUALTIMERn));
		
		/* Set to clears interrupt output */
    DUALTIMERn->TimerIntClr = DUALTIMER_Int_Clear;
}


/**
  * @brief 			Checks whether the specified DUALTIMER Interrupt flag is set or not.
	* @note			This function reads the masked interrupt status value.
  * @param  DUALTIMERn: where n can be 0_0, 0_1, 1_0 and 1_1 to select the Timer peripheral.
  * @retval		The Interrupt status value that is SET or RESET.
  */
ITStatus DUALTIMER_GetIntStatus(DUALTIMER_TypeDef* DUALTIMERn)
{
    /* Check the parameters */
    assert_param(IS_DUALTIMER_ALL_CH(DUALTIMERn));

		/* Return the Timer Masked Interrupt Status Register value */
    return (ITStatus)DUALTIMERn->TimerMIS;
}


/**
  * @brief			Checks whether the specified DUALTIMER Interrupt Enable is set or not.
  * @param  DUALTIMERn: where n can be 0_0, 0_1, 1_0 and 1_1 to select the Timer peripheral.
  * @retval 		The Interrupt Enable Status value that is SET or RESET.
  */
FlagStatus DUALTIMER_GetIntEnableStatus(DUALTIMER_TypeDef* DUALTIMERn)
{
    /* Check the parameters */
    assert_param(IS_DUALTIMER_ALL_CH(DUALTIMERn));

		/* Return the Timer Control Register's bit 5. */
    return (FlagStatus)((DUALTIMERn->TimerControl >> DUALTIMER_TimerControl_IntEnable_Pos) & 0x1);
}



/**
  * @brief Get the Timer Raw Interrupt Status value.
	* @note	This register indicates the raw interrupt status from the counter. This value
	*						is ANDed with the timer interrupt enable bit from the Timer Control Register
	*						to create the masked interrupt.
  * @param  DUALTIMERn: where n can be 0_0, 0_1, 1_0 and 1_1 to select the Timer peripheral.
  * @retval	The Timer Raw Interrupt Statue value of which format is 32bit, but only [0]bit is valid value. 
  */
uint32_t DUALTIMER_GetTimerRIS(DUALTIMER_TypeDef* DUALTIMERn)
{
    /* Check the parameters */
    assert_param(IS_DUALTIMER_ALL_CH(DUALTIMERn));

		/* Return the Timer Raw Interrupt Status Register value */
    return DUALTIMERn->TimerRIS;
}

/**
  * @brief			Get the masked interrupt status value.
	* @note			This value is masked interrupt thiat is passed to the interrupt output pin.
  * @param	DUALTIMERn: where n can be 0_0, 0_1, 1_0 and 1_1 to select the Timer peripheral.
  * @retval		The masked interrupt status value of which format is 32bit, but ony [0]bit is valid value.
  */
uint32_t DUALTIMER_GetTimerMIS(DUALTIMER_TypeDef* DUALTIMERn)
{
    /* Check the parameters */
    assert_param(IS_DUALTIMER_ALL_CH(DUALTIMERn));

		/* Return the Timer Masked Interrupt Status Register value*/
    return DUALTIMERn->TimerMIS;
}





/**
  * @}
  */







/** @defgroup Dualtimer_Group3 Timer Operation Setting
 *  @brief   Dualtimer Operation Setting
 *
@verbatim   
 ===============================================================================
                        Dualtimer Operation Setting
 ===============================================================================  

@endverbatim
  * @{
  */



/**
  * @brief			Set TIMER Enable.  
  * @param  DUALTIMERn: where n can be 0_0, 0_1, 1_0 and 1_1 to select the Timer peripheral.
  * @retval None
  */
void DUALTIMER_Start(DUALTIMER_TypeDef* DUALTIMERn)
{
    /* Check the parameters */
    assert_param(IS_DUALTIMER_ALL_CH(DUALTIMERn));

		/* Set Enable to the Timer Control Register's bit7. */
    DUALTIMERn->TimerControl |= (DUALTIMER_TimerControl_TimerEnable << DUALTIMER_TimerControl_TimerEnable_Pos);
}


/**
  * @brief			Set Timer Disable.
  * @param  DUALTIMERn: where n can be 0_0, 0_1, 1_0 and 1_1 to select the Timer peripheral.
  * @retval		None
  */
void DUALTIMER_Stop(DUALTIMER_TypeDef* DUALTIMERn)
{
    /* Check the parameters */
    assert_param(IS_DUALTIMER_ALL_CH(DUALTIMERn));

		/* Set Disable to the Timer Control Register's bit7. */
    DUALTIMERn->TimerControl &= ~(DUALTIMER_TimerControl_TimerEnable << DUALTIMER_TimerControl_TimerEnable_Pos);
}


/**
  * @brief Get the Timer Load value.
	* @note	The Timer Load register contains the value from which the counter is to decrement. This
								is the value used to reload the counter when Periodic mode is enabled, and
								the current count reaches 0.
  * @param  DUALTIMERn: where n can be 0_0, 0_1, 1_0 and 1_1 to select the Timer peripheral.
  * @retval The Timer Load value of which format is 32bit.
  */
uint32_t DUALTIMER_GetTimerLoad(DUALTIMER_TypeDef* DUALTIMERn)
{
    /* Check the parameters */
    assert_param(IS_DUALTIMER_ALL_CH(DUALTIMERn));
		
		/* Get the Timer Load Register value */
    return DUALTIMERn->TimerLoad;
}




/**
  * @brief Set the Timer Load value in order that the counter is to decrement by the specified value.
	* @note If you set a value in this register, the timer immediately restarts and is replaced by this value.
  * @param  DUALTIMERn: where n can be 0_0, 0_1, 1_0 and 1_1 to select the Timer peripheral.
  * @param  TimerLoad: specifies the value from which the counter is to decrement.
  * @retval None
  */
void DUALTIMER_SetTimerLoad(DUALTIMER_TypeDef* DUALTIMERn, uint32_t TimerLoad)
{
    /* Check the parameters */
    assert_param(IS_DUALTIMER_ALL_CH(DUALTIMERn));

		/* Set the Timer Load Register value */
    DUALTIMERn->TimerLoad = TimerLoad;
}



/**
  * @brief			Get the Timer value.
	* @note			This register provides the current value of the decrementing counter. 
  * @param	DUALTIMERn: where n can be 0_0, 0_1, 1_0 and 1_1 to select the Timer peripheral.
  * @retval 		The Timer value.
  */
uint32_t DUALTIMER_GetTimerValue(DUALTIMER_TypeDef* DUALTIMERn)
{
    /* Check the parameters */
    assert_param(IS_DUALTIMER_ALL_CH(DUALTIMERn));

		/* Get the Timer Value Register value */
    return DUALTIMERn->TimerValue;
}


/**
  * @brief			Get the Timer Control value.
  * @param  DUALTIMERn: where n can be 0_0, 0_1, 1_0 and 1_1 to select the Timer peripheral.
	* @retval 		The Timer Control value whifch of format is 32bi, but only [3:0] and[7:5] are valid value.
  */
uint32_t DUALTIMER_GetTimerControl(DUALTIMER_TypeDef* DUALTIMERn)
{
    /* Check the parameters */
    assert_param(IS_DUALTIMER_ALL_CH(DUALTIMERn));


		/* Return the Timer control Register value */
    return DUALTIMERn->TimerControl;
}


/**
  * @brief Set the Timer Control value 
  * @param  DUALTIMERn: where n can be 0_0, 0_1, 1_0 and 1_1 to select the Timer peripheral.
	* @param	TimerControl: specifies the value to be set to the selected timer.
	*					This parameter can be a value less than 0xFF, only uses [3:0] and [7:5].
	*							[0] OC - One-shot Count
	*									0 : Wrapping mode, default.
	*									1 : One-shot mode.
	*							[1] TS - Timer Size
	*									0 : 16-bit counter, default.
	*									1 : 32-bit counter.
	*						[3:2] TP0 - Timer Prescale.
	*									00 : 0 stages of prescale, clock is divided by 1, default.
	*									01 : 4 stages of prescale, clock is divided by 16.
	*									10 : 8 stages of prescale, clock is divided by 256.
	*									11 : Undefined, do not use.
	*						[5] IE - Interrupt Enable.
	*									0 : Timer Interrupt disable.
	*									1 : Timer Interrupt enabled, default.
	*						[6] TM - Timer Mode.
	*									0 : Timer is in free-running mode, default.
	*									1 : Timer is in periodic mode.
	*						[7] TE - Timer Enable.
	*									0 : Timer disabled, default.
	*									1 : Timer enabled.
  * @retval None
  */
void DUALTIMER_SetTimerControl(DUALTIMER_TypeDef* DUALTIMERn, uint32_t TimerControl)
{
    /* Check the parameters */
    assert_param(IS_DUALTIMER_ALL_CH(DUALTIMERn));

		/* Set the Timer control Register value */
    DUALTIMERn->TimerControl = TimerControl;
}



/**
  * @brief Get the Background Load value.
	* @note This register contains the value from which the counter is to decrement. This
	*			is the value used to reload the counter when Periodic mode is enabled, and
	*			the current count reaches 0.
	*			This register provides an alternative method of accessing the TimerLoad
	*			Register. The difference is that writes to TimerBGLoad Register do not cause
	*			the counter to immediately restart from the new value.
  * @param  DUALTIMERn: where n can be 0_0, 0_1, 1_0 and 1_1 to select the Timer peripheral.
  * @retval		The Timer Background Load Register value.
  */
uint32_t DUALTIMER_GetTimerBGLoad(DUALTIMER_TypeDef* DUALTIMERn)
{
    /* Check the parameters */
    assert_param(IS_DUALTIMER_ALL_CH(DUALTIMERn));

		/* Return the Timer Background Load Register value*/
    return DUALTIMERn->TimerBGLoad;
}





/**
  * @brief Set the Background Load value in order that the counter is to decrement by the specified value.
  * @param  DUALTIMERn: where n can be 0_0, 0_1, 1_0 and 1_1 to select the Timer peripheral.
  * @param  TimerBGLoad: specifies the value from which the counter is to decrement.
  * @retval None
  */
void DUALTIMER_SetTimerBGLoad(DUALTIMER_TypeDef* DUALTIMERn, uint32_t TimerBGLoad)
{
    /* Check the parameters */
    assert_param(IS_DUALTIMER_ALL_CH(DUALTIMERn));
	
    DUALTIMERn->TimerBGLoad = TimerBGLoad;
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


