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
  * @file    W7500x_stdPeriph_Driver/src/W7500x_crg.c    
  * @author  IOP Team
  * @version v1.0.0
  * @date    01-May-2015
  * @brief   This file contains all the functions prototypes for the crg 
  *          firmware library.
  ******************************************************************************
  *
  ******************************************************************************
  */

/*include --------------------------------------------*/
#include "W7500x_crg.h"

/** @addtogroup W7500x_Periph_Driver
  * @{
  */

/** @defgroup CRG
  * @brief CRG driver modules
  * @{
  */


/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/** @defgroup CRG_Private_Functions
  * @{
  */ 

void CRG_DeInit(void)
{
//To Do
}

/**
	*	@brief		Clock Reset Generator(CRG) OSCillator Power Down Enable
	*	@param	NewState: If ENABLE, it is 1. Else if DISABLE, it is 0.
	*	@retval		None
*/

void CRG_OSC_PowerDownEnable(FunctionalState NewState)
{
    if(NewState != DISABLE)     CRG->OSC_PDR = CRG_OSC_PDR_PD;    
    else                        CRG->OSC_PDR = CRG_OSC_PDR_NRMLOP;
}

/**
	*	@brief		Clock Reset Generator(CRG) Phase Locked Loop(PLL) Power Down Enable
	*	@param	NewState: If ENABLE, it is 1. Else if DISABLE, it is 0.
	*	@retval		None
*/
void CRG_PLL_PowerDownEnable(FunctionalState NewState)
{
    if(NewState != DISABLE)     CRG->PLL_PDR = CRG_PLL_PDR_PD;
    else                        CRG->PLL_PDR = CRG_PLL_PDR_NRMLOP;
}

/**
	*	@brief		Clock Reset Generator(CRG) Phase Locked Loop(PLL) Output Enable
	*	@param	NewState: If ENABLE, it is 1. Else if DISABLE, it is 0.
	*	@retval		None
*/
void CRG_PLL_OutputEnable(FunctionalState NewState)
{
    if(NewState != DISABLE)     CRG->PLL_OER = CRG_PLL_OER_EN;
    else                        CRG->PLL_OER = CRG_PLL_OER_DIS;
}

/**
	*	@brief		Clock Reset Generator(CRG) Phase Locked Loop(PLL) Bypass Enable
	*	@param	NewState: If ENABLE, it is 1. Else if DISABLE, it is 0.
	*	@retval		None
*/
void CRG_PLL_BypassEnable(FunctionalState NewState)
{
    if(NewState != DISABLE)     CRG->PLL_BPR = CRG_PLL_BPR_EN;
    else                        CRG->PLL_BPR = CRG_PLL_BPR_DIS;
}

/**
	*	@brief		Clock Reset Generator(CRG) Phase Locked Loop(PLL) Input Frequency Select
	*	@param	src: It consists of  CRG_CLK_DIS, CRG_MCLK, CRG_RCLK, CRG_OCLK.
	*	@retval		None
*/
void CRG_PLL_InputFrequencySelect(CRG_CLK_SOURCE src)
{
	/*	Check the parameters	*/
	/* if src is CRG_RCLK or CRG_OCLK, IS_CRG_PLL_SRC() is 1. Else IS_CRG_PLL_SRC() is 0. */
    assert_param(IS_CRG_PLL_SRC(src));

    if( src == CRG_RCLK )   CRG->PLL_IFSR = CRG_PLL_IFSR_RCLK; 
    else                    CRG->PLL_IFSR = CRG_PLL_IFSR_OCLK;
}

/**
	*	@brief		Clock Reset Generator(CRG) FCLK Source Select
	*	@param	src: It consists of  CRG_CLK_DIS, CRG_MCLK, CRG_RCLK, CRG_OCLK.
	*	@retval		None
*/
void CRG_FCLK_SourceSelect(CRG_CLK_SOURCE src)
{
		/*	Check the parameters	*/
    assert_param(IS_CRG_FCLK_SRC(src));

    if      ( src == CRG_RCLK )     CRG->FCLK_SSR = CRG_FCLK_SSR_RCLK; 
    else if ( src == CRG_OCLK )     CRG->FCLK_SSR = CRG_FCLK_SSR_OCLK;
    else                            CRG->FCLK_SSR = CRG_FCLK_SSR_MCLK;
}

/**
	*	@brief		Clock Reset Generator(CRG) FCLK Set Prescale
	*	@param	prediv: It consists of  CRG_PREDIV1, CRG_PREDIV1, CRG_PREDIV1, CRG_PREDIV1. CRG_PREDIV16, CRG_PREDIV32, CRG_PREDIV64
  * 							  CRG_PREDIV128
	*	@retval		None
*/
void CRG_FCLK_SetPrescale(CRG_PREDIV prediv)
{
		/*	Check the parameters	*/
	assert_param(IS_CRG_FCLK_PREDIV(prediv));

    if      ( prediv == CRG_PREDIV1 )   CRG->FCLK_PVSR = CRG_FCLK_PVSR_DIV1; 
    else if ( prediv == CRG_PREDIV2 )   CRG->FCLK_PVSR = CRG_FCLK_PVSR_DIV2; 
    else if ( prediv == CRG_PREDIV4 )   CRG->FCLK_PVSR = CRG_FCLK_PVSR_DIV4; 
    else                                CRG->FCLK_PVSR = CRG_FCLK_PVSR_DIV8; 
}

/**
	*	@brief		Clock Reset Generator(CRG) SSPCLK Source Select
	*	@param	src: It consists of  CRG_CLK_DIS, CRG_MCLK, CRG_RCLK, CRG_OCLK.
	*	@retval		None
*/
void CRG_SSPCLK_SourceSelect(CRG_CLK_SOURCE src)
{
  	/*	Check the parameters	*/
		assert_param(IS_CRG_SSPCLK_SRC(src));

    if      ( src == CRG_CLK_DIS )     CRG->SSPCLK_SSR = CRG_SSPCLK_SSR_DIS;
    else if ( src == CRG_MCLK )        CRG->SSPCLK_SSR = CRG_SSPCLK_SSR_MCLK;
    else if ( src == CRG_RCLK )        CRG->SSPCLK_SSR = CRG_SSPCLK_SSR_RCLK;
    else                               CRG->SSPCLK_SSR = CRG_SSPCLK_SSR_OCLK;
}

/**
	*	@brief		Clock Reset Generator(CRG) SSPCLK Set Prescale
	*	@param	prediv: It consists of  CRG_PREDIV1, CRG_PREDIV1, CRG_PREDIV1, CRG_PREDIV1. CRG_PREDIV16, CRG_PREDIV32, CRG_PREDIV64
  * 							  CRG_PREDIV128 
	*	@retval		None
*/
void CRG_SSPCLK_SetPrescale(CRG_PREDIV prediv)
{
	  	/*	Check the parameters	*/
    assert_param(IS_CRG_SSPCLK_PREDIV(prediv));

    if      ( prediv == CRG_PREDIV1 )   CRG->SSPCLK_PVSR = CRG_SSPCLK_PVSR_DIV1; 
    else if ( prediv == CRG_PREDIV2 )   CRG->SSPCLK_PVSR = CRG_SSPCLK_PVSR_DIV2; 
    else if ( prediv == CRG_PREDIV4 )   CRG->SSPCLK_PVSR = CRG_SSPCLK_PVSR_DIV4; 
    else                                CRG->SSPCLK_PVSR = CRG_SSPCLK_PVSR_DIV8; 
}

/**
	*	@brief		Clock Reset Generator(CRG) SSPCLK Source Select
	*	@param	src: It consists of  CRG_CLK_DIS, CRG_MCLK, CRG_RCLK, CRG_OCLK.
	*	@retval		None
*/
void CRG_ADCCLK_SourceSelect(CRG_CLK_SOURCE src)
{
	  	/*	Check the parameters	*/
    assert_param(IS_CRG_ADCCLK_SRC(src));

    if      ( src == CRG_CLK_DIS )   CRG->ADCCLK_SSR = CRG_ADCCLK_SSR_DIS;
    else if ( src == CRG_MCLK )      CRG->ADCCLK_SSR = CRG_ADCCLK_SSR_MCLK;
    else if ( src == CRG_RCLK )      CRG->ADCCLK_SSR = CRG_ADCCLK_SSR_RCLK;
    else                             CRG->ADCCLK_SSR = CRG_ADCCLK_SSR_OCLK;
}

/**
	*	@brief		Clock Reset Generator(CRG) ADCCLK Set Prescale
	*	@param	prediv: It consists of  CRG_PREDIV1, CRG_PREDIV1, CRG_PREDIV1, CRG_PREDIV1. CRG_PREDIV16, CRG_PREDIV32, CRG_PREDIV64
  * 							  CRG_PREDIV128
	*	@retval		None
*/
void CRG_ADCCLK_SetPrescale(CRG_PREDIV prediv)
{
		/*	Check the parameters	*/
    assert_param(IS_CRG_ADCCLK_PREDIV(prediv));

    if      ( prediv == CRG_PREDIV1 )   CRG->ADCCLK_PVSR = CRG_ADCCLK_PVSR_DIV1; 
    else if ( prediv == CRG_PREDIV2 )   CRG->ADCCLK_PVSR = CRG_ADCCLK_PVSR_DIV2; 
    else if ( prediv == CRG_PREDIV4 )   CRG->ADCCLK_PVSR = CRG_ADCCLK_PVSR_DIV4; 
    else                                CRG->ADCCLK_PVSR = CRG_ADCCLK_PVSR_DIV8; 
}

/**
	*	@brief		Clock Reset Generator(CRG) TimeRCLK Source Select
	*	@param	num: It consists of CRG_TIMER0 and CRG_TIMER1.
	*	@param	src: It consists of  CRG_CLK_DIS, CRG_MCLK, CRG_RCLK, CRG_OCLK.
	*	@retval		None
*/
void CRG_TIMERCLK_SourceSelect(CRG_TIMER num, CRG_CLK_SOURCE src)
{
			/*	Check the parameters	*/
    assert_param(IS_CRG_TIMERCLK_NUM(num));
    assert_param(IS_CRG_TIMERCLK_SRC(src));

    if      ( src == CRG_CLK_DIS )   CRG_SET_TIMERCLK_SSR(num,CRG_TIMERCLK_SSR_DIS);
    else if ( src == CRG_MCLK )      CRG_SET_TIMERCLK_SSR(num,CRG_TIMERCLK_SSR_MCLK);
    else if ( src == CRG_RCLK )      CRG_SET_TIMERCLK_SSR(num,CRG_TIMERCLK_SSR_RCLK); 
    else                             CRG_SET_TIMERCLK_SSR(num,CRG_TIMERCLK_SSR_OCLK);
}

/**
	*	@brief		Clock Reset Generator(CRG) TimeRCLK Source Select
	*	@param	num: It consists of CRG_TIMER0 and CRG_TIMER1.
	*	@param	prediv: It consists of  CRG_PREDIV1, CRG_PREDIV1, CRG_PREDIV1, CRG_PREDIV1. CRG_PREDIV16, CRG_PREDIV32, CRG_PREDIV64
  * 							  CRG_PREDIV128
	*	@retval		None
*/
void CRG_TIMERCLK_SetPrescale(CRG_TIMER num, CRG_PREDIV prediv)
{
			/*	Check the parameters	*/
    assert_param(IS_CRG_TIMERCLK_NUM(num));
    assert_param(IS_CRG_TIMERCLK_PREDIV(prediv));

    if      ( prediv == CRG_PREDIV1 )   CRG_SET_TIMERCLK_PREDIV(num,CRG_TIMERCLK_PVSR_DIV1); 
    else if ( prediv == CRG_PREDIV2 )   CRG_SET_TIMERCLK_PREDIV(num,CRG_TIMERCLK_PVSR_DIV2); 
    else if ( prediv == CRG_PREDIV4 )   CRG_SET_TIMERCLK_PREDIV(num,CRG_TIMERCLK_PVSR_DIV4);
    else if ( prediv == CRG_PREDIV8 )   CRG_SET_TIMERCLK_PREDIV(num,CRG_TIMERCLK_PVSR_DIV8);
    else if ( prediv == CRG_PREDIV16 )  CRG_SET_TIMERCLK_PREDIV(num,CRG_TIMERCLK_PVSR_DIV16);
    else if ( prediv == CRG_PREDIV32 )  CRG_SET_TIMERCLK_PREDIV(num,CRG_TIMERCLK_PVSR_DIV32);
    else if ( prediv == CRG_PREDIV64 )  CRG_SET_TIMERCLK_PREDIV(num,CRG_TIMERCLK_PVSR_DIV64);
    else                                CRG_SET_TIMERCLK_PREDIV(num,CRG_TIMERCLK_PVSR_DIV128);
}


/**
	*	@brief		Clock Reset Generator(CRG) PWMCLK Source Select
	*	@param	num: It consists of CRG_TIMER0 and CRG_TIMER1.
	*	@param	src: It consists of  CRG_CLK_DIS, CRG_MCLK, CRG_RCLK, CRG_OCLK.
	*	@retval		None
*/
void CRG_PWMCLK_SourceSelect(CRG_PWM num, CRG_CLK_SOURCE src)
{
		/*	Check the parameters	*/
    assert_param(IS_CRG_PWMCLK_NUM(num));
    assert_param(IS_CRG_PWMCLK_SRC(src));

    if      ( src == CRG_CLK_DIS )   CRG_SET_PWMCLK_SSR(num,CRG_PWMCLK_SSR_DIS);
    else if ( src == CRG_MCLK )      CRG_SET_PWMCLK_SSR(num,CRG_PWMCLK_SSR_MCLK);
    else if ( src == CRG_RCLK )      CRG_SET_PWMCLK_SSR(num,CRG_PWMCLK_SSR_RCLK); 
    else                             CRG_SET_PWMCLK_SSR(num,CRG_PWMCLK_SSR_OCLK);
}

/**
	*	@brief		Clock Reset Generator(CRG) PWMCLK Set Prescale
	*	@param	num: It consists of CRG_TIMER0 and CRG_TIMER1.
	*	@param	prediv: It consists of  CRG_PREDIV1, CRG_PREDIV1, CRG_PREDIV1, CRG_PREDIV1. CRG_PREDIV16, CRG_PREDIV32, CRG_PREDIV64
  * 							  CRG_PREDIV128.
	*	@retval		None
*/
void CRG_PWMCLK_SetPrescale(CRG_PWM num, CRG_PREDIV prediv)
{
	/*	Check the parameters	*/
    assert_param(IS_CRG_PWMCLK_NUM(num));
    assert_param(IS_CRG_PWMCLK_PREDIV(prediv));

    if      ( prediv == CRG_PREDIV1 )   CRG_SET_PWMCLK_PREDIV(num,CRG_PWMCLK_PVSR_DIV1); 
    else if ( prediv == CRG_PREDIV2 )   CRG_SET_PWMCLK_PREDIV(num,CRG_PWMCLK_PVSR_DIV2); 
    else if ( prediv == CRG_PREDIV4 )   CRG_SET_PWMCLK_PREDIV(num,CRG_PWMCLK_PVSR_DIV4);
    else if ( prediv == CRG_PREDIV8 )   CRG_SET_PWMCLK_PREDIV(num,CRG_PWMCLK_PVSR_DIV8);
    else if ( prediv == CRG_PREDIV16 )  CRG_SET_PWMCLK_PREDIV(num,CRG_PWMCLK_PVSR_DIV16);
    else if ( prediv == CRG_PREDIV32 )  CRG_SET_PWMCLK_PREDIV(num,CRG_PWMCLK_PVSR_DIV32);
    else if ( prediv == CRG_PREDIV64 )  CRG_SET_PWMCLK_PREDIV(num,CRG_PWMCLK_PVSR_DIV64);
    else                                CRG_SET_PWMCLK_PREDIV(num,CRG_PWMCLK_PVSR_DIV128);
}

/**
	*	@brief		Clock Reset Generator(CRG) WDOGCLK HS Source Select
	*	@param	src: It consists of  CRG_CLK_DIS, CRG_MCLK, CRG_RCLK, CRG_OCLK.
	*	@retval		None
*/
void CRG_WDOGCLK_HS_SourceSelect(CRG_CLK_SOURCE src)
{
	/*	Check the parameters	*/
    assert_param(IS_CRG_WDOGCLK_HS_SRC(src));

    if      ( src == CRG_CLK_DIS )   CRG->WDOGCLK_HS_SSR = CRG_WDOGCLK_HS_SSR_DIS;
    else if ( src == CRG_MCLK )      CRG->WDOGCLK_HS_SSR = CRG_WDOGCLK_HS_SSR_MCLK;
    else if ( src == CRG_RCLK )      CRG->WDOGCLK_HS_SSR = CRG_WDOGCLK_HS_SSR_RCLK;
    else                             CRG->WDOGCLK_HS_SSR = CRG_WDOGCLK_HS_SSR_OCLK;
}

/**
	*	@brief		Clock Reset Generator(CRG) WDOGCLK HS Set Prescale
	*	@param	prediv: It consists of  CRG_PREDIV1, CRG_PREDIV1, CRG_PREDIV1, CRG_PREDIV1. CRG_PREDIV16, CRG_PREDIV32, CRG_PREDIV64
  * 							  CRG_PREDIV128.
	*	@retval		None
*/
void CRG_WDOGCLK_HS_SetPrescale(CRG_PREDIV prediv)
{
	/*	Check the parameters	*/
    assert_param(IS_CRG_WDOGCLK_HS_PREDIV(prediv));

    if      ( prediv == CRG_PREDIV1 )   CRG->WDOGCLK_HS_PVSR = CRG_WDOGCLK_HS_PVSR_DIV1; 
    else if ( prediv == CRG_PREDIV2 )   CRG->WDOGCLK_HS_PVSR = CRG_WDOGCLK_HS_PVSR_DIV2; 
    else if ( prediv == CRG_PREDIV4 )   CRG->WDOGCLK_HS_PVSR = CRG_WDOGCLK_HS_PVSR_DIV4;
    else if ( prediv == CRG_PREDIV8 )   CRG->WDOGCLK_HS_PVSR = CRG_WDOGCLK_HS_PVSR_DIV8;
    else if ( prediv == CRG_PREDIV16 )  CRG->WDOGCLK_HS_PVSR = CRG_WDOGCLK_HS_PVSR_DIV16;
    else if ( prediv == CRG_PREDIV32 )  CRG->WDOGCLK_HS_PVSR = CRG_WDOGCLK_HS_PVSR_DIV32;
    else if ( prediv == CRG_PREDIV64 )  CRG->WDOGCLK_HS_PVSR = CRG_WDOGCLK_HS_PVSR_DIV64;
    else                                CRG->WDOGCLK_HS_PVSR = CRG_WDOGCLK_HS_PVSR_DIV128;
}

/**
	*	@brief		Clock Reset Generator(CRG) UARTCLK Source Select
	*	@param	src: It consists of  CRG_CLK_DIS, CRG_MCLK, CRG_RCLK, CRG_OCLK.
	*	@retval		None
*/
void CRG_UARTCLK_SourceSelect(CRG_CLK_SOURCE src)
{
	/*	Check the parameters	*/	
    assert_param(IS_CRG_UARTCLK_SRC(src));

    if      ( src == CRG_CLK_DIS )   CRG->UARTCLK_SSR = CRG_UARTCLK_SSR_DIS;
    else if ( src == CRG_MCLK )      CRG->UARTCLK_SSR = CRG_UARTCLK_SSR_MCLK;
    else if ( src == CRG_RCLK )      CRG->UARTCLK_SSR = CRG_UARTCLK_SSR_RCLK;
    else                             CRG->UARTCLK_SSR = CRG_UARTCLK_SSR_OCLK;
}

/**
	*	@brief		Clock Reset Generator(CRG) UARTCLK Set Prescale
	*	@param	prediv: It consists of  CRG_PREDIV1, CRG_PREDIV1, CRG_PREDIV1, CRG_PREDIV1. CRG_PREDIV16, CRG_PREDIV32, CRG_PREDIV64
  * 							  CRG_PREDIV128.
	*	@retval		None
*/
void CRG_UARTCLK_SetPrescale(CRG_PREDIV prediv)
{
	/*	Check the parameters	*/	
    assert_param(IS_CRG_UARTCLK_PREDIV(prediv));

    if      ( prediv == CRG_PREDIV1 )   CRG->UARTCLK_PVSR = CRG_UARTCLK_PVSR_DIV1; 
    else if ( prediv == CRG_PREDIV2 )   CRG->UARTCLK_PVSR = CRG_UARTCLK_PVSR_DIV2; 
    else if ( prediv == CRG_PREDIV4 )   CRG->UARTCLK_PVSR = CRG_UARTCLK_PVSR_DIV4; 
    else                                CRG->UARTCLK_PVSR = CRG_UARTCLK_PVSR_DIV8; 
}

/**
	*	@brief		Clock Reset Generator(CRG) MII Enable
	*	@param	rx_clk: It consists of DISABLE and ENABLE. 
	* 	@param	tx_clk: It consists of DISABLE and ENABLE.						  
	*	@retval		None
*/
void CRG_MII_Enable(FunctionalState rx_clk, FunctionalState tx_clk)
{
	/*	Check the parameters	*/	
    assert_param(IS_FUNCTIONAL_STATE(rx_clk));
    assert_param(IS_FUNCTIONAL_STATE(tx_clk));

    if  ( rx_clk != DISABLE )   CRG->MIICLK_ECR |= CRG_MIICLK_ECR_EN_RXCLK;
    else                        CRG->MIICLK_ECR &= ~(CRG_MIICLK_ECR_EN_RXCLK);    

    if  ( tx_clk != DISABLE )   CRG->MIICLK_ECR |= CRG_MIICLK_ECR_EN_TXCLK;
    else                        CRG->MIICLK_ECR &= ~(CRG_MIICLK_ECR_EN_TXCLK);
}

/**
	*	@brief		Clock Reset Generator(CRG) Set Monitoring Clock
	*	@param	value: 32bit type define   
	*	@retval		None
*/
void CRG_SetMonitoringClock(uint32_t value)
{
		/*	Check the parameters	*/	
    assert_param(IS_CRG_MONCLK_SSR(value));
		/* Get MONCLK_SSR */
    CRG->MONCLK_SSR = value;
}

/**
	*	@brief		Clock Reset Generator(CRG) Get Monitoring Clock
	*	@retval		MONCLK_SSR
*/
uint32_t CRG_GetMonitoringClock(void)
{
    return (uint8_t)CRG->MONCLK_SSR;
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
