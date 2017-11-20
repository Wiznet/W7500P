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
  * @file    W7500x_stdPeriph_Driver/src/W7500x_ssp.c
  * @author  IOP Team
  * @version v1.0.0
  * @date    01-May-2015
  * @brief   This file contains all the functions prototypes for the ssp
  *          firmware library.
  ******************************************************************************
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "W7500x_ssp.h"


/** @addtogroup W7500x_Periph_Driver
  * @{
  */

/** @defgroup SSP
  * @brief SSP driver modules
  * @{
  */


/* Private typedef -----------------------------------------------------------*/


/* Private define ------------------------------------------------------------*/
/* SSP SOD mask */
#define CR1_SOD_Set         ((uint32_t)0x0004)
#define CR1_SOD_Reset       ((uint32_t)0xFFFB)


/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/** @defgroup SSP_Private_Functions
  * @{
  */ 

  
  
  
/**
 * @brief  Deinitializes the SSPx peripheral registers to their default
 *         reset values (Affects also the I2Ss).
 * @param  SSPx: where x can be 1 or 2 to select the SSP peripheral.
 * @retval None
 */
void SSP_DeInit(SSP_TypeDef* SSPx)
{
    /* Check the parameters */
    assert_param(IS_SSP_ALL_PERIPH(SSPx));

    SSPx->CR0 = 0x00;
    SSPx->CR1 = 0x00; // SSE Enable = reset
    SSPx->DR  = 0x00;
    SSPx->CPSR = 0x00;
    SSPx->IMSC = 0x00;
    SSPx->DMACR= 0x00;

}

/**
 * @brief  Fills each SSP_InitStruct member with its default value.
 * @param  SSP_InitStruct : pointer to a SSP_InitTypeDef structure which will be initialized.
 * @retval None
 */
void SSP_StructInit(SSP_InitTypeDef* SSP_InitStruct)
{
    /*--------------- Reset SSP init structure parameters values -----------------*/
    /* Initialize the SSP_SerialClockRate member */
    SSP_InitStruct->SSP_SerialClockRate = 0x00;
    /* initialize the SSP_FrameFormat member */
    SSP_InitStruct->SSP_FrameFormat = SSP_FrameFormat_MO;
    /* Initialize the SSP_CPHA member */
    SSP_InitStruct->SSP_CPHA = SSP_CPHA_1Edge;
    /* Initialize the SSP_CPOL member */
    SSP_InitStruct->SSP_CPOL = SSP_CPOL_Low;
    /* initialize the SSP_DataSize member */
    SSP_InitStruct->SSP_DataSize = SSP_DataSize_8b;
    /* Initialize the SSP_SerialOutputDisable member */
    SSP_InitStruct->SSP_SOD = SSP_SOD_RESET;
    /* initialize the SSP_Mode member */
    SSP_InitStruct->SSP_Mode = SSP_Mode_Master;
    /* Initialize the SSP_NSS member */
    SSP_InitStruct->SSP_NSS = SSP_NSS_Hard;
    /* Initialize the SSP_Synchoronous Serial port member */
    SSP_InitStruct->SSP_SSE = SSP_SSE_SET;
    /* Initialize the SSP_LoopBackMode member */
    SSP_InitStruct->SSP_LBM = SSP_LBM_RESET;
    /* Initialize the SSP_BaudRatePrescaler member */
    SSP_InitStruct->SSP_BaudRatePrescaler = SSP_BaudRatePrescaler_4;
}

/**
 * @brief  Initializes the SSPx peripheral according to the specified
 *         parameters in the SSP_InitStruct.
 * @param  SSPx: where x can be 1 or 2 to select the SSP peripheral.
 * @param  SSP_InitStruct: pointer to a SSP_InitTypeDef structure that
 *         contains the configuration information for the specified SSP peripheral.
 * @retval None
 */
void SSP_Init(SSP_TypeDef* SSPx, SSP_InitTypeDef* SSP_InitStruct)
{
    uint32_t tmpreg = 0;

    /* check the parameters */
    assert_param(IS_SSP_ALL_PERIPH(SSPx));

    /* Check the SSP parameters */
    assert_param(IS_SSP_SERIALCLOCKRATE(SSP_InitStruct->SSP_SerialClockRate));
    assert_param(IS_SSP_FRAMEFORMAT(SSP_InitStruct->SSP_FrameFormat));
    assert_param(IS_SSP_CPHA(SSP_InitStruct->SSP_CPHA));
    assert_param(IS_SSP_CPOL(SSP_InitStruct->SSP_CPOL));
    assert_param(IS_SSP_DATASIZE(SSP_InitStruct->SSP_DataSize));
    assert_param(IS_SSP_SOD(SSP_InitStruct->SSP_SOD));
    assert_param(IS_SSP_MODE(SSP_InitStruct->SSP_Mode));
    assert_param(IS_SSP_NSS(SSP_InitStruct->SSP_NSS));
    assert_param(IS_SSP_LBM(SSP_InitStruct->SSP_LBM));
    assert_param(IS_SSP_SSE(SSP_InitStruct->SSP_SSE));
    assert_param(IS_SSP_BAUDRATE_PRESCALER(SSP_InitStruct->SSP_BaudRatePrescaler));

    /*---------------------------- SSPx CR0 Configuration ------------------------*/
    /* Get the SSPx CR0 value */
    tmpreg = SSPx->CR0;
    /* Clear  bits */
    //tmpreg &= CR1_CLEAR_Mask;
    tmpreg |= (uint32_t)(SSP_InitStruct->SSP_SerialClockRate | SSP_InitStruct->SSP_FrameFormat |
            SSP_InitStruct->SSP_CPHA | SSP_InitStruct->SSP_CPOL | SSP_InitStruct->SSP_DataSize );
    //printf("CR0: %.8X \r\n",tmpreg);
    /* Write to SSPx CR0 */
    SSPx->CR0 = tmpreg;

    /*---------------------------- SSPx CR1 Configuration ------------------------*/
    /* Write to SSPx CR1 */
    tmpreg = SSPx->CR1;
    /* Clear  bits */
    //tmpreg &= CR1_CLEAR_Mask;
    tmpreg |= (uint32_t)(SSP_InitStruct->SSP_SOD | SSP_InitStruct->SSP_Mode |
            SSP_InitStruct->SSP_NSS | SSP_InitStruct->SSP_SSE | SSP_InitStruct->SSP_LBM );
    SSPx->CR1 = tmpreg;
    //printf("CR1: %.8X \r\n",tmpreg);
    /*---------------------------- SSPx Clock prescal register ------------------------*/
    SSPx->CPSR = SSP_InitStruct->SSP_BaudRatePrescaler;

}



/**
 * @brief  Enables or disables the specified SSP/I2S interrupts.
 * @param  SSPx: where x can be
 *   - SSP0, SSP1
 * @param  SSP_IT: specifies the SSP interrupt source to be enabled or disabled.
 *   This parameter can be one of the following values:
 *     @arg SSP_IT_TXIM: Tx FIFO interrupt mask
 *     @arg SSP_IT_RXIM: Rx FIFO interrupt mask
 *     @arg SSP_IT_RTIM: RX Timeout interrupt mask
 *     @arg SSP_IT_RORIM: RX overrun interrupt mask
 * @param  NewState: new state of the specified SSP/I2S interrupt.
 *   This parameter can be: ENABLE or DISABLE.
 * @retval None
 */
void SSP_ITConfig(SSP_TypeDef* SSPx, uint32_t SSP_IT, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_SSP_ALL_PERIPH(SSPx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));
    assert_param(IS_SSP_CONFIG_IT(SSP_IT));


    if (NewState != DISABLE)
    {
        /* Enable the selected SSP/I2S interrupt */
        SSPx->IMSC |= SSP_IT;
    }
    else
    {
        /* Disable the selected SSP/I2S interrupt */
        SSPx->IMSC &= ~SSP_IT;
    }
}

/**
 * @brief  Enables or disables the SSPx/I2Sx DMA interface.
 * @param  SSPx: where x can be
 *   - SSP0, SSP1
 * @param  SSP_DMAReq: specifies the SSP DMA transfer request to be enabled or disabled.
 *   This parameter can be any combination of the following values:
 *     @arg SSP_DMAReq_Tx: Tx buffer DMA transfer request
 *     @arg SSP_DMAReq_Rx: Rx buffer DMA transfer request
 * @param  NewState: new state of the selected SSP DMA transfer request.
 *   This parameter can be: ENABLE or DISABLE.
 * @retval None
 */
void SSP_DMACmd(SSP_TypeDef* SSPx, uint32_t SSP_DMAReq, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_SSP_ALL_PERIPH(SSPx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));
    assert_param(IS_SSP_DMAREQ(SSP_DMAReq));
    if (NewState != DISABLE)
    {
        /* Enable the selected SSP DMA requests */
        SSPx->DMACR |= SSP_DMAReq;
    }
    else
    {
        /* Disable the selected SSP/I2S DMA requests */
        SSPx->DMACR &= ~SSP_DMAReq;
    }
}

/**
 * @brief  Transmits a Data through the SSPx/I2Sx peripheral.
 * @param  SSPx: where x can be
 *   - SSP0, SSP1
 * @param  Data : Data to be transmitted.
 * @retval None
 */
void SSP_SendData(SSP_TypeDef* SSPx, uint16_t Data)
{
    /* Check the parameters */
    assert_param(IS_SSP_ALL_PERIPH(SSPx));

    /* Write in the DR register the data to be sent */
    SSPx->DR = Data;
}

/**
 * @brief  Returns the most recent received data by the SSPx/I2Sx peripheral.
 * @param  SSPx: where x can be
 *   - SSP0, SSP1
 * @retval The value of the received data.
 */
uint16_t SSP_ReceiveData(SSP_TypeDef* SSPx)
{
    /* Check the parameters */
    assert_param(IS_SSP_ALL_PERIPH(SSPx));

    /* Return the data in the DR register */
    return SSPx->DR;
}

/**
 * @brief  Configures internally by software the NSS pin for the selected SSP.
 * @param  SSPx: where x can be 1 or 2 to select the SSP peripheral.
 * @param  SSP_NSSInternalSoft: specifies the SSP NSS internal state.
 *   This parameter can be one of the following values:
 *     @arg SSP_NSSInternalSoft_Set: Set NSS pin internally
 *     @arg SSP_NSSInternalSoft_Reset: Reset NSS pin internally
 * @retval None
 */
void SSP_NSSInternalSoftwareConfig(SSP_TypeDef* SSPx, uint16_t SSP_NSSInternalSoft)
{
    /* Check the parameters */
    assert_param(IS_SSP_ALL_PERIPH(SSPx));
    assert_param(IS_SSP_NSS_INTERNAL(SSP_NSSInternalSoft));
    if (SSP_NSSInternalSoft != SSP_NSSInternalSoft_Reset)
    {
        /* Set NSS pin internally by software */
        SSPx->CR1 |= SSP_NSSInternalSoft_Set;
    }
    else
    {
        /* Reset NSS pin internally by software */
        SSPx->CR1 &= SSP_NSSInternalSoft_Reset;
    }
}

/**
 * @brief  Enables or disables the SS output for the selected SSP.
 * @param  SSPx: where x can be 1 or 2 to select the SSP peripheral.
 * @param  NewState: new state of the SSPx SS output.
 *   This parameter can be: ENABLE or DISABLE.
 * @retval None
 */
void SSP_SSOutputCmd(SSP_TypeDef* SSPx, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_SSP_ALL_PERIPH(SSPx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));
    if (NewState != DISABLE)
    {
        /* Enable the selected SSP SS output */
        SSPx->CR1 |= CR1_SOD_Set;
    }
    else
    {
        /* Disable the selected SSP SS output */
        SSPx->CR1 &= CR1_SOD_Reset;
    }
}

/**
 * @brief  Configures the data size for the selected SSP.
 * @param  SSPx: where x can be 1 or 2 to select the SSP peripheral.
 * @param  SSP_DataSize: specifies the SSP data size.
 *   This parameter can be one of the following values:
 *     @arg from SSP_DataSize_16b: Set data frame format to 16bit
 *     @arg to SSP_DataSize_4b: Set data frame format to 8bit
 * @retval None
 */
void SSP_DataSizeConfig(SSP_TypeDef* SSPx, uint16_t SSP_DataSize)
{
    /* Check the parameters */
    assert_param(IS_SSP_ALL_PERIPH(SSPx));
    assert_param(IS_SSP_DATASIZE(SSP_DataSize));
    /* Clear DFF bit */
    SSPx->CR0 &= ~SSP_DataSize_16b;
    /* Set new DFF bit value */
    SSPx->CR0 |= SSP_DataSize;
}



/**
 * @brief  Checks whether the specified SSP flag is set or not.
 * @param  SSPx: where x can be
 *   - SSP0, SSP1
 * @param  SSP_FLAG: specifies the SSP flag to check.
 *   This parameter can be one of the following values:
 *     @arg SSP_FLAG_BSY : BUSY flag
 *     @arg SSP_FLAG_RFF : RX FIFO full flag
 *     @arg SSP_FLAG_RNE : RX FIFO not empty flag
 *     @arg SSP_FLAG_TNF : TX FIFO not full flag
 *     @arg SSP_FLAG_TFE : TX FIFO empty flag
 * @retval The new state of SSP_FLAG (SET or RESET).
 */
FlagStatus SSP_GetFlagStatus(SSP_TypeDef* SSPx, uint32_t SSP_FLAG)
{
    FlagStatus bitstatus = RESET;
    /* Check the parameters */
    assert_param(IS_SSP_ALL_PERIPH(SSPx));
    assert_param(IS_SSP_GET_FLAG(SSP_FLAG));
    /* Check the status of the specified SSP/I2S flag */
    if ((SSPx->SR & SSP_FLAG))
    {
        /* SSP_FLAG is set */
        bitstatus = SET;
    }
    else
    {
        /* SSP__FLAG is reset */
        bitstatus = RESET;
    }
    /* Return the SSP_I2S_FLAG status */
    return  bitstatus;
}


/**
 * @brief  Checks whether the specified SSP interrupt has occurred or not.
 * @param  SSPx: where x can be
 *   - SSP0, SSP1
 * @param  SSP_IT: specifies the SSP interrupt source to check.
 *   This parameter can be one of the following values:
 *     @arg SSP_IT_TXIM: Tx FIFO interrupt mask
 *     @arg SSP_IT_RXIM: Rx FIFO interrupt mask
 *     @arg SSP_IT_RTIM: RX Timeout interrupt mask
 *     @arg SSP_IT_RORIM: RX overrun interrupt mask
 * @retval The new state of SSP_IT (SET or RESET).
 */
ITStatus SSP_GetITStatus(SSP_TypeDef* SSPx, uint32_t SSP_IT)
{
    ITStatus bitstatus = RESET;

    /* Check the parameters */
    assert_param(IS_SSP_ALL_PERIPH(SSPx));
    assert_param(IS_SSP_GET_IT(SSP_IT));

    /* Check the status of the specified SSP interrupt */
    if (SSPx->MIS & SSP_IT)
    {
        /* SSP_IT is set */
        bitstatus = SET;
    }
    else
    {
        /* SSP_IT is reset */
        bitstatus = RESET;
    }
    /* Return the SSP_IT status */
    return bitstatus;
}

/**
 * @brief  Clears the SSPx CRC Error (CRCERR) interrupt pending bit.
 * @param  SSPx: where x can be
 *   - SSP0, SSP1
 * @param  SSP_IT: specifies the SSP interrupt pending bit to clear.
 * @note
 *   - SSP_CLEAR_IT_RORIC : Clear the RUNOVER
 *   - SSP_CLEAR_IT_RTIC  : Clear the interrupts ???
 * @retval None
 */
void SSP_ClearIT_Bit(SSP_TypeDef* SSPx, uint32_t SSP_CLEAR_IT)
{
    /* Check the parameters */
    assert_param(IS_SSP_ALL_PERIPH(SSPx));
    assert_param(IS_SSP_CLEAR_IT(SSP_IT));

    /* Clear the selected SSP  interrupt pending bit */
    SSPx->ICR = SSP_CLEAR_IT;
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
