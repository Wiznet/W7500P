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
  * @file    W7500x_stdPeriph_Driver/inc/W7500x_pwm.h
  * @author  IOP Team
  * @version V1.0.0
  * @date    01-May-2015
  * @brief   This file contains all the functions prototypes for the pwm 
  *          firmware library.
  ******************************************************************************
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __W7500X_PWM_H
#define __W7500X_PWM_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "W7500x.h"


/** @addtogroup W7500x_Periph_Driver
  * @{
  */

/** @addtogroup PWM
  * @{
  */        
  
  
typedef struct
{
    uint32_t    PWM_CHn_PR;   //Prescale register
                              //   <0..5>   PR : prescale register <R/W>
    uint32_t    PWM_CHn_MR;   //Match register
                              //   <0..31>   MR : Match register <R/W>
    uint32_t    PWM_CHn_LR;   //Limit register
                              //   <0..31>   LR : Limit register <R/W>
    uint32_t    PWM_CHn_UDMR; //Up-Down mode register
                              //   <0>   UDM : Up-down mode <R/W>
    uint32_t    PWM_CHn_PDMR; //Periodic mode register
                                   //   <0>   PDM : Periodic mode <R/W>
}PWM_TimerModeInitTypeDef;

typedef struct
{
    uint32_t    PWM_CHn_PR;   //Prescale register 
                              //   <0..5>   PR : prescale register <R/W>
    uint32_t    PWM_CHn_MR;   //Match register
                              //   <0..31>   MR : Match register <R/W>
    uint32_t    PWM_CHn_LR;   //Limit register
                              //   <0..31>   LR : Limit register <R/W>
    uint32_t    PWM_CHn_UDMR; //Up-Down mode register
                              //   <0>   UDM : Up-down mode <R/W>
    uint32_t    PWM_CHn_PDMR; //Periodic mode register
                              //   <0>   PDM : Peiodic mode <R/W>
    uint32_t    PWM_CHn_CMR;  //Capture mode register
                                   //   <0>   CM : Capture mode <R/W>
}PWM_CaptureModeInitTypeDef;

typedef struct
{
    uint32_t    PWM_CHn_MR;
    uint32_t    PWM_CHn_LR;
    uint32_t    PWM_CHn_UDMR;
    uint32_t    PWM_CHn_PDMR;
    uint32_t    PWM_CHn_TCMR;
}PWM_CounterModeInitTypeDef;

typedef struct
{
    uint32_t    PWM_CHn_PEEER;
}PWM_CtrlPWMOutputTypeDef;

typedef struct
{
    uint32_t    PWM_CHn_PR;
    uint32_t    PWM_CHn_MR;
    uint32_t    PWM_CHn_LR;
    uint32_t    PWM_CHn_UDMR;
    uint32_t    PWM_CHn_PDMR;
    uint32_t    PWM_CHn_DZCR;
}PWM_DeadzoneModeInitTypDef;


#define IS_PWM_ALL_CH(CHn)             ((CHn == PWM_CH0) || \
                                        (CHn == PWM_CH1) || \
                                        (CHn == PWM_CH2) || \
                                        (CHn == PWM_CH3) || \
                                        (CHn == PWM_CH4) || \
                                        (CHn == PWM_CH5) || \
                                        (CHn == PWM_CH6) || \
                                        (CHn == PWM_CH7))


#define PWM_IER_IE0_Enable              (0x1ul << 0) 
#define PWM_IER_IE1_Enable              (0x1ul << 1)
#define PWM_IER_IE2_Enable              (0x1ul << 2)
#define PWM_IER_IE3_Enable              (0x1ul << 3)
#define PWM_IER_IE4_Enable              (0x1ul << 4)
#define PWM_IER_IE5_Enable              (0x1ul << 5)
#define PWM_IER_IE6_Enable              (0x1ul << 6)
#define PWM_IER_IE7_Enable              (0x1ul << 7)

#define PWM_IER_IE0_Disable             ~PWM_IER_IE0_Enable
#define PWM_IER_IE1_Disable             ~PWM_IER_IE1_Enable
#define PWM_IER_IE2_Disable             ~PWM_IER_IE2_Enable
#define PWM_IER_IE3_Disable             ~PWM_IER_IE3_Enable
#define PWM_IER_IE4_Disable             ~PWM_IER_IE4_Enable
#define PWM_IER_IE5_Disable             ~PWM_IER_IE5_Enable
#define PWM_IER_IE6_Disable             ~PWM_IER_IE6_Enable
#define PWM_IER_IE7_Disable             ~PWM_IER_IE7_Enable

#define PWM_SSR_SS0_Start               (0x1ul << 0)
#define PWM_SSR_SS1_Start               (0x1ul << 1)
#define PWM_SSR_SS2_Start               (0x1ul << 2)
#define PWM_SSR_SS3_Start               (0x1ul << 3)
#define PWM_SSR_SS4_Start               (0x1ul << 4)
#define PWM_SSR_SS5_Start               (0x1ul << 5)
#define PWM_SSR_SS6_Start               (0x1ul << 6)
#define PWM_SSR_SS7_Start               (0x1ul << 7)

#define PWM_SSR_SS0_Stop                ~PWM_SSR_SS0_Start
#define PWM_SSR_SS1_Stop                ~PWM_SSR_SS1_Start
#define PWM_SSR_SS2_Stop                ~PWM_SSR_SS2_Start
#define PWM_SSR_SS3_Stop                ~PWM_SSR_SS3_Start
#define PWM_SSR_SS4_Stop                ~PWM_SSR_SS4_Start
#define PWM_SSR_SS5_Stop                ~PWM_SSR_SS5_Start
#define PWM_SSR_SS6_Stop                ~PWM_SSR_SS6_Start
#define PWM_SSR_SS7_Stop                ~PWM_SSR_SS7_Start

#define IS_SSR_BIT_FLAG(FLAG)           (FLAG <= 0xFF)

#define PWM_PSR_PS0_Pause               (0x1ul << 0)
#define PWM_PSR_PS1_Pause               (0x1ul << 1)
#define PWM_PSR_PS2_Pause               (0x1ul << 2)
#define PWM_PSR_PS3_Pause               (0x1ul << 3)
#define PWM_PSR_PS4_Pause               (0x1ul << 4)
#define PWM_PSR_PS5_Pause               (0x1ul << 5)
#define PWM_PSR_PS6_Pause               (0x1ul << 6)
#define PWM_PSR_PS7_Pause               (0x1ul << 7)

#define PWM_PSR_PS0_Restart             ~PWM_PSR_PS0_Pause
#define PWM_PSR_PS1_Restart             ~PWM_PSR_PS1_Pause
#define PWM_PSR_PS2_Restart             ~PWM_PSR_PS2_Pause
#define PWM_PSR_PS3_Restart             ~PWM_PSR_PS3_Pause
#define PWM_PSR_PS4_Restart             ~PWM_PSR_PS4_Pause
#define PWM_PSR_PS5_Restart             ~PWM_PSR_PS5_Pause
#define PWM_PSR_PS6_Restart             ~PWM_PSR_PS6_Pause
#define PWM_PSR_PS7_Restart             ~PWM_PSR_PS7_Pause

#define IS_PWM_PSR_BIT_FLAG(FLAG)       (FLAG <= 0xFF)



#define PWM_CHn_IER_MIE                 (0x1ul << 0) ///< Match Interrupt Enable
#define PWM_CHn_IER_OIE                 (0x1ul << 1) ///< Overflow Interrupt Enable
#define PWM_CHn_IER_CIE                 (0x1ul << 2) ///< Capture Interrupt Enable
#define IS_PWM_CHn_IER(FLAG)            (FLAG <= 0x7)

#define PWM_CHn_IER_MI_Msk              (0x1ul << 0) ///< Match Interrupt Enable Mask
#define PWM_CHn_IER_OI_Msk              (0x1ul << 1) ///< Overflow Interrupt Enable Mask
#define PWM_CHn_IER_CI_Msk              (0x1ul << 2) ///< Capture Interrupt Enable Mask

#define PWM_CHn_ICR_MatchInterruptClear     (0x1ul << 0)
#define PWM_CHn_ICR_OverflowInterruptClear  (0x1ul << 1)
#define PWM_CHn_ICR_CaptureInterruptClear   (0x1ul << 2)
#define IS_PWM_CHn_IntClearFlag(FLAG)       FLAG <= 0x7



//M20170223 becky 1F -> 3F  (PR uses [5:0]bits) 
#define IS_PWM_PR_FILTER(MAXVAL)        (MAXVAL <= 0x3F)
                                     

#define PWM_CHn_UDMR_UpCount            (0x0ul)
#define PWM_CHn_UDMR_DownCount          (0x1ul)
#define IS_PWM_CHn_UDMR(MODE)          ((MODE == PWM_CHn_UDMR_UpCount) || \
                                        (MODE == PWM_CHn_UDMR_DownCount))

#define PWM_CHn_TCMR_TimerMode          (0x0ul)
#define PWM_CHn_TCMR_RisingCounterMode  (0x1ul)
#define PWM_CHn_TCMR_FallingCounterMode (0x2ul)
#define PWM_CHn_TCMR_BothCounterMode    (0x3ul)

//A20170223 becky  add "MODE == PWM_CHn_TCMR_TimerMode"  
#define IS_PWM_CHn_TCMR(MODE)          ((MODE == PWM_CHn_TCMR_TimerMode) || \
										(MODE == PWM_CHn_TCMR_RisingCounterMode)  || \
                                        (MODE == PWM_CHn_TCMR_FallingCounterMode) || \
                                        (MODE == PWM_CHn_TCMR_BothCounterMode))

#define PWM_CHn_PEEER_Disable           (0x0ul)
#define PWM_CHn_PEEER_ExtEnable         (0x1ul)
#define PWM_CHn_PEEER_PWMEnable         (0x2ul)
#define IS_PWM_CHn_PEEER(ENABLE)       ((ENABLE == PWM_CHn_PEEER_Disable)   || \
                                        (ENABLE == PWM_CHn_PEEER_ExtEnable) || \
                                        (ENABLE == PWM_CHn_PEEER_PWMEnable))  

#define IS_PWM_Output(ENABLE)          ((ENABLE == PWM_CHn_PEEER_Disable)   || \
                                        (ENABLE == PWM_CHn_PEEER_PWMEnable))  

#define PWM_CHn_CMR_RisingEdge          0x0ul
#define PWM_CHn_CMR_FallingEdge         0x1ul
#define IS_PWM_CHn_CMR(MODE)           ((MODE == PWM_CHn_CMR_RisingEdge) || \
                                        (MODE == PWM_CHn_CMR_FallingEdge)) 

#define PWM_CHn_PDMR_Oneshot            (0x0ul)
#define PWM_CHn_PDMR_Periodic           (0x1ul)
#define IS_PWM_CHn_PDMR(MODE)          ((MODE == PWM_CHn_PDMR_Periodic) || \
                                        (MODE == PWM_CHn_PDMR_Oneshot))




#define PWM_CHn_DZER_Enable             (0x1ul)             
#define PWM_CHn_DZER_Disable            (0x0ul)             





//M20170223 becky  (PWM_CHn_DZER - > IS_PWM_CHn_DZER )
#define IS_PWM_CHn_DZER(ENABLE)           ((ENABLE == PWM_CHn_DZER_Enable) || \
                                        (ENABLE == PWM_CHn_DZER_Disable)) 

#define IS_PWM_Deadznoe(CHn)           (((CHn == PWM_CH0) && (PWM_CH1->DZER == PWM_CHn_DZER_Disable)) || \
                                        ((CHn == PWM_CH1) && (PWM_CH0->DZER == PWM_CHn_DZER_Disable)) || \
                                        ((CHn == PWM_CH2) && (PWM_CH3->DZER == PWM_CHn_DZER_Disable)) || \
                                        ((CHn == PWM_CH3) && (PWM_CH2->DZER == PWM_CHn_DZER_Disable)) || \
                                        ((CHn == PWM_CH4) && (PWM_CH5->DZER == PWM_CHn_DZER_Disable)) || \
                                        ((CHn == PWM_CH5) && (PWM_CH4->DZER == PWM_CHn_DZER_Disable)) || \
                                        ((CHn == PWM_CH6) && (PWM_CH7->DZER == PWM_CHn_DZER_Disable)) || \
                                        ((CHn == PWM_CH7) && (PWM_CH6->DZER == PWM_CHn_DZER_Disable)))

#define IS_PWM_CHn_DZCR_FILTER(MAXVAL)  (MAXVAL <= 0x3FF)


void PWM_DeInit(PWM_CHn_TypeDef* PWM_CHn);
void PWM_TimerModeInit(PWM_CHn_TypeDef* PWM_CHn, PWM_TimerModeInitTypeDef* PWM_TimerModeInitStruct);
void PWM_CaptureModeInit(PWM_CHn_TypeDef* PWM_CHn, PWM_CaptureModeInitTypeDef* PWM_CaptureModeInitStruct);
void PWM_CounterModeInit(PWM_CHn_TypeDef* PWM_CHn, PWM_CounterModeInitTypeDef* PWM_CounterModeInitStruct);
void PWM_DeadzoneModeInit(PWM_CHn_TypeDef* PWM_CHn, PWM_DeadzoneModeInitTypDef* PWM_DeadzoneModeInitStruct);
void PWM_CtrlPWMOutput(PWM_CHn_TypeDef* PWM_CHn, uint32_t outputEnDisable );
void PWM_CtrlPWMOutputEnable(PWM_CHn_TypeDef* PWM_CHn) ;
void PWM_CtrlPWMOutputDisable(PWM_CHn_TypeDef* PWM_CHn) ;
void PWM_IntConfig(PWM_CHn_TypeDef* PWM_CHn, FunctionalState state);
FlagStatus PWM_GetIntEnableStatus(PWM_CHn_TypeDef* PWM_CHn);
void PWM_CHn_IntConfig(PWM_CHn_TypeDef* PWM_CHn, uint32_t PWM_CHn_IER, FunctionalState state);
void PWM_CHn_Start(PWM_CHn_TypeDef* PWM_CHn);
void PWM_Multi_Start(uint32_t ssr_bit_flag);
void PWM_CHn_Stop(PWM_CHn_TypeDef* PWM_CHn);
void PWM_Multi_Stop(uint32_t ssr_bit_flag);
void PWM_CHn_Pause(PWM_CHn_TypeDef* PWM_CHn);
void PWM_Multi_Pause(uint32_t psr_bit_flag);
void PWM_CHn_Restart(PWM_CHn_TypeDef* PWM_CHn);
void PWM_Multi_Restart(uint32_t psr_bit_flag);
uint32_t PWM_CHn_GetIntEnableStatus(PWM_CHn_TypeDef* PWM_CHn);
uint32_t PWM_CHn_GetIntFlagStatus(PWM_CHn_TypeDef* PWM_CHn);
void PWM_CHn_ClearInt(PWM_CHn_TypeDef* PWM_CHn, uint32_t PWM_CHn_ICR);
uint32_t PWM_CHn_GetTCR(PWM_CHn_TypeDef* PWM_CHn);
uint32_t PWM_CHn_GetPCR(PWM_CHn_TypeDef* PWM_CHn);
uint32_t PWM_CHn_GetPR(PWM_CHn_TypeDef* PWM_CHn);
void PWM_CHn_SetPR(PWM_CHn_TypeDef* PWM_CHn, uint32_t PR);
uint32_t PWM_CHn_GetMR(PWM_CHn_TypeDef* PWM_CHn);
void PWM_CHn_SetMR(PWM_CHn_TypeDef* PWM_CHn, uint32_t MR);
uint32_t PWM_CHn_GetLR(PWM_CHn_TypeDef* PWM_CHn);
void PWM_CHn_SetLR(PWM_CHn_TypeDef* PWM_CHn, uint32_t LR);
uint32_t PWM_CHn_GetUDMR(PWM_CHn_TypeDef* PWM_CHn);
void PWM_CHn_SetUDMR(PWM_CHn_TypeDef* PWM_CHn, uint32_t UDMR);
uint32_t PWM_CHn_GetTCMR(PWM_CHn_TypeDef* PWM_CHn);
void PWM_CHn_SetTCMR(PWM_CHn_TypeDef* PWM_CHn, uint32_t TCMR);
uint32_t PWM_CHn_GetPEEER(PWM_CHn_TypeDef* PWM_CHn);
void PWM_CHn_SetPEEER(PWM_CHn_TypeDef* PWM_CHn, uint32_t PEEER);
uint32_t PWM_CHn_GetCMR(PWM_CHn_TypeDef* PWM_CHn);
void PWM_CHn_SetCMR(PWM_CHn_TypeDef* PWM_CHn, uint32_t CMR);
uint32_t PWM_CHn_GetCR(PWM_CHn_TypeDef* PWM_CHn);
uint32_t PWM_CHn_GetPDMR(PWM_CHn_TypeDef* PWM_CHn);
void PWM_CHn_SetPDMR(PWM_CHn_TypeDef* PWM_CHn, uint32_t PDMR);
void PWM_CHn_SetDZER(PWM_CHn_TypeDef* PWM_CHn, uint32_t DZER);
uint32_t PWM_CHn_GetDZCR(PWM_CHn_TypeDef* PWM_CHn);
void PWM_CHn_SetDZCR(PWM_CHn_TypeDef* PWM_CHn, uint32_t DZCR);
void PWM_CH0_ClearMatchInt(void);
void PWM_CH0_ClearOverflowInt(void);
void PWM_CH0_ClearCaptureInt(void);
void PWM_CH1_ClearMatchInt(void);
void PWM_CH1_ClearOverflowInt(void);
void PWM_CH1_ClearCaptureInt(void);
void PWM_CH2_ClearMatchInt(void);
void PWM_CH2_ClearOverflowInt(void);
void PWM_CH2_ClearCaptureInt(void);
void PWM_CH3_ClearMatchInt(void);
void PWM_CH3_ClearOverflowInt(void);
void PWM_CH3_ClearCaptureInt(void);
void PWM_CH4_ClearMatchInt(void);
void PWM_CH4_ClearOverflowInt(void);
void PWM_CH4_ClearCaptureInt(void);
void PWM_CH5_ClearMatchInt(void);
void PWM_CH5_ClearOverflowInt(void);
void PWM_CH5_ClearCaptureInt(void);
void PWM_CH6_ClearMatchInt(void);
void PWM_CH6_ClearOverflowInt(void);
void PWM_CH6_ClearCaptureInt(void);
void PWM_CH7_ClearMatchInt(void);
void PWM_CH7_ClearOverflowInt(void);
void PWM_CH7_ClearCaptureInt(void);

#ifdef __cplusplus
}
#endif

#endif //__W7500X_PWM_H

/**
  * @}
  */

/**
  * @}
  */
