/*
 *********************************************************************
 * @file
 * @version
 * @author
 * @data
 * @brief
 *********************************************************************
 * @attention
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __W7500X_RTC_H
#define __W7500X_RTC_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "W7500x.h"

	 
/* ----------------------- BIT DEFINITIONS ----------------------------------- */
#define RTC_CON_CLKEN_Disable       (0x00ul << 0)
#define RTC_CON_CLKEN_Enable        (0x01ul << 0)
#define RTC_CON_DIVRST_Reset        (0x01ul << 1)
#define RTC_CON_INTEN_Disable       (0x00ul << 5)
#define RTC_CON_INTEN_Enable        (0x01ul << 5)

/**********************************************************************
* RTCINTP register definitions
**********************************************************************/
/** RTCINTP register mask */
#define RTC_INTP_BITMASK		(0x00000003)
/** Bit inform the source interrupt is counter increment*/
#define RTC_INTP_CIF			(0x01ul << 0)
/** Bit inform the source interrupt is alarm match*/
#define RTC_INTP_ALF			(0x01ul << 1)

/**********************************************************************
* Time Counter Group and Alarm register group
**********************************************************************/
/** SEC register mask */
#define RTC_SEC_MASK			(0x0000007F)
/** MIN register mask */
#define RTC_MIN_MASK			(0x0000007F)
/** HOUR register mask */
#define RTC_HOUR_MASK			(0x0000003F)
/** DOW register mask */
#define RTC_DOW_MASK			(0x0000000F)
/** DOM register mask */
#define RTC_DOM_MASK			(0x0000003F)
/** MONTH register mask */
#define RTC_MONTH_MASK			(0x0000001F)
/** YEAR register mask */
#define RTC_YEAR_MASK			(0x0000FFFF)

#define RTC_CTIME_SEC_MASK			(0x0000007F)
#define RTC_CTIME_MIN_MASK			(0x00007F00)
#define RTC_CTIME_HOUR_MASK			(0x003F0000)
#define RTC_CTIME_DOW_MASK			(0x0F000000)
#define RTC_CTIME_DOM_MASK			(0x0000003F)
#define RTC_CTIME_MONTH_MASK		(0x00001F00)
#define RTC_CTIME_YEAR_MASK			(0xFFFF0000)

#define RTC_SECOND_MAX		59 /*!< Maximum value of second */
#define RTC_SECOND_MIN		0 /*!< Maximum value of second */
#define RTC_MINUTE_MAX		59 /*!< Maximum value of minute*/
#define RTC_MINUTE_MIN		0 /*!< Maximum value of minute*/
#define RTC_HOUR_MAX		23 /*!< Maximum value of hour*/
#define RTC_HOUR_MIN		0 /*!< Maximum value of hour*/
#define RTC_DAYOFWEEK_MAX	7 /*!< Maximum value of day of week*/
#define RTC_DAYOFWEEK_MIN	1 /*!< Minimum value of day of week*/
#define RTC_DAYOFMONTH_MAX 	31 /*!< Maximum value of day of month*/
#define RTC_DAYOFMONTH_MIN 	1 /*!< Minimum value of day of month*/
#define RTC_MONTH_MAX		12 /*!< Maximum value of month*/
#define RTC_MONTH_MIN		1 /*!< Minimum value of month*/
#define RTC_YEAR_MAX		4095 /*!< Maximum value of year*/
#define RTC_YEAR_MIN		0 /*!< Maximum value of year*/

typedef struct {
	uint8_t  SEC; 		/*!< Seconds Register */
	uint8_t  MIN; 		/*!< Minutes Register */
	uint8_t  HOUR; 		/*!< Hours Register */
	uint8_t  DOW; 		/*!< Day of Week Register */
	uint8_t  DOM;		/*!< Day of Month Register */
	uint8_t  MONTH; 	/*!< Months Register */
	uint16_t YEAR; 		/*!< Years Register */
} RTC_TIME_Type;

/** @brief Consolidated RTC Time */
typedef struct {
	uint32_t TIME0; 	/*!< RTCTIME0 Register */
	uint32_t TIME1; 	/*!< RTCTIME1 Register */
} RTC_CONTIME_Type;

/** @brief RTC time type option */
typedef enum {
	RTC_TIMETYPE_SECOND = 0, 		/*!< Second */
	RTC_TIMETYPE_MINUTE = 1, 		/*!< Month */
	RTC_TIMETYPE_HOUR = 2, 			/*!< Hour */
	RTC_TIMETYPE_DAYOFWEEK = 3, 	/*!< Day of week */
	RTC_TIMETYPE_DAYOFMONTH = 4, 	/*!< Day of month */
	RTC_TIMETYPE_MONTH = 5, 		/*!< Month */
	RTC_TIMETYPE_YEAR = 6 			/*!< Year */
} RTC_TIMETYPE_Num;

/** @brief RTC interrupt source */
typedef enum {
	RTC_INT_COUNTER_INCREASE = RTC_INTP_CIF, 	/*!<  Counter Increment Interrupt */
	RTC_INT_ALARM = RTC_INTP_ALF 				/*!< The alarm interrupt */
} RTC_INT_OPT;

/** @brief RTC Interrupt Mask register */
typedef enum {
	RTC_INTMASK_SECOND = 0, 		/*!< Second */
	RTC_INTMASK_MINUTE = 1, 		/*!< Month */
	RTC_INTMASK_HOUR = 2, 			/*!< Hour */
	RTC_INTMASK_DATE = 3, 			/*!< Day of month */
	RTC_INTMASK_DAY = 4, 			/*!< Day of week */
	RTC_INTMASK_MONTH = 5, 			/*!< Month */
	RTC_INTMASK_ALARM = 6 			/*!< Alarm */
} RTC_INTMASK_POS;

/* ---------------- CHECK PARAMETER DEFINITIONS ---------------------------- */
/** Macro to determine if it is valid RTC peripheral */
#define PARAM_RTCx(x)	(((uint32_t *)x)==((uint32_t *)RTC))
#define IS_INTMASK_POS(POS) (((POS) == RTC_INTMASK_SECOND) || \
                             ((POS) == RTC_INTMASK_MINUTE) || \
                             ((POS) == RTC_INTMASK_HOUR) || \
                             ((POS) == RTC_INTMASK_DATE) || \
                             ((POS) == RTC_INTMASK_DAY) || \
                             ((POS) == RTC_INTMASK_MONTH) || \
                             ((POS) == RTC_INTMASK_ALARM) )
#define IS_SEC(SEC) (((SEC) >= RTC_SECOND_MIN) && \
                     ((SEC) <= RTC_SECOND_MAX) )
#define IS_MIN(MIN) (((MIN) >= RTC_MINUTE_MIN) && \
                     ((MIN) <= RTC_MINUTE_MAX) )
#define IS_HOUR(HOUR) (((HOUR) >= RTC_HOUR_MIN) && \
                       ((HOUR) <= RTC_HOUR_MAX) )
#define IS_DOW(DOW) (((DOW) >= RTC_DAYOFWEEK_MIN) && \
                     ((DOW) <= RTC_DAYOFWEEK_MAX) )
#define IS_DOM(DOM) (((DOM) >= RTC_DAYOFMONTH_MIN) && \
                     ((DOM) <= RTC_DAYOFMONTH_MAX) )
#define IS_MONTH(MONTH) (((MONTH) >= RTC_MONTH_MIN) && \
                         ((MONTH) <= RTC_MONTH_MAX) )
#define IS_YEAR(YEAR) (((YEAR) >= RTC_YEAR_MIN) && \
                       ((YEAR) <= RTC_YEAR_MAX) )

/* Public Functions ----------------------------------------------------------- */
/** @defgroup RTC_Public_Functions
 * @{
 */

void RTC_Init (RTC_TypeDef *RTCx);
void RTC_DeInit(RTC_TypeDef *RTCx);
void RTC_EnableINT(RTC_TypeDef *RTCx);
void RTC_DisableINT(RTC_TypeDef *RTCx);
void RTC_ClearINTMask(RTC_TypeDef *RTCx);
void RTC_SetINTMask(RTC_TypeDef *RTCx, RTC_INTMASK_POS pos);
void RTC_ClearINTPendingBit(RTC_TypeDef *RTCx);
void RTC_ClearAlarmMask(RTC_TypeDef *RTCx);
void RTC_SetAlarmMask(RTC_TypeDef *RTCx, RTC_INTMASK_POS pos);
void RTC_ClearAlarmPendingBit(RTC_TypeDef *RTCx);
uint8_t RTC_GetStatusPendingBit(RTC_TypeDef *RTCx);
void RTC_SetFullTime (RTC_TypeDef *RTCx, RTC_TIME_Type *pFullTime);
void RTC_GetFullTime (RTC_TypeDef *RTCx, RTC_TIME_Type *pFullTime);
void RTC_SetFullAlarmTime (RTC_TypeDef *RTCx, RTC_TIME_Type *pFullTime);
void RTC_GetFullAlarmTime (RTC_TypeDef *RTCx, RTC_TIME_Type *pFullTime);

void rtc_wrw( uint32_t addr, uint32_t data);
uint32_t rtc_rdw( uint32_t addr);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /*  __W7500X_RTC_H */

/**
 * @}
 */

/* --------------------------------- End Of File ------------------------------ */



