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
  * @file    W7500x_stdPeriph_Driver/inc/W7500x_wdt.h
  * @author  IOP Team
  * @version V1.0.0
  * @date    01-May-2015
  * @brief   This file contains all the functions prototypes for the WDT 
  *          firmware library.
  ******************************************************************************
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __W7500X_WDT_H
#define __W7500X_WDT_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "W7500x.h"

/**********************************************************************************************/
/**********************************************************************************************/
//                This structure and define must be in W7500x.h
/**********************************************************************************************/
/**********************************************************************************************/


/** @addtogroup W7500x_Periph_Driver
  * @{
  */

/** @addtogroup WDT
  * @{
  */ 
  
  
typedef struct
{
    uint32_t  WDTLoad;
    uint32_t  WDTControl_RstEn;  
}WDT_InitTypeDef;

#define WDTControl_RstEnable        0x1ul
#define WDTControl_RstDisable       0x0ul
#define WDTControl_RstEn_Pos        1

#define WDTControl_IntEnable        0x1ul
#define WDTControl_IntDisable       0x0ul
#define WDTControl_IntEn_Pos        0

#define IS_WDT_CONTROL(CONTROL)        CONTROL <= 0x3ul

#define IS_WDT_CTRL_RSTEN(RSTEN)       RSTEN <= 0x1ul
#define IS_WDT_CTRL_INTEN(INTEN)       INTEN <= 0x1ul


void WDT_DeInit(void);
void WDT_Init(WDT_InitTypeDef* WDT_InitStruct);
void WDT_Start(void);
void WDT_Stop(void);
void WDT_Unlock(void);
void WDT_Lock(void);
void WDT_Set(uint32_t Load);
void WDT_IntClear(void);
ITStatus WDT_GetIntStatus(void);
ITStatus WDT_GetWDTRIS(void);
ITStatus WDT_GetWDTMIS(void);
uint32_t WDT_GetWDTLoad(void);
void WDT_SetWDTLoad(uint32_t Load);
uint32_t WDT_GetWDTValue(void);
uint32_t WDT_GetWDTControl(void);
void WDT_SetWDTControl(uint32_t Control);

#endif //__W7500X_WDT_H


/**
  * @}
  */

/**
  * @}
  */
