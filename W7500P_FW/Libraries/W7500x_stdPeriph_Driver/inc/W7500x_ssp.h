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
  * @file    W7500x_stdPeriph_Driver/inc/W7500x_ssp.h
  * @author  IOP Team
  * @version V1.0.0
  * @date    01-May-2015
  * @brief   This file contains all the functions prototypes for the SSP 
  *          firmware library.
  ******************************************************************************
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __W7500X_SSP_H
#define __W7500X_SSP_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "W7500x.h"

/** @addtogroup W7500x_StdPeriph_Driver
  * @{
  */

/** @addtogroup SSP
  * @{
  */ 

/** @defgroup SSP_Exported_Types
  * @{
  */

/** 
  * @brief  SSP Init structure definition  
  */

typedef struct
{

  uint32_t SSP_SerialClockRate;     /*!<  */

  uint32_t SSP_FrameFormat;          /*!<  */

  uint32_t SSP_CPHA;                /*!< Specifies the clock active edge for the bit capture.
                                         This parameter can be a value of @ref SSP_Clock_Phase */
  uint32_t SSP_CPOL;                /*!< Specifies the serial clock steady state.
                                         This parameter can be a value of @ref SSP_Clock_Polarity */
  uint32_t SSP_DataSize;            /*!< Specifies the SSP data size.
                                         This parameter can be a value of @ref SSP_data_size */
  uint32_t SSP_SOD;                 /*!< Specifies the Slave-mode output disable.
                                         This parameter can be a value of @ref SSP slave mode */
  uint32_t SSP_Mode;                /*!< Specifies the SSP operating mode.
                                         This parameter can be a value of @ref SSP_mode */
  uint32_t SSP_NSS;                 /*!< Specifies whether the NSS signal is managed by
                                         hardware (NSS pin) or by software using the SSI bit.
                                         This parameter can be a value of @ref SSP_Slave_Select_management */
  uint32_t SSP_LBM;                 /*!< Specifies whether the Loopback mode. 
                                         This parameter can be a value of @ref SSP_Loop back mode */

  uint32_t SSP_SSE;                 /*!<  */

  uint32_t SSP_BaudRatePrescaler;   /*!< Specifies the Baud Rate prescaler value which will be
                                         used to configure the transmit and receive SCK clock.
                                         This parameter can be a value of @ref SSP_BaudRate_Prescaler.
                                         @note The communication clock is derived from the master
                                               clock. The slave clock does not need to be set. */
}SSP_InitTypeDef;



/** @defgroup SSP_Exported_Constants
  * @{
  */

#define IS_SSP_ALL_PERIPH(PERIPH) (((PERIPH) == SPI0) || \
                                   ((PERIPH) == SPI1))

#define SSP_SCR(X)  (X<<8)
#define IS_SSP_SERIALCLOCKRATE(RATE) (((RATE) > (0x0000FFFF)) && \
                                     ((RATE) < (0x00010000))) 

/** @defgroup SSP_Clock_Phase 
  * @{
  */

#define SSP_CPHA_1Edge                  ((uint32_t)0x00)
#define SSP_CPHA_2Edge                  ((uint32_t)0x80)
#define IS_SSP_CPHA(CPHA) (((CPHA) == SSP_CPHA_1Edge) || \
                           ((CPHA) == SSP_CPHA_2Edge))
/**
  * @}
  */
/** @defgroup SSP_Clock_Polarity 
  * @{
  */

#define SSP_CPOL_Low                    ((uint32_t)0x00)
#define SSP_CPOL_High                   ((uint32_t)0x40)
#define IS_SSP_CPOL(CPOL) (((CPOL) == SSP_CPOL_Low) || \
                           ((CPOL) == SSP_CPOL_High))
/**
  * @}
  */

/** @defgroup SSP_Frame_Format 
  * @{
  */
#define SSP_FrameFormat_MO ((uint32_t)0x00000000)
#define SSP_FrameFormat_TI ((uint32_t)0x00000010)
#define SSP_FrameFormat_NA ((uint32_t)0x00000020)

#define IS_SSP_FRAMEFORMAT(TYPE) (((TYPE) == SSP_FrameFormat_MO) || \
                                  ((TYPE) == SSP_FrameFormat_TI) || \
                                  ((TYPE) == SSP_FrameFormat_NA))
/**
  * @}
  */ 

/** @defgroup SSP_data_size 
  * @{
  */
#define SSP_DataSize_4b                ((uint32_t)0x3)
#define SSP_DataSize_5b                ((uint32_t)0x4)
#define SSP_DataSize_6b                ((uint32_t)0x5)
#define SSP_DataSize_7b                ((uint32_t)0x6)
#define SSP_DataSize_8b                ((uint32_t)0x7)
#define SSP_DataSize_9b                ((uint32_t)0x8)
#define SSP_DataSize_10b               ((uint32_t)0x9)
#define SSP_DataSize_11b               ((uint32_t)0xA)
#define SSP_DataSize_12b               ((uint32_t)0xB)
#define SSP_DataSize_13b               ((uint32_t)0xC)
#define SSP_DataSize_14b               ((uint32_t)0xD)
#define SSP_DataSize_15b               ((uint32_t)0xE)
#define SSP_DataSize_16b               ((uint32_t)0xF)
#define IS_SSP_DATASIZE(DATASIZE) (((DATASIZE) == SSP_DataSize_16b) || \
                                   ((DATASIZE) == SSP_DataSize_15b) || \
                                   ((DATASIZE) == SSP_DataSize_14b) || \
                                   ((DATASIZE) == SSP_DataSize_13b) || \
                                   ((DATASIZE) == SSP_DataSize_12b) || \
                                   ((DATASIZE) == SSP_DataSize_11b) || \
                                   ((DATASIZE) == SSP_DataSize_10b) || \
                                   ((DATASIZE) == SSP_DataSize_9b)  || \
                                   ((DATASIZE) == SSP_DataSize_8b)  || \
                                   ((DATASIZE) == SSP_DataSize_7b)  || \
                                   ((DATASIZE) == SSP_DataSize_6b)  || \
                                   ((DATASIZE) == SSP_DataSize_5b)  || \
                                   ((DATASIZE) == SSP_DataSize_4b))
/**
  * @}
  */ 

/** @defgroup SSP_sod 
  * @{
  */

#define SSP_SOD_RESET    ((uint32_t)0x00)
#define SSP_SOD_SET      ((uint32_t)0x08)
#define IS_SSP_SOD(SOD)  (((SOD) == SSP_SOD_ENABLE) || \
                          ((SOD) == SSP_SOD_DISABLE))
/**
  * @}
  */

/** @defgroup SSP_mode 
  * @{
  */

#define SSP_Mode_Master ((uint32_t)0x00)
#define SSP_Mode_Slave  ((uint32_t)0x04)
#define IS_SSP_MODE(MODE) (((MODE) == SSP_Mode_Master) || \
                           ((MODE) == SSP_Mode_Slave))
/**
  * @}
  */



/** @defgroup SSP_Slave_Select_management 
  * @{
  */
#define SSP_NSS_Soft    ((uint32_t)0x00)
#define SSP_NSS_Hard    ((uint32_t)0x02)
#define IS_SSP_NSS(NSS) (((NSS) == SSP_NSS_Soft) || \
                         ((NSS) == SSP_NSS_Hard))
/**
  * @}
  */ 

/** @defgroup SSP_Synchronous serial port Enable
  * @{
  */

#define SSP_SSE_SET                     ((uint32_t)0x02)
#define SSP_SSE_RESET                   ((uint32_t)0x00)
#define IS_SSP_SSE(SSE) (((SSE) == SSP_SSE_SET) || \
                           ((SSE) == SSP_SSE_RESET))
/**
  * @}
  */

/** @defgroup SSP_BaudRate_Prescaler 
  * @{
  */

#define SSP_BaudRatePrescaler_2         ((uint32_t)0x0002)
#define SSP_BaudRatePrescaler_4         ((uint32_t)0x0004)
#define SSP_BaudRatePrescaler_8         ((uint32_t)0x0008)
#define SSP_BaudRatePrescaler_16        ((uint32_t)0x0010)
#define SSP_BaudRatePrescaler_32        ((uint32_t)0x0020)
#define SSP_BaudRatePrescaler_64        ((uint32_t)0x0040)
#define SSP_BaudRatePrescaler_128       ((uint32_t)0x0080)
#define SSP_BaudRatePrescaler_254       ((uint32_t)0x00FE)
#define IS_SSP_BAUDRATE_PRESCALER(PRESCALER) (((PRESCALER) == SSP_BaudRatePrescaler_2) || \
                                              ((PRESCALER) == SSP_BaudRatePrescaler_4) || \
                                              ((PRESCALER) == SSP_BaudRatePrescaler_8) || \
                                              ((PRESCALER) == SSP_BaudRatePrescaler_16) || \
                                              ((PRESCALER) == SSP_BaudRatePrescaler_32) || \
                                              ((PRESCALER) == SSP_BaudRatePrescaler_64) || \
                                              ((PRESCALER) == SSP_BaudRatePrescaler_128) || \
                                              ((PRESCALER) == SSP_BaudRatePrescaler_254))
/**
  * @}
  */ 

/** @defgroup SSP FLAG 
  * @{
  */
#define SSP_FLAG_BSY  ((uint32_t)0x10)   
#define SSP_FLAG_RFF  ((uint32_t)0x08)   
#define SSP_FLAG_RNE  ((uint32_t)0x04)
#define SSP_FLAG_TNF  ((uint32_t)0x02)
#define SSP_FLAG_TFE  ((uint32_t)0x01)
#define IS_SSP_GET_FLAG(FLAG)                (((FLAG) == SSP_FLAG_BSY) || \
                                              ((FLAG) == SSP_FLAG_RFF) || \
                                              ((FLAG) == SSP_FLAG_RNE) || \
                                              ((FLAG) == SSP_FLAG_TNF) || \
                                              ((FLAG) == SSP_FLAG_TFE)) 
/**
  * @}
  */
/** @defgroup SSP interrupts mask
  * @{
  */
#define SSP_IT_TXIM  ((uint32_t)0x08)   
#define SSP_IT_RXIM  ((uint32_t)0x04)
#define SSP_IT_RTIM  ((uint32_t)0x02)
#define SSP_IT_RORIM ((uint32_t)0x01)
#define IS_SSP_CONFIG_IT(IT) ((IT) < (0x10)) 
/**
  * @}
  */
/** @defgroup SSP_Slave_Select_management 
  * @{
  */
#define SSP_LBM_RESET  ((uint32_t)0x00)
#define SSP_LBM_SET    ((uint32_t)0x01)
#define IS_SSP_LBM(LBM) (((LBM) == SSP_LBM_NORMAL) || \
                         ((LBM) == SSP_NSS_ENABLE))
/**
  * @}
  */ 

/** @defgroup SSP_DMA_transfer_requests 
  * @{
  */

#define SSP_DMAReq_Tx               ((uint32_t)0x0002)
#define SSP_DMAReq_Rx               ((uint32_t)0x0001)
#define IS_SSP_DMAREQ(DMAREQ) (((DMAREQ) == SSP_DMAReq_Tx) || \
                           ((DMAREQ) == SSP_DMAReq_Rx))
/**
  * @}
  */

/** @defgroup SSP_NSS_internal_software_management 
  * @{
  */

#define SSP_NSSInternalSoft_Set         ((uint32_t)0x01)
#define SSP_NSSInternalSoft_Reset       ((uint32_t)0x00)
#define IS_SSP_NSS_INTERNAL(INTERNAL) (((INTERNAL) == SSP_NSSInternalSoft_Set) || \
                                       ((INTERNAL) == SSP_NSSInternalSoft_Reset))
/**
  * @}
  */
/** @defgroup SSP_Slave_Select_management 
  * @{
  */
#define SSP_CLEAR_IT_RTIC_RORIC  ((uint32_t)0x03)
#define SSP_CLEAR_IT_RTIC  ((uint32_t)0x02)
#define SSP_CLEAR_IT_RORIC ((uint32_t)0x01)
#define IS_SSP_CLEAR_IT(CLEAR) (((CLEAR) == SSP_CLEAR_IT_RTIC_RORIC) || \
                                ((CLEAR) == SSP_CLEAR_IT_RTIC) || \
                                ((CLEAR) == SSP_CLEAR_IT_RORIC))
/**
  * @}
  */ 

/**
  * @}
  */

/** @defgroup SSP_Exported_Macros
  * @{
  */

/**
  * @}
  */

/** @defgroup SSP_Exported_Functions
  * @{
  */
	
void SSP_DeInit(SSP_TypeDef* SSPx);
void SSP_Init(SSP_TypeDef* SSPx, SSP_InitTypeDef* SSP_InitStruct);
void SSP_StructInit(SSP_InitTypeDef* SSP_InitStruct);
void SSP_NSSInternalSoftwareConfig(SSP_TypeDef* SSPx, uint16_t SSP_NSSInternalSoft);
void SSP_SSOutputCmd(SSP_TypeDef* SSPx, FunctionalState NewState);
void SSP_DataSizeConfig(SSP_TypeDef* SSPx, uint16_t SSP_DataSize);
void SSP_ITConfig(SSP_TypeDef* SSPx, uint32_t SSP_IT, FunctionalState NewState);
void SSP_DMACmd(SSP_TypeDef* SSPx, uint32_t SSP_DMAReq, FunctionalState NewState);
void SSP_SendData(SSP_TypeDef* SSPx, uint16_t Data);
uint16_t SSP_ReceiveData(SSP_TypeDef* SSPx);
FlagStatus SSP_GetFlagStatus(SSP_TypeDef* SSPx, uint32_t SSP_FLAG);
ITStatus SSP_GetITStatus(SSP_TypeDef* SSPx, uint32_t SSP_IT);
void SSP_ClearIT_Bit(SSP_TypeDef* SSPx, uint32_t SSP_CLEAR_IT);

#ifdef __cplusplus
    }
#endif

#endif // __W7500X_SSP_H
/**
  * @}
  */

/**
  * @}
  */
