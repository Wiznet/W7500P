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
