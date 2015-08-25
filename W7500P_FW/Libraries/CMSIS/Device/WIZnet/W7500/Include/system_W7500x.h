/**************************************************************************/
/**
 * @file    system_W7500x.h 
 * @author  IOP Team
 * @version V1.0.0
 * @date    01-May-2015
 * @brief   CMSIS Cortex-M0 Core Peripheral Access Layer Header File for
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

#ifndef SYSTEM_W7500x_H   /* ToDo: replace '<Device>' with your device name */
#define SYSTEM_W7500x_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include "W7500x.h"

extern uint32_t SystemCoreClock;     /*!< System Clock Frequency (Core Clock)  */
extern uint32_t GetSystemClock(void);    /*!< Get System Clock Frequency */


/**
 * Initialize the system
 *
 * @param  none
 * @return none
 *
 * @brief  Setup the microcontroller system.
 *         Initialize the System and update the SystemCoreClock variable.
 */
extern void SystemInit (void);

/**
 * Update SystemCoreClock variable
 *
 * @param  none
 * @return none
 *
 * @brief  Updates the SystemCoreClock with current core Clock
 *         retrieved from cpu registers.
 */
extern void SystemCoreClockUpdate (void);

/*----------------------------------------------------------------------------
  Define clocks
 *----------------------------------------------------------------------------*/
#define EXTERN_XTAL     (8000000UL)     /* External Oscillator Frequency        */
#define INTERN_XTAL     (8000000UL)     /* Internal Oscillator Frequency         */

#ifdef __cplusplus
}
#endif

#endif /* SYSTEM_W7500x_H */
