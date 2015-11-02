/**
  ******************************************************************************
  * @file    W7500x_stdPeriph_Driver/src/W7500x_wdt.c    
  * @author  IOP Team
  * @version v1.0.0
  * @date    26-AUG-2015
  * @brief   This file contains all the functions prototypes for the watchdog timer
  *          firmware library.
  ******************************************************************************
  *
  ******************************************************************************
  */
  
/* Includes -------------------------------------------*/
#include "W7500x_wdt.h"

void WDT_DeInit(void)
{
    WDT_Unlock();

    WDT->WDTLoad      = 0xFFFFFFFF;
    WDT->WDTControl   = 0;
}

void WDT_Init(WDT_InitTypeDef* WDT_InitStruct)
{
    /* Check the parameters */
    assert_param(IS_WDT_CTRL_RSTEN(WDT_InitStruct->WDTControl_RstEn));
   
    WDT_Stop();
    
    WDT->WDTLoad      = WDT_InitStruct->WDTLoad;
    WDT->WDTControl   = (WDT_InitStruct->WDTControl_RstEn << WDTControl_RstEn_Pos);

    WDT_Lock();
}

void WDT_Start(void)
{
    WDT_Unlock();
    
    WDT->WDTControl |= (WDTControl_IntEnable << WDTControl_IntEn_Pos); 
    
    WDT_Lock();
}


void WDT_Stop(void)
{
    WDT_Unlock();
    
    WDT->WDTControl &= ~(WDTControl_IntEnable << WDTControl_IntEn_Pos); 
}

void WDT_Unlock(void)
{
    WDT->WDTLock = 0x1ACCE551;
}

void WDT_Lock(void)
{
    WDT->WDTLock = 0x1;
}

void WDT_Set(uint32_t Load)
{
    WDT_Unlock();
    WDT->WDTLoad = Load;
    WDT_Lock();
}

void WDT_IntClear(void)
{
    WDT_Unlock();
    WDT->WDTIntClr = 0x1;
    WDT_Lock();
}

ITStatus WDT_GetIntStatus(void)
{
    return (ITStatus)WDT->WDTMIS;
}

ITStatus WDT_GetWDTRIS(void)
{
    return (ITStatus)WDT->WDTRIS;
}

ITStatus WDT_GetWDTMIS(void)
{
    return (ITStatus)WDT->WDTMIS;
}


uint32_t WDT_GetWDTLoad(void)
{
    return WDT->WDTLoad;
}

void WDT_SetWDTLoad(uint32_t Load)
{
    WDT_Unlock();
    WDT->WDTLoad = Load;
    WDT_Lock();
}

uint32_t WDT_GetWDTValue(void)
{
    return WDT->WDTValue;
}

uint32_t WDT_GetWDTControl(void)
{
    return WDT->WDTControl;
}

void WDT_SetWDTControl(uint32_t Control)
{
    /* Check the parameters */
    assert_param(IS_WDT_CONTROL(CONTROL));

    WDT_Unlock();
    WDT->WDTControl = Control;
    WDT_Lock();
}


