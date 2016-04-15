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
/**************************************************************************/
/**
 * @file    system_W7500x.c 
 * @author  IOP Team
 * @version V1.0.0
 * @date    25-AUG-2015
 * @brief   CMSIS Cortex-M0 Core Peripheral Access Layer Source File for
 *          Device W7500x
 ******************************************************************************
 *
 * @attention
 * @par Revision history
 *    <2015/05/01> 1st Release
 *
 * <h2><center>&copy; COPYRIGHT 2015 WIZnet Co.,Ltd.</center></h2>
 ******************************************************************************
 */

#include "system_W7500x.h"


/*----------------------------------------------------------------------------
  DEFINES
 *----------------------------------------------------------------------------*/
//#define SYSCLK_EXTERN_OSC



/*----------------------------------------------------------------------------
  Clock Variable definitions
 *----------------------------------------------------------------------------*/
uint32_t SystemFrequency = 0;    /*!< System Clock Frequency (Core Clock)  */
uint32_t SystemCoreClock = 0;    /*!< Processor Clock Frequency            */


/*----------------------------------------------------------------------------
  Clock functions
 *----------------------------------------------------------------------------*/
void SystemCoreClockUpdate (void)            /* Get Core Clock Frequency      */
{
  //SystemCoreClock = XTAL;
}

uint32_t GetSystemClock()
{
    return SystemFrequency;
}


/**
 * Initialize the system
 *
 * @param  none
 * @return none
 *
 * @brief  Setup the microcontroller system.
 *         Initialize the System.
 */
void SystemInit (void)
{
    uint8_t M,N,OD;
    
    (*((volatile uint32_t *)(W7500x_TRIM_BGT))) = (*((volatile uint32_t *)(W7500x_INFO_BGT)));
    (*((volatile uint32_t *)(W7500x_TRIM_OSC))) = (*((volatile uint32_t *)(W7500x_INFO_OSC)));

    // Set PLL input frequency
#ifdef SYSCLK_EXTERN_OSC
    CRG->PLL_IFSR = CRG_PLL_IFSR_OCLK;
#else
    CRG->PLL_IFSR = CRG_PLL_IFSR_RCLK;
#endif    
    OD = (1 << (CRG->PLL_FCR & 0x01)) * (1 << ((CRG->PLL_FCR & 0x02) >> 1));
    N = (CRG->PLL_FCR >>  8 ) & 0x3F;
    M = (CRG->PLL_FCR >> 16) & 0x3F;

#ifdef SYSCLK_EXTERN_OSC
    SystemFrequency = EXTERN_XTAL * M / N * 1 / OD;
#else
    SystemFrequency = INTERN_XTAL * M / N * 1 / OD;
#endif
}
