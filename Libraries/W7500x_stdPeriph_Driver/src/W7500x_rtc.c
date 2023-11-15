/**
  ******************************************************************************
  * @file    W7500x_rtc.c
  * @author  
  * @version 
  * @date    
  * @brief   
  ******************************************************************************
  * @attention
  *
 *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "W7500x_crg.h"
#include "W7500x_rtc.h"

/********************************************************************//**
 * @brief		Initializes the RTC peripheral.
 * @param[in]	RTCx	RTC peripheral selected, should be W7500x_RTC
 * @return 		None
 *********************************************************************/
void RTC_Init (RTC_TypeDef *RTCx)
{
	assert_param(PARAM_RTCx(RTCx));

    //CRG->RTCCLK_SEL = (0x01ul);
    //CRG->RTCCLK_PRE = (0x80ul);
    CRG->RTCCLK_32K = (0x01ul);

    RTCx->RTCCON = RTC_CON_CLKEN_Enable;
}

/*********************************************************************//**
 * @brief		De-initializes the RTC peripheral registers to their
*                  default reset values.
 * @param[in]	RTCx	RTC peripheral selected, should be W7500x_RTC
 * @return 		None
 **********************************************************************/
void RTC_DeInit(RTC_TypeDef *RTCx)
{
	assert_param(PARAM_RTCx(RTCx));

	RTCx->RTCCON     = 0x0;
	RTCx->RTCINTE    = 0x0;
	RTCx->RTCINTP    = 0x0;
	RTCx->RTCAMR     = 0x0;
	RTCx->BCDSEC     = 0x0;
	RTCx->BCDMIN     = 0x0;
	RTCx->BCDHOUR    = 0x0;
	RTCx->BCDDAY     = 0x0;
	RTCx->BCDDATE    = 0x0;
	RTCx->BCDMON     = 0x0;
	RTCx->BCDYEAR    = 0x0;
	RTCx->PRESEC     = 0x0;
	RTCx->PREMIN     = 0x0;
	RTCx->PREHOUR    = 0x0;
	RTCx->PREDAY     = 0x0;
	RTCx->PREDATE    = 0x0;
	RTCx->PREMON     = 0x0;
	RTCx->PREYEAR    = 0x0;
}

void RTC_EnableINT(RTC_TypeDef *RTCx)
{
	assert_param(PARAM_RTCx(RTCx));

	RTCx->RTCCON |= RTC_CON_INTEN_Enable;
}

void RTC_DisableINT(RTC_TypeDef *RTCx)
{
	assert_param(PARAM_RTCx(RTCx));

	RTC_ClearINTMask(RTCx);
	RTCx->RTCCON &= ~RTC_CON_INTEN_Disable;
}

void RTC_ClearINTMask(RTC_TypeDef *RTCx)
{
	assert_param(PARAM_RTCx(RTCx));

	RTCx->RTCINTE &= ~(0x3Ful);
}

void RTC_SetINTMask(RTC_TypeDef *RTCx, RTC_INTMASK_POS pos)
{
	assert_param(PARAM_RTCx(RTCx));
	assert_param(IS_INTMASK_POS(pos));

	if(pos == RTC_INTMASK_ALARM)
		RTCx->RTCINTE &= ~(0x01ul << pos);
	else
		RTC_ClearINTMask(RTCx);
	RTCx->RTCINTE |= (0x01ul << pos);
}

void RTC_ClearINTPendingBit(RTC_TypeDef *RTCx)
{
	assert_param(PARAM_RTCx(RTCx));

	RTCx->RTCINTP ^= ~RTC_INTP_CIF;
}

void RTC_ClearAlarmMask(RTC_TypeDef *RTCx)
{
	assert_param(PARAM_RTCx(RTCx));

	RTCx->RTCAMR &= ~(0x7Ful);
}

void RTC_SetAlarmMask(RTC_TypeDef *RTCx, RTC_INTMASK_POS pos)
{
	assert_param(PARAM_RTCx(RTCx));
	assert_param(IS_INTMASK_POS(pos));

	RTC_SetINTMask(RTCx, pos);
	RTC_ClearAlarmMask(RTCx);
	RTCx->RTCAMR |= (0x7Ful);
}

void RTC_ClearAlarmPendingBit(RTC_TypeDef *RTCx)
{
	assert_param(PARAM_RTCx(RTCx));

	RTCx->RTCINTP ^= ~RTC_INTP_ALF;
}

uint8_t RTC_GetStatusPendingBit(RTC_TypeDef *RTCx)
{
	assert_param(PARAM_RTCx(RTCx));

	return (uint8_t)(RTCx->RTCINTP & RTC_INTP_BITMASK);
}

void RTC_SetFullTime (RTC_TypeDef *RTCx, RTC_TIME_Type *pFullTime)
{
	assert_param(PARAM_RTCx(RTCx));
	assert_param(IS_SEC(pFullTime->SEC));
	assert_param(IS_MIN(pFullTime->MIN));
	assert_param(IS_HOUR(pFullTime->HOUR));
	assert_param(IS_DOW(pFullTime->DOW));
	assert_param(IS_DOM(pFullTime->DOM));
	assert_param(IS_MONTH(pFullTime->MONTH));
	assert_param(IS_YEAR(pFullTime->YEAR));

	RTCx->BCDSEC =  (uint32_t)(pFullTime->SEC & RTC_SEC_MASK);
	RTCx->BCDMIN =  (uint32_t)(pFullTime->MIN & RTC_MIN_MASK);
	RTCx->BCDHOUR = (uint32_t)(pFullTime->HOUR & RTC_HOUR_MASK);
	RTCx->BCDDAY =  (uint32_t)(pFullTime->DOW & RTC_DOW_MASK);
	RTCx->BCDDATE = (uint32_t)(pFullTime->DOM & RTC_DOM_MASK);
	RTCx->BCDMON =  (uint32_t)(pFullTime->MONTH & RTC_MONTH_MASK);
	RTCx->BCDYEAR = (uint32_t)(pFullTime->YEAR & RTC_YEAR_MASK);
}

void RTC_GetFullTime (RTC_TypeDef *RTCx, RTC_TIME_Type *pFullTime)
{
	assert_param(PARAM_RTCx(RTCx));

	pFullTime->SEC = (uint8_t)((RTCx->RTCTIME0 & RTC_CTIME_SEC_MASK) );
	pFullTime->MIN = (uint8_t)((RTCx->RTCTIME0 & RTC_CTIME_MIN_MASK)  >> 8);
	pFullTime->HOUR = (uint8_t)((RTCx->RTCTIME0 & RTC_CTIME_HOUR_MASK) >> 16);
	pFullTime->DOW = (uint8_t)((RTCx->RTCTIME0 & RTC_CTIME_DOW_MASK) >> 24);
	pFullTime->DOM = (uint8_t)((RTCx->RTCTIME1 & RTC_CTIME_DOM_MASK) );
	pFullTime->MONTH = (uint8_t)((RTCx->RTCTIME1 & RTC_CTIME_MONTH_MASK) >> 8);
	pFullTime->YEAR = (uint16_t)((RTCx->RTCTIME1 & RTC_CTIME_YEAR_MASK) >> 16);
}

void RTC_SetFullAlarmTime (RTC_TypeDef *RTCx, RTC_TIME_Type *pFullTime)
{
	assert_param(PARAM_RTCx(RTCx));
	assert_param(IS_SEC(pFullTime->SEC));
	assert_param(IS_MIN(pFullTime->MIN));
	assert_param(IS_HOUR(pFullTime->HOUR));
	assert_param(IS_DOW(pFullTime->DOW));
	assert_param(IS_DOM(pFullTime->DOM));
	assert_param(IS_MONTH(pFullTime->MONTH));
	assert_param(IS_YEAR(pFullTime->YEAR));

	RTCx->PRESEC =  (uint32_t)(pFullTime->SEC & RTC_SEC_MASK);
	RTCx->PREMIN =  (uint32_t)(pFullTime->MIN & RTC_MIN_MASK);
	RTCx->PREHOUR = (uint32_t)(pFullTime->HOUR & RTC_HOUR_MASK);
	RTCx->PREDAY =  (uint32_t)(pFullTime->DOW & RTC_DOW_MASK);
	RTCx->PREDATE = (uint32_t)(pFullTime->DOM & RTC_DOM_MASK);
	RTCx->PREMON =  (uint32_t)(pFullTime->MONTH & RTC_MONTH_MASK);
	RTCx->PREYEAR = (uint32_t)(pFullTime->YEAR & RTC_YEAR_MASK);
}

void RTC_GetFullAlarmTime (RTC_TypeDef *RTCx, RTC_TIME_Type *pFullTime)
{
	assert_param(PARAM_RTCx(RTCx));

	pFullTime->SEC = (uint8_t)(RTCx->PRESEC);
	pFullTime->MIN = (uint8_t)(RTCx->PREMIN);
	pFullTime->HOUR = (uint8_t)(RTCx->PREHOUR);
	pFullTime->DOW = (uint8_t)(RTCx->PREDAY);
	pFullTime->DOM = (uint8_t)(RTCx->PREDATE);
	pFullTime->MONTH = (uint8_t)(RTCx->PREMON);
	pFullTime->YEAR = (uint16_t)(RTCx->PREYEAR);
}

void rtc_wrw( uint32_t addr, uint32_t data)
{
	*(volatile uint32_t *)(addr) = data;
}

uint32_t rtc_rdw( uint32_t addr)
{
	return *(volatile uint32_t *)(addr);
}
