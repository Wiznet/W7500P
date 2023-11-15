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
  * @file    W7500x_stdPeriph_Driver/src/W7500x_pwm.c    
  * @author  IOP Team
  * @version v1.0.0
  * @date    01-May-2015
  * @brief   This file contains all the functions prototypes for the pwm 
  *          firmware library.
	*					- Denitialization and Start functions
	*					- Interrupts and flags management
	*					- TimeBase management
	*					- Timer/Counter Mode management
	*					- Capture Mode management
	*					- Dead Zone Mode management
	*					- PWM output management
	*					- Interrupts clear function by channel and type
	*
  *              
  *  @verbatim
  *  
  *          ===================================================================
  *                                 How to use this driver
  *          ===================================================================
  *          This driver provides functions to configure and program the PWM
  *          These functions are split in 8 groups: 
  *   
  *          1. Denitialization and Start functions
  *                   - Deinitializes
  *                   - Start/Stop  
  *                   - Restart/Pause   
  *                 
  *          2. Interrupts and flags management
	*                   - Set/Clear the Global Interrupt Enable status
  *                   - Set/Clear the Interrupt Enable status
  *                   - Get the Interrupt flag
  *                   - Clear the Interrupt flag
  *                   
  *          3. TimeBase management
  *                   - Get the Timer/Counter value
  *                   - Get the Prescale Counter value
  *                   - Set/Get the Prescale value
  *                   - Set/Get the Match value
  *                   - Set/Get the Limit value
  *                   - Set/Get the Up-down mode status
  *                   - Set/Get the periodic mode status
  *                   
  *          4. Timer/Counter Mode management
  *                   - Timer Mode initializes
  *                   - Counter Mode initializes
  *                   - Set/Get the Timer/Counter mode status
  *                              
  *          5. Capture Mode management
  *                   - Initializes Captrue Mode
  *                   - Set/Get the Capture Mode Register value(=rising/falling edge)
  *                   - Get the Capture value
  *              
  *          6. Dead Zone Mode management
  *                   - Initializes Deadzon Mode
  *                   - Set/Get the Dead zone mode enable status
	*                   - Set/Get the Dead zone counter value
  *         
  *          7. PWM Output management
  *                   - Set/Get the PWM PEEER register(PWM output and external input enable status) 
  *                   - Control the PWM output enable status(external input is disable)   
  *     
  *          8. Interrupts clear function by channel and type
  *                   - Clear the Match Interrupt
	*                   - Clear the Overflow	Interrupt
	*                   - Clear the Capture Interrupt
  *         
  *   
  *  @endverbatim
  *
	*
  ******************************************************************************
  *
  ******************************************************************************
  */
  
/* Includes -------------------------------------------*/
#include "W7500x_pwm.h"



/** @addtogroup W7500x_Periph_Driver
  * @{
  */

/** @defgroup PWM
  * @brief PWM driver modules
  * @{
  */


/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/** @defgroup PWM_Private_Functions
  * @{
  */ 

/** @defgroup PWM_Group1 Deinitialization and Start functions
 *  @brief   Deinitialization and Start functions
 *
@verbatim   
 ===============================================================================
                  Deinitialization and Start functions
 ===============================================================================  

@endverbatim
  * @{
  */
	
	
/**
  * @brief  Deinitializes the PWM peripheral registers to their default reset values.
  * @param  PWM_CHn: where n can be (0..7) to select the PWM peripheral.
  * @retval None
  */
void PWM_DeInit(PWM_CHn_TypeDef* PWM_CHn)
{
    /* Check the parameters */
    assert_param(IS_PWM_ALL_CH(PWM_CHn));
    
    /* Stop PWM_CHn */
    PWM_CHn_Stop(PWM_CHn);
    
    if( PWM_CHn == PWM_CH0 )
    {
        PWM->IER        &= PWM_IER_IE0_Disable;  ///< Interrupt enable register 
        PWM->SSR        &= PWM_SSR_SS0_Stop;     ///< Start Stop register 
        PWM->PSR        &= PWM_PSR_PS0_Restart;  ///< Pause register 
        PWM_CH0->IER    = 0;                    ///< Interrupt enable register 
        PWM_CH0->ICR    =  PWM_CHn_ICR_MatchInterruptClear      | 
                           PWM_CHn_ICR_OverflowInterruptClear   | 
                           PWM_CHn_ICR_CaptureInterruptClear;   ///< Interrupt clear register
        PWM_CH0->PR     = 0;                    ///< Prescale register 
        PWM_CH0->MR     = 0;                    ///< Match register 
        PWM_CH0->LR     = 0xFFFFFFFF;           ///< Limit register 
        PWM_CH0->UDMR   = 0;                    ///< Up Dowm mode register
        PWM_CH0->TCMR   = 0;                    ///< Timer Counter mode register
        PWM_CH0->PEEER  = 0;                    ///< PWM output Enable and External input Enable register
        PWM_CH0->CMR    = 0;                    ///< Capture mode register
        PWM_CH0->PDMR   = 0;                    ///< Periodic Mode register
        PWM_CH0->DZER   = 0;                    ///< Dead Zone Enable register
        PWM_CH0->DZCR   = 0;                    ///< Dead Zone Counter register
    }
    else if( PWM_CHn == PWM_CH1 )
    {
        PWM->IER        &= PWM_IER_IE1_Disable;  ///< Reset Interrupt enable register 
        PWM->SSR        &= PWM_SSR_SS1_Stop;     ///< Reset Start Stop register 
        PWM->PSR        &= PWM_PSR_PS1_Restart;  ///< Reset Pause register 
        PWM_CH1->IER    = 0;                    ///< Interrupt enable register 
        PWM_CH1->ICR    =  PWM_CHn_ICR_MatchInterruptClear      | 
                           PWM_CHn_ICR_OverflowInterruptClear   | 
                           PWM_CHn_ICR_CaptureInterruptClear;   ///< Interrupt clear register
        PWM_CH1->PR     = 0;                    ///< Prescale register 
        PWM_CH1->MR     = 0;                    ///< Match register 
        PWM_CH1->LR     = 0xFFFFFFFF;           ///< Limit register 
        PWM_CH1->UDMR   = 0;                    ///< Up Dowm mode register
        PWM_CH1->TCMR   = 0;                    ///< Timer Counter mode register
        PWM_CH1->PEEER  = 0;                    ///< PWM output Enable and External input Enable register
        PWM_CH1->CMR    = 0;                    ///< Capture mode register
        PWM_CH1->PDMR   = 0;                    ///< Periodic Mode register
        PWM_CH1->DZER   = 0;                    ///< Dead Zone Enable register
        PWM_CH1->DZCR   = 0;                    ///< Dead Zone Counter register
    }
    else if( PWM_CHn == PWM_CH2)
    {
        PWM->IER        &= PWM_IER_IE2_Disable;  ///< Interrupt enable register 
        PWM->SSR        &= PWM_SSR_SS2_Stop;     ///< Start Stop register 
        PWM->PSR        &= PWM_PSR_PS2_Restart;  ///< Pause register 
        PWM_CH2->IER    = 0;                    ///< Interrupt enable register 
        PWM_CH2->ICR    =  PWM_CHn_ICR_MatchInterruptClear      | 
                           PWM_CHn_ICR_OverflowInterruptClear   | 
                           PWM_CHn_ICR_CaptureInterruptClear;   ///< Interrupt clear register
        PWM_CH2->PR     = 0;                    ///< Prescale register 
        PWM_CH2->MR     = 0;                    ///< Match register 
        PWM_CH2->LR     = 0xFFFFFFFF;           ///< Limit register 
        PWM_CH2->UDMR   = 0;                    ///< Up Dowm mode register
        PWM_CH2->TCMR   = 0;                    ///< Timer Counter mode register
        PWM_CH2->PEEER  = 0;                    ///< PWM output Enable and External input Enable register
        PWM_CH2->CMR    = 0;                    ///< Capture mode register
        PWM_CH2->PDMR   = 0;                    ///< Periodic Mode register
        PWM_CH2->DZER   = 0;                    ///< Dead Zone Enable register
        PWM_CH2->DZCR   = 0;                    ///< Dead Zone Counter register
    }
    else if( PWM_CHn == PWM_CH3 )
    {
        PWM->IER        &= PWM_IER_IE3_Disable;  ///< Interrupt enable register 
        PWM->SSR        &= PWM_SSR_SS3_Stop;     ///< Start Stop register 
        PWM->PSR        &= PWM_PSR_PS3_Restart;  ///< Pause register 
        PWM_CH3->IER    = 0;                    ///< Interrupt enable register 
        PWM_CH3->ICR    =  PWM_CHn_ICR_MatchInterruptClear      | 
                           PWM_CHn_ICR_OverflowInterruptClear   | 
                           PWM_CHn_ICR_CaptureInterruptClear;   ///< Interrupt clear register
        PWM_CH3->MR     = 0;                    ///< Match register 
        PWM_CH3->LR     = 0xFFFFFFFF;           ///< Limit register 
        PWM_CH3->UDMR   = 0;                    ///< Up Dowm mode register
        PWM_CH3->TCMR   = 0;                    ///< Timer Counter mode register
        PWM_CH3->PEEER  = 0;                    ///< PWM output Enable and External input Enable register
        PWM_CH3->CMR    = 0;                    ///< Capture mode register
        PWM_CH3->PDMR   = 0;                    ///< Periodic Mode register
        PWM_CH3->DZER   = 0;                    ///< Dead Zone Enable register
        PWM_CH3->DZCR   = 0;                    ///< Dead Zone Counter register
    }
    else if( PWM_CHn == PWM_CH4 )
    {
        PWM->SSR        &= PWM_IER_IE4_Disable;  ///< Start Stop register 
        PWM->PSR        &= PWM_SSR_SS4_Stop;     ///< Pause register 
        PWM->IER        &= PWM_PSR_PS4_Restart;  ///< Interrupt enable register 
        PWM_CH4->IER    = 0;                    ///< Interrupt enable register 
        PWM_CH4->ICR    =  PWM_CHn_ICR_MatchInterruptClear      | 
                           PWM_CHn_ICR_OverflowInterruptClear   | 
                           PWM_CHn_ICR_CaptureInterruptClear;   ///< Interrupt clear register
        PWM_CH4->PR     = 0;                    ///< Prescale register 
        PWM_CH4->MR     = 0;                    ///< Match register 
        PWM_CH4->LR     = 0xFFFF;               ///< Limit register 
        PWM_CH4->UDMR   = 0;                    ///< Up Dowm mode register
        PWM_CH4->TCMR   = 0;                    ///< Timer Counter mode register
        PWM_CH4->PEEER  = 0;                    ///< PWM output Enable and External input Enable register
        PWM_CH4->CMR    = 0;                    ///< Capture mode register
        PWM_CH4->PDMR   = 0;                    ///< Periodic Mode register
        PWM_CH4->DZER   = 0;                    ///< Dead Zone Enable register
        PWM_CH4->DZCR   = 0;                    ///< Dead Zone Counter register
    }
    else if( PWM_CHn == PWM_CH5 )
    {
        PWM->SSR        &= PWM_IER_IE5_Disable;  ///< Start Stop register 
        PWM->PSR        &= PWM_SSR_SS5_Stop;     ///< Pause register 
        PWM->IER        &= PWM_PSR_PS5_Restart;  ///< Interrupt enable register 
        PWM_CH5->IER    = 0;                    ///< Interrupt enable register 
        PWM_CH5->ICR    =  PWM_CHn_ICR_MatchInterruptClear      |
                           PWM_CHn_ICR_OverflowInterruptClear   | 
                           PWM_CHn_ICR_CaptureInterruptClear;   ///< Interrupt clear register
        PWM_CH5->PR     = 0;                    ///< Prescale register 
        PWM_CH5->MR     = 0;                    ///< Match register 
        PWM_CH5->LR     = 0xFFFFFFFF;           ///< Limit register 
        PWM_CH5->UDMR   = 0;                    ///< Up Dowm mode register
        PWM_CH5->TCMR   = 0;                    ///< Timer Counter mode register
        PWM_CH5->PEEER  = 0;                    ///< PWM output Enable and External input Enable register
        PWM_CH5->CMR    = 0;                    ///< Capture mode register
        PWM_CH5->PDMR   = 0;                    ///< Periodic Mode register
        PWM_CH5->DZER   = 0;                    ///< Dead Zone Enable register
        PWM_CH5->DZCR   = 0;                    ///< Dead Zone Counter register
    }
    else if( PWM_CHn == PWM_CH6 )
    {
        PWM->SSR        &= PWM_IER_IE6_Disable;  ///< Start Stop register 
        PWM->PSR        &= PWM_SSR_SS6_Stop;     ///< Pause register 
        PWM->IER        &= PWM_PSR_PS6_Restart;  ///< Interrupt enable register 
        PWM_CH6->IER    = 0;                    ///< Interrupt enable register 
        PWM_CH6->ICR    =  PWM_CHn_ICR_MatchInterruptClear      | 
                           PWM_CHn_ICR_OverflowInterruptClear   | 
                           PWM_CHn_ICR_CaptureInterruptClear;   ///< Interrupt clear register
        PWM_CH6->PR     = 0;                    ///< Prescale register 
        PWM_CH6->MR     = 0;                    ///< Match register 
        PWM_CH6->LR     = 0xFFFFFFFF;           ///< Limit register 
        PWM_CH6->UDMR   = 0;                    ///< Up Dowm mode register
        PWM_CH6->TCMR   = 0;                    ///< Timer Counter mode register
        PWM_CH6->PEEER  = 0;                    ///< PWM output Enable and External input Enable register
        PWM_CH6->CMR    = 0;                    ///< Capture mode register
        PWM_CH6->PDMR   = 0;                    ///< Periodic Mode register
        PWM_CH6->DZER   = 0;                    ///< Dead Zone Enable register
        PWM_CH6->DZCR   = 0;                    ///< Dead Zone Counter register
    }
    else if( PWM_CHn == PWM_CH7 )
    {
        PWM->SSR        &= PWM_IER_IE7_Disable;  ///< Start Stop register 
        PWM->PSR        &= PWM_SSR_SS7_Stop;     ///< Pause register 
        PWM->IER        &= PWM_PSR_PS7_Restart;  ///< Interrupt enable register 
        PWM_CH7->IER    = 0;                    ///< Interrupt enable register 
        PWM_CH7->ICR    = PWM_CHn_ICR_MatchInterruptClear      | 
                          PWM_CHn_ICR_OverflowInterruptClear   | 
                          PWM_CHn_ICR_CaptureInterruptClear;   ///< Interrupt clear register
        PWM_CH7->PR     = 0;                    ///< Prescale register 
        PWM_CH7->MR     = 0;                    ///< Match register 
        PWM_CH7->LR     = 0xFFFFFFFF;           ///< Limit register 
        PWM_CH7->UDMR   = 0;                    ///< Up Dowm mode register
        PWM_CH7->TCMR   = 0;                    ///< Timer Counter mode register
        PWM_CH7->PEEER  = 0;                    ///< PWM output Enable and External input Enable register
        PWM_CH7->CMR    = 0;                    ///< Capture mode register
        PWM_CH7->PDMR   = 0;                    ///< Periodic Mode register
        PWM_CH7->DZER   = 0;                    ///< Dead Zone Enable register
        PWM_CH7->DZCR   = 0;                    ///< Dead Zone Counter register
    }
}




/**
  * @brief  Start the PWM operation to select PWM channel.
	* @note	The only difference from the PWM_CHn_Start function is that the format of the parameters is different.
	*						PWM_CHn_Start's parameter is in 32-bit format and this function is in PWM_CHn format.
  * @param  PWM_CHn: where n can be (0..7) to select the PWM peripheral.
  * @retval None
  */
void PWM_CHn_Start(PWM_CHn_TypeDef* PWM_CHn) //complete
{
    /* Check the parameters */
    assert_param(IS_PWM_ALL_CH(PWM_CHn));

    /* Set Start Stop register */
    if(PWM_CHn == PWM_CH0) { 
        PWM->SSR |= PWM_SSR_SS0_Start;
    }
    else if(PWM_CHn == PWM_CH1) {
        PWM->SSR |= PWM_SSR_SS1_Start;
    }
    else if(PWM_CHn == PWM_CH2) {
        PWM->SSR |= PWM_SSR_SS2_Start;
    }
    else if(PWM_CHn == PWM_CH3) {
        PWM->SSR |= PWM_SSR_SS3_Start;
    }
    else if(PWM_CHn == PWM_CH4) {
        PWM->SSR |= PWM_SSR_SS4_Start;
    }
    else if(PWM_CHn == PWM_CH5) {
        PWM->SSR |= PWM_SSR_SS5_Start;
    }
    else if(PWM_CHn == PWM_CH6) {
        PWM->SSR |= PWM_SSR_SS6_Start;
    }
    else if(PWM_CHn == PWM_CH7) {
        PWM->SSR |= PWM_SSR_SS7_Start;
    }
}



/**
  * @brief  Start the PWM operation of selected PWM channel.
  * @param  ssr_bit_flag: specifies channels to start PWM operation.
	*          This parameter can be a value less than 0xFF, because there are eight PWM channels.
	*          Set a bit equal to the channel number for which you want to start PWM operation to 1.
  * @retval None
  */
void PWM_Multi_Start(uint32_t ssr_bit_flag) //complete
{
    /* Check the parameters */
    assert_param(IS_SSR_BIT_FLAG(FLAG));

    /* Set Start Stop register */
    PWM->SSR |= ssr_bit_flag;
}



/**
  * @brief  Stop the PWM operation of selected PWM channel.
	* @note	The only difference from the PWM_Multi_Stop function is that the format of the parameters is different.
	*						PWM_Multi_Stop's parameter is in 32-bit format and this function is in PWM_CHn format.
	*						The Timer/Counter is immediately stoped.
  * @param  PWM_CHn: where n can be (0..7) to select the PWM peripheral.
  * @retval None
  */
void PWM_CHn_Stop(PWM_CHn_TypeDef* PWM_CHn) //complete
{
    /* Check the parameters */
    assert_param(IS_PWM_ALL_CH(PWM_CHn));

    /* Reset Start Stop register */
    if(PWM_CHn == PWM_CH0) { 
        PWM->SSR &= PWM_SSR_SS0_Stop;
    }
    else if(PWM_CHn == PWM_CH1) {
        PWM->SSR &= PWM_SSR_SS1_Stop;
    }
    else if(PWM_CHn == PWM_CH2) {
        PWM->SSR &= PWM_SSR_SS2_Stop;
    }
    else if(PWM_CHn == PWM_CH3) {
        PWM->SSR &= PWM_SSR_SS3_Stop;
    }
    else if(PWM_CHn == PWM_CH4) {
        PWM->SSR &= PWM_SSR_SS4_Stop;
    }
    else if(PWM_CHn == PWM_CH5) {
        PWM->SSR &= PWM_SSR_SS5_Stop;
    }
    else if(PWM_CHn == PWM_CH6) {
        PWM->SSR &= PWM_SSR_SS6_Stop;
    }
    else if(PWM_CHn == PWM_CH7) {
        PWM->SSR &= PWM_SSR_SS7_Stop;
    }
}



/**
  * @brief  Stop the PWM operation of selected PWM channel.
  * @param  ssr_bit_flag: specifies channels to stop PWM operation.
	*          This parameter can be a value less than 0xFF, because there are eight PWM channels.
	*          Set a bit equal to the channel number for which you want to stop PWM operation to 1.
  * @retval None
  */
void PWM_Multi_Stop(uint32_t ssr_bit_flag) //complete
{
    /* Check the parameters */
    assert_param(IS_SSR_BIT_FLAG(FLAG));

    /* Reset Start Stop register */
    PWM->SSR &= ~ssr_bit_flag;
}


/**
  * @brief  Pause the PWM operation of the selected PWM channel.
	* @note	The only difference from the PWM_Multi_Pause function is that the format of the parameters is different.
	*						PWM_Multi_Pause's parameter is in 32-bit format and this function is in PWM_CHn format.
	*						The Timer/Counter is paused after Timer/Counter is reached to value of limit register unlike controlling the start/stop register immediately stop.
  * @param  PWM_CHn: where n can be (0..7) to select the PWM peripheral.
  * @retval None
  */
void PWM_CHn_Pause(PWM_CHn_TypeDef* PWM_CHn)
{
    /* Check the parameters */
    assert_param(IS_PWM_ALL_CH(PWM_CHn));

    /* Set Pause register */
    if(PWM_CHn == PWM_CH0) { 
        PWM->PSR |= PWM_PSR_PS0_Pause;
    }
    else if(PWM_CHn == PWM_CH1) {
        PWM->PSR |= PWM_PSR_PS1_Pause;
    }
    else if(PWM_CHn == PWM_CH2) {
        PWM->PSR |= PWM_PSR_PS2_Pause;
    }
    else if(PWM_CHn == PWM_CH3) {
        PWM->PSR |= PWM_PSR_PS3_Pause;
    }
    else if(PWM_CHn == PWM_CH4) {
        PWM->PSR |= PWM_PSR_PS4_Pause;
    }
    else if(PWM_CHn == PWM_CH5) {
        PWM->PSR |= PWM_PSR_PS5_Pause;
    }
    else if(PWM_CHn == PWM_CH6) {
        PWM->PSR |= PWM_PSR_PS6_Pause;
    }
    else if(PWM_CHn == PWM_CH7) {
        PWM->PSR |= PWM_PSR_PS7_Pause;
    }
}


/**
  * @brief  Pause the PWM operation of the selected PWM channel.
  * @param  psr_bit_flag: specifies channels to pause PWM operation.
	*          This parameter can be a value less than 0xFF, because there are eight PWM channels.
	*          Set a bit equal to the channel number for which you want to pause PWM operation to 1.
  * @retval None
  */
void PWM_Multi_Pause(uint32_t psr_bit_flag)
{
    /* Check the parameters */
    assert_param(IS_PSR_BIT_FLAG(FLAG));

		/* Set the Pause */
    PWM->PSR |= psr_bit_flag;
}


/**
  * @brief  Restart the PWM operation of the selected PWM channel.
	* @note	The only difference from the PWM_Multi_Restart function is that the format of the parameters is different.
	*						PWM_Multi_Restart's parameter is in 32-bit format and this function is in PWM_CHn format.
  * @param  PWM_CHn: where n can be (0..7) to select the PWM peripheral.
  * @retval None
  */
void PWM_CHn_Restart(PWM_CHn_TypeDef* PWM_CHn)
{
    /* Check the parameters */
    assert_param(IS_PWM_ALL_CH(PWM_CHn));

    /* Reset Pause register */
    if(PWM_CHn == PWM_CH0) { 
        PWM->PSR &= PWM_PSR_PS0_Restart;
    }
    else if(PWM_CHn == PWM_CH1) {
        PWM->PSR &= PWM_PSR_PS1_Restart;
    }
    else if(PWM_CHn == PWM_CH2) {
        PWM->PSR &= PWM_PSR_PS2_Restart;
    }
    else if(PWM_CHn == PWM_CH3) {
        PWM->PSR &= PWM_PSR_PS3_Restart;
    }
    else if(PWM_CHn == PWM_CH4) {
        PWM->PSR &= PWM_PSR_PS4_Restart;
    }
    else if(PWM_CHn == PWM_CH5) {
        PWM->PSR &= PWM_PSR_PS5_Restart;
    }
    else if(PWM_CHn == PWM_CH6) {
        PWM->PSR &= PWM_PSR_PS6_Restart;
    }
    else if(PWM_CHn == PWM_CH7) {
        PWM->PSR &= PWM_PSR_PS7_Restart;
    }
}





/**
  * @brief  		Restart the PWM operation of selected PWM channel.
  * @param	psr_bit_flag: specifies channel to restart PWM operation.
	*          This parameter can be a value less than 0xFF, because there are eight PWM channels.
	*          Set a bit equal to the channel number for which you want to restart PWM operation to 1.
  * @retval None
  */
void PWM_Multi_Restart(uint32_t psr_bit_flag)
{
    /* Check the parameters */
    assert_param(IS_PSR_BIT_FLAG(FLAG));

		/* Reset the Pause register */
    PWM->PSR &= ~psr_bit_flag;
}



/**
  * @}
  */






/** @defgroup PWM_Group2 Interrupts and flags management
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
  * @brief  Configures the global Interrupt enable/disable of selected PWM channel.
	* @note	PWM_CHn_IntConfig is a function to check match, limit, and capture interrupts for one channel, and this function checks the global interrupt for each channel
	*						In the reference manual, PWM_CHn_IntConfig controls the registers belonging to the PWM Channel-n Registers,
	*						and in this case controls the registers belonging to the PWM Common Registers.
  * @param  PWM_CHn: where n can be (0..7) to select the PWM peripheral.
  * @param  state:  specifies the value to be set to the selected PWM channel.
  *          This parameter can be one of the FunctionalState enum values:
  *            @arg Disable: to disable the interrupt.
  *            @arg Enable: to enable the interrupt.
  * @retval None
  */
void PWM_IntConfig(PWM_CHn_TypeDef* PWM_CHn, FunctionalState state) //complete
{
    /* Check the parameter */
    assert_param(IS_PWM_ALL_CH(PWM_CHn));
    
	

    /* Stop PWM_CHn */
    PWM_CHn_Stop(PWM_CHn);

		/* Set Interrupt Enable*/
    if(state == ENABLE)
    {
        if(PWM_CHn == PWM_CH0) {  
            PWM->IER |= PWM_IER_IE0_Enable;    
        }
        else if(PWM_CHn == PWM_CH1) {
            PWM->IER |= PWM_IER_IE1_Enable;
        }
        else if(PWM_CHn == PWM_CH2) {
            PWM->IER |= PWM_IER_IE2_Enable;
        } 
        else if(PWM_CHn == PWM_CH3) {
            PWM->IER |= PWM_IER_IE3_Enable;
        }
        else if(PWM_CHn == PWM_CH4) {
            PWM->IER |= PWM_IER_IE4_Enable;
        }
        else if(PWM_CHn == PWM_CH5) {
            PWM->IER |= PWM_IER_IE5_Enable;
        }
        else if(PWM_CHn == PWM_CH6) {
            PWM->IER |= PWM_IER_IE6_Enable;
        }
        else if(PWM_CHn == PWM_CH7) {
            PWM->IER |= PWM_IER_IE7_Enable;
        }
    }
		
		/* Set Interrupt disable */
    else
    {
        if(PWM_CHn == PWM_CH0) { 
            PWM->IER &= PWM_IER_IE0_Disable;
        }
        else if(PWM_CHn == PWM_CH1) {
            PWM->IER &= PWM_IER_IE1_Disable;
        }
        else if(PWM_CHn == PWM_CH2) {
            PWM->IER &= PWM_IER_IE2_Disable;
        }
        else if(PWM_CHn == PWM_CH3) {
            PWM->IER &= PWM_IER_IE3_Disable;
        }
        else if(PWM_CHn == PWM_CH4) {
            PWM->IER &= PWM_IER_IE4_Disable;
        }
        else if(PWM_CHn == PWM_CH5) {
            PWM->IER &= PWM_IER_IE5_Disable;
        }
        else if(PWM_CHn == PWM_CH6) {
            PWM->IER &= PWM_IER_IE6_Disable;
        }
        else if(PWM_CHn == PWM_CH7) {
            PWM->IER &= PWM_IER_IE7_Disable;
        }
    }
}
 

/**
  * @brief  		Get the global Interrupt enable/disable status of selected PWM channel.
  * @param  PWM_CHn: where n can be (0..7) to select the PWM peripheral.
  * @retval  	The interrupt status value of format in RESET(0) or SET(1)
  */
FlagStatus PWM_GetIntEnableStatus(PWM_CHn_TypeDef* PWM_CHn) //complete
{
    /* Check the parameters */
    assert_param(IS_PWM_ALL_CH(PWM_CHn));

	
		/* Return the Interrupt Enable status */
    if(PWM_CHn == PWM_CH0) { 
        return (FlagStatus)((PWM->IER & 0x01) >> 0);
    }
    else if(PWM_CHn == PWM_CH1) {
        return (FlagStatus)((PWM->IER & 0x02) >> 1);
    }
    else if(PWM_CHn == PWM_CH2) {
        return (FlagStatus)((PWM->IER & 0x04) >> 2);
    }
    else if(PWM_CHn == PWM_CH3) {
        return (FlagStatus)((PWM->IER & 0x08) >> 3);
    }
    else if(PWM_CHn == PWM_CH4) {
        return (FlagStatus)((PWM->IER & 0x10) >> 4);
    }
    else if(PWM_CHn == PWM_CH5) {
        return (FlagStatus)((PWM->IER & 0x20) >> 5);
    }
    else if(PWM_CHn == PWM_CH6) {
        return (FlagStatus)((PWM->IER & 0x40) >> 6);
    }
    else if(PWM_CHn == PWM_CH7) {
        return (FlagStatus)((PWM->IER & 0x80) >> 7);    
    }
    
    return RESET;
}



/**
  * @brief  Configures the Interrupt enable/disable of selected PWM channel.
	* @note	To enable this interrupt, the corresponding channel must be enabled in PWM_IntConfig().
  * @param  PWM_CHn: where n can be (0..7) to select the PWM peripheral.
  * @param  PWM_CHn_IER: specifies the channel bits to be configured.
  *          This parameter can be a value less than 0x7. Because PWM_CHn_IER only uses bits 0, 1, and 2.
  *          [0]: MI - Match Interrupt
  *          [1]: OI - Overflow Interrupt
  *          [2]: CI - Capture Interrupt
  * @param  state:  specifies the value to be set to the selected channel.
  *          This parameter can be one of the FunctionalState enum values:
  *            @arg Disable: to disable the interrupt to selected PWM channel's pin
  *            @arg Enable: to enable the interrupt to selected PWM channel's pin
  * @retval None
  */
void PWM_CHn_IntConfig(PWM_CHn_TypeDef* PWM_CHn, uint32_t PWM_CHn_IER, FunctionalState state) //complete
{
    /* Check the parameters */
    assert_param(IS_PWM_ALL_CH(PWM_CHn));
	  assert_param(IS_PWM_CHn_IER(PWM_CHn_IER));
    

    /* Stop PWM_CHn */
    PWM_CHn_Stop(PWM_CHn);
		
		/* Set the Interrupt enable */
    if(state == ENABLE)
        PWM_CHn->IER |= PWM_CHn_IER;
    
		/* Set Interrupt disable */
		else 
        PWM_CHn->IER &= ~PWM_CHn_IER;
}


/**
  * @brief  Get the Interrupt enable/disable status of selected PWM channel.
  * @param  PWM_CHn: where n can be (0..7) to select the PWM peripheral.
  * @retval The interrupt status value.
	*          The format of this value is 32bits, but only [2:0]bit is a valid value.
  *          [0]: MI - Match Interrupt
  *          [1]: OI - Overflow Interrupt
  *          [2]: CI - Capture Interrupt
  */
uint32_t PWM_CHn_GetIntEnableStatus(PWM_CHn_TypeDef* PWM_CHn) //complete
{
    /* Check the parameters */
    assert_param(IS_PWM_ALL_CH(PWM_CHn));

		/* Return the Interrupt Enable status */
    return PWM_CHn->IER;
}


/**
  * @brief  Get the Interrupt flag of selected PWM Channel.
  * @param  PWM_CHn: where n can be (0..7) to select the PWM peripheral.
  * @retval The interrupt Flag value
  * @retval The interrupt status value
  *          The format of this value is 32bits, but only [0:2]bit is a valid value.
  *          [0]: MI - Match Interrupt
  *          [1]: OI - Overflow Interrupt
  *          [2]: CI - Capture Interrupt
  */
uint32_t PWM_CHn_GetIntFlagStatus(PWM_CHn_TypeDef* PWM_CHn) //complete
{
    /* Check the parameters */
    assert_param(IS_PWM_ALL_CH(PWM_CHn));

		/* Return the Interrupt flag */
    return PWM_CHn->IR;
}



/**
  * @brief  Clear the Interrupt flag of selected PWM channel.
	* @note	In case of global interrupt, it automatically becomes 0 when all interrupts of the channel are cleared.
  * @param  PWM_CHn: where n can be (0..7) to select the PWM peripheral.
  * @param  PWM_CHn_ICR: specifies the value to be set to the selected channel.
  *          This parameter can be a value less than 0x7. Because PWM_CHn_ICR only uses bits 0, 1, and 2.
  *          [0]: MI - Match Interrupt
  *                      0 : No action.
  *                      1 : Match interrupt is cleared.
  *          [1]: OI - Overflow Interrupt
  *                      0 : No action.
  *                     1 : Overflow Interrupt is cleared.
  *          [2]: CI - Capture Interrupt
  *                      0 : No action.
  *                      1 : Capture Interrupt is cleared.
  *  
  * @retval None
  */
void PWM_CHn_ClearInt(PWM_CHn_TypeDef* PWM_CHn, uint32_t PWM_CHn_ICR)
{
    /* Check the parameters */
    assert_param(IS_PWM_ALL_CH(PWM_CHn));
    assert_param(IS_PWM_CHn_IntClearFlag(IntClearFlag));

		/* Set the Interrupt clear */
    PWM_CHn->ICR = PWM_CHn_ICR;
}


/**
  * @}
  */







/** @defgroup PWM_Group3 TimeBase management
 *  @brief   TimeBase management
 *
@verbatim   
 ===============================================================================
                  TimeBase management
 ===============================================================================  

@endverbatim
  * @{
  */



/**
  * @brief  Get the Timer/Counter value of selected PWM channel.
	* @note	The Timer/Counter is incremented every Prescale cycles. When the Timer/Counter is
	*						reached to value of match register, the match interrupt is occurred and PWM
	*						output waveform becomes 0. When the Timer/Counter is reached to the value of limit
	*						register, the overflow interrupt is occurred, the Timer/Counter is reset as 0. It is a read-only register.
  * @param  PWM_CHn: where n can be (0..7) to select the PWM peripheral.
  * @retval The Timer/Counter register value.
  */
uint32_t PWM_CHn_GetTCR(PWM_CHn_TypeDef* PWM_CHn) 
{
    /* Check the parameters */
    assert_param(IS_PWM_ALL_CH(PWM_CHn));

		/* Return the Timer/Counter Register value */
    return PWM_CHn->TCR;
}


/**
  * @brief  Get the Prescale Counter value of selected PWM channel.
	* @note	The Prescale Counter is incremented to the value stored in Prescale Register. When the Prescale Counter is
	*						reached to Prescale value, the Timer Counter is incremented and the Prescale Counter is reset as 0.
	*						It is a read-only register.
  * @param  PWM_CHn: where n can be (0..7) to select the PWM peripheral.
  * @retval The prescale counter value of which the format is 32bits, but only [5:0]bits are the valid value.
  */
uint32_t PWM_CHn_GetPCR(PWM_CHn_TypeDef* PWM_CHn) //complete
{
    /* Check the parameters */
    assert_param(IS_PWM_ALL_CH(PWM_CHn));

		/* Return the Prescale Counter Register value */
    return PWM_CHn->PCR;
}


/**
  * @brief			Get the Prescale value of selected PWM channel.
  * @param	PWM_CHn: where n can be (0..7) to select the PWM peripheral.
	* @retval		The prescale register value of which the format is 32bits, but only [5:0]bits are the valid value.
  */
uint32_t PWM_CHn_GetPR(PWM_CHn_TypeDef* PWM_CHn) //complete
{
    /* Check the parameters */
    assert_param(IS_PWM_ALL_CH(PWM_CHn));

		/* Return the Prescale Register value */
    return PWM_CHn->PR;
}


/**
  * @brief		Set the specified value to Prescale value of selected PWM channel.
	* @note		The Prescale Counter is incremented when the Prescale Counter is reached to the Prescale value.				
  * @param	PWM_CHn: where n can be (0..7) to select the PWM peripheral.
  * @param	PR: specifies the value to be written to the selected channel.
	*					This parameter can be a value less than 0x3F. Because PWM_CHn_PR only uses [5:0]bits.
  * @retval	None
  */
void PWM_CHn_SetPR(PWM_CHn_TypeDef* PWM_CHn, uint32_t PR) //complete
{
    /* Check the parameters */
    assert_param(IS_PWM_ALL_CH(PWM_CHn));
    assert_param(IS_PWM_PR_FILTER(PR));

		/* Set the Prescale Register value */
    PWM_CHn->PR = PR;
}


/**
  * @brief		Get the Match value of the selected PWM channel.
  * @param	PWM_CHn: where n can be (0..7) to select the PWM peripheral.
  * @retval	The Match value.
  */
uint32_t PWM_CHn_GetMR(PWM_CHn_TypeDef* PWM_CHn) //complete
{
    /* Check the parameters */
    assert_param(IS_PWM_ALL_CH(PWM_CHn));

		/* Return the Match Register value */
    return PWM_CHn->MR;
}


/**
  * @brief		Set the specified value to Match value of selected PWM channel.
	* @note		The Match Register can generate a match interrupt and PWM output waveform 
	*							becomes 0 when the Timer/Counter is reached to the Match Regiset. Match register should
	*							be smaller than limit register. If not, match interrupt is not occurred and
	*							PWM output waveform is always 1.
  * @param	PWM_CHn: where n can be (0..7) to select the PWM peripheral.
  * @param	MR: specifies the value to be written to selected channel.
  * @retval	None
  */
void PWM_CHn_SetMR(PWM_CHn_TypeDef* PWM_CHn, uint32_t MR) //complete
{
    /* Check the parameters */
    assert_param(IS_PWM_ALL_CH(PWM_CHn));

		/* Set the Match Register value */
    PWM_CHn->MR = MR;
}


/**
  * @brief		Get the Limit value of the selected channel.
  * @param	PWM_CHn: where n can be (0..7) to select the PWM peripheral.
  * @retval	The Limit value.
  */
uint32_t PWM_CHn_GetLR(PWM_CHn_TypeDef* PWM_CHn) //complete
{
    /* Check the parameters */
    assert_param(IS_PWM_ALL_CH(PWM_CHn));

		/* Return the Limit Register value */
    return PWM_CHn->LR;
}


/**
  * @brief		Set the Limit value of selected channel.
	* @note		The Limit Register can generate an overflow interrupt and PWM output waveform becomes 1 when the Timer/Count is reached to the Limit Regiset.
	* 						Match register should	be smaller than limit register. If not, match interrupt is not occurred and PWM output waveform is always 1.
  * @param	PWM_CHn: where n can be (0..7) to select the PWM peripheral.
  * @param	LR: specifies the Limit value of the selected PWM channel.
  * @retval	None
  */
void PWM_CHn_SetLR(PWM_CHn_TypeDef* PWM_CHn, uint32_t LR) //complete
{
    /* Check the parameters */
    assert_param(IS_PWM_ALL_CH(PWM_CHn));

		/* Set the Limit Register value */
    PWM_CHn->LR = LR;
}

/**
  * @brief		Check the Up-down mode.
  * @param	PWM_CHn: where n can be (0..7) to select the PWM peripheral.
  * @retval	The Up-down mode value of which the format is 32bits, but only [0]bit is a valid value.
	*					0x0ul : Timer/Counter runs up count.
  *					0x1ul : Timer/Counter runs down count.
  */
uint32_t PWM_CHn_GetUDMR(PWM_CHn_TypeDef* PWM_CHn) //complete
{
    /* Check the parameters */
    assert_param(IS_PWM_ALL_CH(PWM_CHn));

		/* Return the Up-down Mode Register value */
    return PWM_CHn->UDMR;
}


/**
  * @brief		Set the Up-down mode value of the selected PWM channel.
  * @param	PWM_CHn: where n can be (0..7) to select the PWM peripheral.
  * @param	UDMR: specifies the Up-down mode value.
  *		    	This parameter can be a value of PWM_CHn_UDMR_UpCount(0x0ul) or PWM_CHn_UDMR_DownCount(0x1ul), only uses [0]bit.
  * @retval	None
  */
void PWM_CHn_SetUDMR(PWM_CHn_TypeDef* PWM_CHn, uint32_t UDMR) //complete
{
    /* Check the parameters */
    assert_param(IS_PWM_ALL_CH(PWM_CHn));
    assert_param(IS_PWM_CHn_UDMR(UDMR));
		
		/* Set the Up-down Mode Register value */
    PWM_CHn->UDMR = UDMR;
}

/**
  * @brief		Check whether the specfied Periodic Mode is set or not. 
  * @param	PWM_CHn: where n can be (0..7) to select the PWM peripheral.
  * @retval  The Periodic Mode value of which the format is 32bits, but only [0]bit is a valid value.
	*					0x0ul : Periodic mode.
  *					0x1ul : One-shot mode. 
  */
uint32_t PWM_CHn_GetPDMR(PWM_CHn_TypeDef* PWM_CHn) //complete
{
    /* Check the parameters */
    assert_param(IS_PWM_ALL_CH(PWM_CHn));
		
		/* Return the Periodic register value */
    return PWM_CHn->PDMR;
}


/**
  * @brief  	Sets or Clears a Periodic Mode of the selected PWM channel.
  * @note		Periodic mode : When the timer/counter is reached to the limit register, the timer/counter returns to 0 and then continues counting periodically.
  * @note		One-shot mode : When the timer/counter is reached to the limit register, the timer/counter returns to 0 and then stops counting.
  * @param	PWM_CHn: where n can be (0..7) to select the PWM peripheral.
  * @param	PDMR: specfies the value to be set to Periodic Mode of the selected channel.
  *		     		This parameter can be a value of PWM_CHn_PDMR_Periodic(0x1ul) or PWM_CHn_PDMR_Oneshot(0x0ul), only uses [0]bit.
	*						0x0ul : Periodic mode. 
  *						0x1ul : One-shot mode. 
  * @retval 	None
  */
void PWM_CHn_SetPDMR(PWM_CHn_TypeDef* PWM_CHn, uint32_t PDMR) //complete
{
    /* Check the parameters */
    assert_param(IS_PWM_ALL_CH(PWM_CHn));
    assert_param(IS_PWM_CHn_PDMR(PDMR));

		/* Set the periodic mode register value */
    PWM_CHn->PDMR = PDMR; 
	}

/**
  * @}
  */




/** @defgroup PWM_Group4 Timer/Counter Mode management
 *  @brief   Timer/Counter Mode management
 *
@verbatim   
 ===============================================================================
                  Timer/Counter Mode management
 ===============================================================================  

@endverbatim
  * @{
  */




/**
  * @brief  Initializes the PWM Timer mode Unit peripheral according to the specified
  *         parameters in the PWM_TimerModeInitStruct.
  * @param  PWM_CHn: where n can be (0..7) to select the PWM peripheral.
  * @param  PWM_TimerModeInitStruct: pointer to a PWM_TimerModeInitTypeDef structure that contains
  *         the configuration information for the specified PWM peripheral.
  * @retval None
  */
void PWM_TimerModeInit(PWM_CHn_TypeDef* PWM_CHn, PWM_TimerModeInitTypeDef* PWM_TimerModeInitStruct) //complet
{
    /* Check the parameters */
    assert_param(IS_PWM_ALL_CH(PWM_CHn));
    assert_param(IS_PWM_PR_FILTER(PWM_TimerModeInitStruct->PWM_CHn_PR));
    assert_param(IS_PWM_MR_FILTER(PWM_CHn, PWM_TimerModeInitStruct->PWM_CHn_MR));
    assert_param(IS_PWM_LR_FILTER(PWM_CHn, PWM_TimerModeInitStruct->PWM_CHn_LR));
    assert_param(IS_PWM_CHn_UDMR(PWM_TimerModeInitStruct->PWM_CHn_UDMR));
    assert_param(IS_PWM_CHn_PDMR(PWM_TimerModeInitStruct->PWM_CHn_PDMR));

    /* Select Timer/Counter mode as Timer mode */ 
    PWM_CHn->TCMR = PWM_CHn_TCMR_TimerMode;
    /* Set Prescale register value */
    PWM_CHn->PR = PWM_TimerModeInitStruct->PWM_CHn_PR;
    /* Set Match register value */
    PWM_CHn->MR = PWM_TimerModeInitStruct->PWM_CHn_MR;
    /* Set Limit register value */
    PWM_CHn->LR = PWM_TimerModeInitStruct->PWM_CHn_LR;
    /* Select Up-down mode */
    PWM_CHn->UDMR = PWM_TimerModeInitStruct->PWM_CHn_UDMR;
    /* Select Periodic mode */ 
    PWM_CHn->PDMR = PWM_TimerModeInitStruct->PWM_CHn_PDMR;
}






/**
  * @brief		Initializes the PWM Counter Mode Unit peripheral according to the specified
  *         parameters in the PWM_CounterModeInitStruct.
  * @param	PWM_CHn: where n can be (0..7) to select the PWM peripheral.
  * @param	PWM_CounterModeInitStruct: pointer to a PWM_CounterModeInitTypeDef structure that contains
  *         the configuration information for the specified PWM peripheral.
  * @retval	None
  */
void PWM_CounterModeInit(PWM_CHn_TypeDef* PWM_CHn, PWM_CounterModeInitTypeDef* PWM_CounterModeInitStruct) //complete
{
    /* Check the parameters */
    assert_param(IS_PWM_ALL_CH(PWM_CHn));
    assert_param(IS_PWM_PR_FILTER(PWM_CounterModeInitStruct->PWM_CHn_PR));
    assert_param(IS_PWM_MR_FILTER(PWM_CHn, PWM_CounterModeInitStruct->PWM_CHn_MR));
    assert_param(IS_PWM_LR_FILTER(PWM_CHn, PWM_CounterModeInitStruct->PWM_CHn_LR));
    assert_param(IS_PWM_CHn_UDMR(PWM_CounterModeInitStruct->PWM_CHn_UDMR));
    assert_param(IS_PWM_CHn_PDMR(PWM_CounterModeInitStruct->PWM_CHn_PDMR));
    assert_param(IS_PWM_CHn_TCMR(PWM_CounterModeInitStruct->PWM_CHn_TCMR));
    assert_param(IS_PWM_CHn_PEEER(PWM_CounterModeInitStruct->PWM_CHn_PEEER));

    /* Set Match register value */
    PWM_CHn->MR = PWM_CounterModeInitStruct->PWM_CHn_MR;
    /* Set Limit register value */
    PWM_CHn->LR = PWM_CounterModeInitStruct->PWM_CHn_LR;
    /* Select Up-down mode */
    PWM_CHn->UDMR = PWM_CounterModeInitStruct->PWM_CHn_UDMR;
    /* Select Periodic mode */ 
    PWM_CHn->PDMR = PWM_CounterModeInitStruct->PWM_CHn_PDMR;
    /* Select Counter mode */ 
    PWM_CHn->TCMR = PWM_CounterModeInitStruct->PWM_CHn_TCMR;
    /* Enable external input */
    PWM_CHn->PEEER = PWM_CHn_PEEER_ExtEnable; 
}



/**
  * @brief		Check the Timer/Counter mode of the selected PWM channel.
  * @param	PWM_CHn: where n can be (0..7) to select the PWM peripheral.
  * @retval	The Timer/Counter mode value of which format is 32bits, but only [1:0]bits are the valid value.
	* 				@arg 00 : Timer mode.
	* 				@arg 01 : Counter mode with counting driven by rising edge external input .
	* 				@arg 10 : Counter mode with counting driven by falling edge external input.
	* 				@arg 11 : Counter mode with counting driven by rising and falling edge external input.
  */
uint32_t PWM_CHn_GetTCMR(PWM_CHn_TypeDef* PWM_CHn) //complete
{
    /* Check the parameters */
    assert_param(IS_PWM_ALL_CH(PWM_CHn));

		/* Return the Timer/Counter Mode Register */
    return PWM_CHn->TCMR;
}

/**
  * @brief		Set the mode value to Timer/Counter mode to select PWM channel.
  * @param	PWM_CHn: where n can be (0..7) to select the PWM peripheral.
  * @param	TCMR: specfies the value to be set to Timer/Counter mode to selected channel.
	*       	This parameter can be a value of following text. This register only uses [1:0]bits.
	* 					@arg PWM_CHn_TCMR_TimerMode		         	(00): Timer mode.
	*					@arg PWM_CHn_TCMR_RisingCounterMode	(01): Counter mode with counting driven by rising edge external input .
	*					@arg PWM_CHn_TCMR_FallingCounterMode	(10): Counter mode with counting driven by falling edge external input.
	*					@arg PWM_CHn_TCMR_BothCounterMode   (10): Counter mode with counting driven by rising and falling edge external input.
	*
  * @retval None
  */
void PWM_CHn_SetTCMR(PWM_CHn_TypeDef* PWM_CHn, uint32_t TCMR) //complete
{
    /* Check the parameters */
    assert_param(IS_PWM_ALL_CH(PWM_CHn));
    assert_param(IS_PWM_CHn_TCMR(TCMR));

		/* Set the Timer/Counter mode register value */
    PWM_CHn->TCMR = TCMR;
}

/**
  * @}
  */







/** @defgroup PWM_Group5 Capture Mode management
 *  @brief   Capture Mode management
 *
@verbatim   
 ===============================================================================
                  Capture Mode management
 ===============================================================================  

@endverbatim
  * @{
  */


void PWM_CaptureModeInit(PWM_CHn_TypeDef* PWM_CHn, PWM_CaptureModeInitTypeDef* PWM_CaptureModeInitStruct) //complete
{
    /* Check the parameters */
    assert_param(IS_PWM_ALL_CH(PWM_CHn));
    assert_param(IS_PWM_PR_FILTER(PWM_CaptureModeInitStruct->PWM_CHn_PR));
    assert_param(IS_PWM_MR_FILTER(PWM_CHn, PWM_CaptureModeInitStruct->PWM_CHn_MR));
    assert_param(IS_PWM_LR_FILTER(PWM_CHn, PWM_CaptureModeInitStruct->PWM_CHn_LR));
    assert_param(IS_PWM_CHn_UDMR(PWM_CaptureModeInitStruct->PWM_CHn_UDMR));
    assert_param(IS_PWM_CHn_PDMR(PWM_CaptureModeInitStruct->PWM_CHn_PDMR));
    assert_param(IS_PWM_CHn_CMR(PWM_CaptureModeInitStruct->PWM_CHn_CMR));
    
    /* Select Timer/Counter mode as Timer mode */ 
    PWM_CHn->TCMR = PWM_CHn_TCMR_TimerMode;
    /* Set Prescale register value */
    PWM_CHn->PR = PWM_CaptureModeInitStruct->PWM_CHn_PR;
    /* Set Match register value */
    PWM_CHn->MR = PWM_CaptureModeInitStruct->PWM_CHn_MR;
    /* Set Limit register value */
    PWM_CHn->LR = PWM_CaptureModeInitStruct->PWM_CHn_LR;
    /* Select Up-down mode */
    PWM_CHn->UDMR = PWM_CaptureModeInitStruct->PWM_CHn_UDMR;
    /* Select Periodic mode */ 
    PWM_CHn->PDMR = PWM_CaptureModeInitStruct->PWM_CHn_PDMR;
    /* Select Capture mode */
    PWM_CHn->CMR = PWM_CaptureModeInitStruct->PWM_CHn_CMR;
    /* External input enable */
    PWM_CHn->PEEER = PWM_CHn_PEEER_ExtEnable;
}


uint32_t PWM_CHn_GetCMR(PWM_CHn_TypeDef* PWM_CHn) //complete
{
    /* Check the parameters */
    assert_param(IS_PWM_ALL_CH(PWM_CHn));
	
    return PWM_CHn->CMR;
}

void PWM_CHn_SetCMR(PWM_CHn_TypeDef* PWM_CHn, uint32_t CMR) //complete
{
    /* Check the parameters */
    assert_param(IS_PWM_ALL_CH(PWM_CHn));
    assert_param(IS_PWM_CHn_CMR(CMR));

    PWM_CHn->CMR = CMR;
}

uint32_t PWM_CHn_GetCR(PWM_CHn_TypeDef* PWM_CHn)
{
    /* Check the parameters */
    assert_param(IS_PWM_ALL_CH(PWM_CHn));

    return PWM_CHn->CR;
}

/**
  * @}
  */









/** @defgroup PWM_Group6 Dead Zone Mode management
 *  @brief   Dead Zone Mode management
 *
@verbatim   
 ===============================================================================
                  Dead Zone Mode management
 ===============================================================================  

@endverbatim
  * @{
  */





/**
  * @brief		Initializes the PWM Deadzone Mode Unit peripheral according to the specified
  *         parameters in the PWM_DeadzoneModeInitStruct.
  * @param	PWM_CHn: where n can be (0..7) to select the PWM peripheral.
  * @param	PWM_DeadzoneModeInitStruct: pointer to a PWM_DeadzoneModeInitTypDef structure that contains
  *         the configuration information for the specified PWM peripheral.
  * @retval	None
  */
void PWM_DeadzoneModeInit(PWM_CHn_TypeDef* PWM_CHn, PWM_DeadzoneModeInitTypDef* PWM_DeadzoneModeInitStruct) //complete
{
    /* Check the parameters */
    assert_param(IS_PWM_ALL_CH(PWM_CHn));
    assert_param(IS_PWM_PR_FILTER(PWM_DeadzoneModeInitStruct->PWM_CHn_PR));
    assert_param(IS_PWM_MR_FILTER(PWM_CHn, PWM_DeadzoneModeInitStruct->PWM_CHn_MR));
    assert_param(IS_PWM_LR_FILTER(PWM_CHn, PWM_DeadzoneModeInitStruct->PWM_CHn_LR));
    assert_param(IS_PWM_CHn_UDMR(PWM_DeadzoneModeInitStruct->PWM_CHn_UDMR));
    assert_param(IS_PWM_CHn_PDMR(PWM_DeadzoneModeInitStruct->PWM_CHn_PDMR));
    assert_param(IS_PWM_Deadznoe(PWM_CHn));

    /* Select Timer/Counter mode as Timer mode */ 
    PWM_CHn->TCMR = PWM_CHn_TCMR_TimerMode; 
    /* Set Prescale register value */
    PWM_CHn->PR = PWM_DeadzoneModeInitStruct->PWM_CHn_PR;
    /* Set Match register value */
    PWM_CHn->MR = PWM_DeadzoneModeInitStruct->PWM_CHn_MR;
    /* Set Limit register value */
    PWM_CHn->LR = PWM_DeadzoneModeInitStruct->PWM_CHn_LR;
    /* Select Up-down mode */
    PWM_CHn->UDMR = PWM_DeadzoneModeInitStruct->PWM_CHn_UDMR;
    /* Select Periodic mode */ 
    PWM_CHn->PDMR = PWM_DeadzoneModeInitStruct->PWM_CHn_PDMR;
    /* Enable Dead Zone generation */
    PWM_CHn->DZER = PWM_CHn_DZER_Enable; 
    /* Set Dead Zone Counter */
    PWM_CHn->DZCR = PWM_DeadzoneModeInitStruct->PWM_CHn_DZCR;
}

/**
  * @brief		Check whether the specfied Dead Zone Enable is set or not.
  * @param PWM_CHn: where n can be (0..7) to select the PWM peripheral.
  * @retval 	The Dead Zone Enable value of which the format is 32bits, but only [0]bit is a valid value.
  */
uint32_t PWM_CHn_GetDZER(PWM_CHn_TypeDef* PWM_CHn) //complete
{
    /* Check the parameters */
    assert_param(IS_PWM_ALL_CH(PWM_CHn));
		
		/* Return the Dead Zone Enable Register value */
    return PWM_CHn->DZER;
}


/**
  * @brief		Set the enable/disable to dead zone mode to select PWM channel.
  * @note		If dead zone mode is enabled on one channel, the inverted waveform is generated one the pair channel.
  *							Channel 0 and 1 are a pair, channel 2 and 3 are a pair, channel 4 and 5 are a pair, and channel 6 and 7 are a pair.
  *             	If channels in a pair dead zone generation are enabled both, all outputs are 0.
  *             	At this time, the copied waveform has a reversed waveform delayed by a dead zone counter value.
  * @param	PWM_CHn: where n can be (0..7) to select the PWM peripheral.
  * @param	DZER: specfies the value to be set to Dead zone counter to selected channel.
  *		    	This parameter can be a value of PWM_CHn_DZER_Enable(0x1ul) or PWM_CHn_DZER_Disable(0x0ul), only uses [0]bit.
  * @retval	None
  */
void PWM_CHn_SetDZER(PWM_CHn_TypeDef* PWM_CHn, uint32_t DZER) //complete                                                      
{
    /* Check the parameters */
    assert_param(IS_PWM_ALL_CH(PWM_CHn));
    assert_param(IS_PWM_CHn_DZER(DZER));

		/* Set the Dead Zone Enable Register value */
    PWM_CHn->DZER = DZER;
}



/**
  * @brief		Gets a  Dead Zone Counter value of the selected PWM channel.
  * @param	PWM_CHn: where n can be (0..7) to select the PWM peripheral.
  * @retval	The Dead Zone Counter value.
  */
uint32_t PWM_CHn_GetDZCR(PWM_CHn_TypeDef* PWM_CHn) //complete
{
    /* Check the parameters */
    assert_param(IS_PWM_ALL_CH(PWM_CHn));
		
	 /* Return the Dead Zone Counter Register value */
   return PWM_CHn->DZCR;
}


/**
  * @brief		Sets the specified value to Dead Zone Counter value of the selected PWM channel.
  * @note		Delay is generated by the value set in Dead zone counter when PWM waveform is rising and falling in dead zone mode.
  * 						It blocks the section where two waveforms are 1.
	*        			For dead zone mode information, please refer to PWM_CHn_SetDZER().
  * @param	PWM_CHn: where n can be (0..7) to select the PWM peripheral.
  * @param	DZCR: specfies the value to be written to Dead Zone Counter of the selected channel.
  *					This parameter can be a value less than 0x3FF, only uses [9:0]bits.
  * @retval	None
  */
void PWM_CHn_SetDZCR(PWM_CHn_TypeDef* PWM_CHn, uint32_t DZCR) //complete
{
    /* Check the parameters */
    assert_param(IS_PWM_ALL_CH(PWM_CHn));
    assert_param(IS_PWM_CHn_DZCR_FILTER(DZCR));

		/* Set the Dead Zone Counter Register value */
    PWM_CHn->DZCR = DZCR; 
}

/**
  * @}
  */







/** @defgroup PWM_Group7 PWM Output management
 *  @brief  PWM Output management
 *
@verbatim   
 ===============================================================================
                  PWM Output management
 ===============================================================================  

@endverbatim
  * @{
  */



/**
  * @brief		Check whether the specfied PWM output and External input is enable or disable.
  * @param	PWM_CHn: where n can be (0..7) to select the PWM peripheral.
	* @retval	The PWM output and External input enable value of which format is 32bits, but only [1:0]bits are the valid value.
	*					00: PWM output is disable and external input is disable.
	*					01: PWM output is disable and external input is enable.
	*					10: PWM output is enable and external input is disable.
  */
uint32_t PWM_CHn_GetPEEER(PWM_CHn_TypeDef* PWM_CHn) //complete
{
    /* Check the parameters */
    assert_param(IS_PWM_ALL_CH(PWM_CHn));

		/* Return the PWM output and External input Enable Register value */
    return PWM_CHn->PEEER;
}

/**
  * @brief  	Set the enable/disable to a PWM output and External input.
  * @param	PWM_CHn: where n can be (0..7) to select the PWM peripheral.
  * @param	PEEER: specfies the value to be set to PWM output and External input of the selected channel.
	*        	This parameter can be a value of following text. This register only uses [1:0]bits.
	* 					@arg PWM_CHn_PEEER_Disable		 	  	(00): PWM output is disable and external input is disable.
	*					@arg PWM_CHn_PEEER_ExtEnable		 	(01): PWM output is disable and external input is enable.
	*					@arg PWM_CHn_PEEER_PWMEnable	(10): PWM output is enable and external input is disable.
  * @retval None
  */

void PWM_CHn_SetPEEER(PWM_CHn_TypeDef* PWM_CHn, uint32_t PEEER) //complete
{
    /* Check the parameters */
    assert_param(IS_PWM_ALL_CH(PWM_CHn));
    assert_param(IS_PWM_CHn_PEEER(PEEER));
		
		/* Set the PWM output and External input Enable Register value */
    PWM_CHn->PEEER = PEEER;
}



/**
  * @brief			Control output enable/disable of PWM.   
  * @param	PWM_CHn: where n can be (0..7) to select the PWM peripheral.
  * @param	outputEnDisable: specifies the value to be written to the selected channel.
  *          This parameter can be either PWM_CHn_PEEER_Disable(0x0ul) or PWM_CHn_PEEER_Enable(0x2ul).          
  *          PWM_CHn_PEEER_Disable: PWM output disable
  *          PWM_CHn_PEEER_Enable: PWM output enable                  
  * @retval None
  */
void PWM_CtrlPWMOutput(PWM_CHn_TypeDef* PWM_CHn, uint32_t outputEnDisable ) //complete
{
    /* Check the parameters */
    assert_param(IS_PWM_ALL_CH(PWM_CHn));
		assert_param(IS_PWM_Output(outputEnDisable));
		
		/* if Deadzone mode is enabled, check the only one channel is enabled in pair */
		if( PWM_CHn->DZER )
        assert_param(IS_PWM_Deadznoe(PWM_CHn));

    /* Stop PWM_CHn */
    PWM_CHn_Stop(PWM_CHn);
    /*Config PWM output and External input */
    PWM_CHn->PEEER = outputEnDisable; 
}





/**
  * @brief			Set enable PWM output of the selected PWM channel.
  * @param	PWM_CHn: where n can be (0..7) to select the PWM peripheral.
  * @retval		None
  */
void PWM_CtrlPWMOutputEnable(PWM_CHn_TypeDef* PWM_CHn) 
{
		/* Set PWM Output Enable */
    PWM_CtrlPWMOutput(PWM_CHn, PWM_CHn_PEEER_PWMEnable);
}



/**
  * @brief   Set disable PWM output of the selected PWM channel.
  * @param  PWM_CHn: where n can be (0..7) to select the PWM peripheral.
  * @retval None
  */
void PWM_CtrlPWMOutputDisable(PWM_CHn_TypeDef* PWM_CHn) 
{
		/* Set PWM Output Disable */
    PWM_CtrlPWMOutput(PWM_CHn, PWM_CHn_PEEER_Disable);
}






/**
  * @}
  */




/** @defgroup PWM_Group8 Interrupts clear function by channel and type
 *  @brief   Interrupts clear function by channel and type
 *
@verbatim   
 ===============================================================================
                  Interrupts clear function by channel and type
 ===============================================================================  

@endverbatim
  * @{
  */





/* CH0 - Clear Match interrupt, Overflow interrupt and Capture interrupt */
void PWM_CH0_ClearMatchInt(void)
{
    PWM_CHn_ClearInt(PWM_CH0, PWM_CHn_ICR_MatchInterruptClear);
}

void PWM_CH0_ClearOverflowInt(void)
{
   PWM_CHn_ClearInt(PWM_CH0, PWM_CHn_ICR_OverflowInterruptClear);
}

void PWM_CH0_ClearCaptureInt(void)
{
   PWM_CHn_ClearInt(PWM_CH0, PWM_CHn_ICR_CaptureInterruptClear);
}

/* CH1 - Clear Match interrupt, Overflow interrupt and Capture interrupt */
void PWM_CH1_ClearMatchInt(void)
{
    PWM_CHn_ClearInt(PWM_CH1, PWM_CHn_ICR_MatchInterruptClear);
}

void PWM_CH1_ClearOverflowInt(void)
{
   PWM_CHn_ClearInt(PWM_CH1, PWM_CHn_ICR_OverflowInterruptClear);
}

void PWM_CH1_ClearCaptureInt(void)
{
   PWM_CHn_ClearInt(PWM_CH1, PWM_CHn_ICR_CaptureInterruptClear);
}

/* CH2 - Clear Match interrupt, Overflow interrupt and Capture interrupt */
void PWM_CH2_ClearMatchInt(void)
{
    PWM_CHn_ClearInt(PWM_CH2, PWM_CHn_ICR_MatchInterruptClear);
}

void PWM_CH2_ClearOverflowInt(void)
{
   PWM_CHn_ClearInt(PWM_CH2, PWM_CHn_ICR_OverflowInterruptClear);
}

void PWM_CH2_ClearCaptureInt(void)
{
   PWM_CHn_ClearInt(PWM_CH2, PWM_CHn_ICR_CaptureInterruptClear);
}

/* CH3 - Clear Match interrupt, Overflow interrupt and Capture interrupt */
void PWM_CH3_ClearMatchInt(void)
{
    PWM_CHn_ClearInt(PWM_CH3, PWM_CHn_ICR_MatchInterruptClear);
}

void PWM_CH3_ClearOverflowInt(void)
{
   PWM_CHn_ClearInt(PWM_CH3, PWM_CHn_ICR_OverflowInterruptClear);
}

void PWM_CH3_ClearCaptureInt(void)
{
   PWM_CHn_ClearInt(PWM_CH3, PWM_CHn_ICR_CaptureInterruptClear);
}

/* CH4 - Clear Match interrupt, Overflow interrupt and Capture interrupt */
void PWM_CH4_ClearMatchInt(void)
{
    PWM_CHn_ClearInt(PWM_CH4, PWM_CHn_ICR_MatchInterruptClear);
}

void PWM_CH4_ClearOverflowInt(void)
{
   PWM_CHn_ClearInt(PWM_CH4, PWM_CHn_ICR_OverflowInterruptClear);
}

void PWM_CH4_ClearCaptureInt(void)
{
   PWM_CHn_ClearInt(PWM_CH4, PWM_CHn_ICR_CaptureInterruptClear);
}

/* CH5 - Clear Match interrupt, Overflow interrupt and Capture interrupt */
void PWM_CH5_ClearMatchInt(void)
{
    PWM_CHn_ClearInt(PWM_CH5, PWM_CHn_ICR_MatchInterruptClear);
}

void PWM_CH5_ClearOverflowInt(void)
{
   PWM_CHn_ClearInt(PWM_CH5, PWM_CHn_ICR_OverflowInterruptClear);
}

void PWM_CH5_ClearCaptureInt(void)
{
   PWM_CHn_ClearInt(PWM_CH5, PWM_CHn_ICR_CaptureInterruptClear);
}

/* CH6 - Clear Match interrupt, Overflow interrupt and Capture interrupt */
void PWM_CH6_ClearMatchInt(void)
{
    PWM_CHn_ClearInt(PWM_CH6, PWM_CHn_ICR_MatchInterruptClear);
}

void PWM_CH6_ClearOverflowInt(void)
{
   PWM_CHn_ClearInt(PWM_CH6, PWM_CHn_ICR_OverflowInterruptClear);
}

void PWM_CH6_ClearCaptureInt(void)
{
   PWM_CHn_ClearInt(PWM_CH6, PWM_CHn_ICR_CaptureInterruptClear);
}

/* CH7 - Clear Match interrupt, Overflow interrupt and Capture interrupt */
void PWM_CH7_ClearMatchInt(void)
{
    PWM_CHn_ClearInt(PWM_CH7, PWM_CHn_ICR_MatchInterruptClear);
}

void PWM_CH7_ClearOverflowInt(void)
{
   PWM_CHn_ClearInt(PWM_CH7, PWM_CHn_ICR_OverflowInterruptClear);
}

void PWM_CH7_ClearCaptureInt(void)
{
   PWM_CHn_ClearInt(PWM_CH7, PWM_CHn_ICR_CaptureInterruptClear);
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

