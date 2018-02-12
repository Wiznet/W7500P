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
  * @file    W7500x_stdPeriph_Driver/inc/W7500x_gpio.h
  * @author  IOP Team
  * @version V1.0.5
  * @date    05-June-2015
  * @brief   This file contains all the functions prototypes for the GPIO 
  *          firmware library.
  ******************************************************************************
  * @par Revision history
  *    <2015/06/03> Update about Interrupt (add Interrupt Function)
  *                         - Add GPIOPol_TypeDef
  *                         - Add GPIOSet_TypeDef
  *                         - Add GPIO_INT_Enable_Bits Function
  *                         - Add GPIO_INT_Enable Function
  *                         - Add GPIO_INT_Polarity_Bits Function
  *                         - Add GPIO_INT_Polarity Function
  *                         - Add GPIO_INT_Clear Function
  *                         - Add GPIO_Read_INTstatus Function
  *                         - Add GPIO_INT_Configuration Function
  *                         Add GPIO_Configuration Function
  *    <2015/05/01> 1st Release
  *
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __W7500X_GPIO_H
#define __W7500X_GPIO_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "W7500x.h"


#define GPIO_Pin_0      (uint16_t)(0x01 <<  0)     // Pin  0 Selected
#define GPIO_Pin_1      (uint16_t)(0x01 <<  1)     // Pin  1 Selected
#define GPIO_Pin_2      (uint16_t)(0x01 <<  2)     // Pin  2 Selected
#define GPIO_Pin_3      (uint16_t)(0x01 <<  3)     // Pin  3 Selected
#define GPIO_Pin_4      (uint16_t)(0x01 <<  4)     // Pin  4 Selected
#define GPIO_Pin_5      (uint16_t)(0x01 <<  5)     // Pin  5 Selected
#define GPIO_Pin_6      (uint16_t)(0x01 <<  6)     // Pin  6 Selected
#define GPIO_Pin_7      (uint16_t)(0x01 <<  7)     // Pin  7 Selected
#define GPIO_Pin_8      (uint16_t)(0x01 <<  8)     // Pin  8 Selected
#define GPIO_Pin_9      (uint16_t)(0x01 <<  9)     // Pin  9 Selected
#define GPIO_Pin_10     (uint16_t)(0x01 << 10)     // Pin 10 Selected
#define GPIO_Pin_11     (uint16_t)(0x01 << 11)     // Pin 11 Selected
#define GPIO_Pin_12     (uint16_t)(0x01 << 12)     // Pin 12 Selected
#define GPIO_Pin_13     (uint16_t)(0x01 << 13)     // Pin 13 Selected
#define GPIO_Pin_14     (uint16_t)(0x01 << 14)     // Pin 14 Selected
#define GPIO_Pin_15     (uint16_t)(0x01 << 15)     // Pin 15 Selected
#define GPIO_Pin_All    (uint16_t)(0xFFFF)         // All pins Selected


#define IS_GPIO_PIN(PIN)        ((PIN) != (uint16_t)0x00)
#define IS_GET_GPIO_PIN(PIN)    (((PIN) == GPIO_Pin_0)  || ((PIN) == GPIO_Pin_1)  || \
                                (((PIN) == GPIO_Pin_2)  || ((PIN) == GPIO_Pin_3)  || \
                                (((PIN) == GPIO_Pin_4)  || ((PIN) == GPIO_Pin_5)  || \
                                (((PIN) == GPIO_Pin_6)  || ((PIN) == GPIO_Pin_7)  || \
                                (((PIN) == GPIO_Pin_8)  || ((PIN) == GPIO_Pin_9)  || \
                                (((PIN) == GPIO_Pin_10) || ((PIN) == GPIO_Pin_11) || \
                                (((PIN) == GPIO_Pin_12) || ((PIN) == GPIO_Pin_13) || \
                                (((PIN) == GPIO_Pin_14) || ((PIN) == GPIO_Pin_15) )


#define IS_GPIO_ALL_PERIPH(PERIPH)  (((PERIPH) == GPIOA) || ((PERIPH) == GPIOB) || \
                                     ((PERIPH) == GPIOC))

                                     
/** @addtogroup W7500x_Periph_Driver
  * @{
  */

/** @addtogroup GPIO
  * @{
  */                                      
typedef enum
{
    GPIO_Mode_IN    = 0x00, /*!< GPIO Input Mode                 */
    GPIO_Mode_OUT   = 0x01, /*!< GPIO Output Mode                */
    GPIO_Mode_AF    = 0x02 /*!< GPIO Alternate function Mode    */
}GPIOMode_TypeDef;

typedef enum
{
    GPIO_PuPd_UP = Px_PCR_PUPD_UP,
    GPIO_PuPd_DOWN = Px_PCR_PUPD_DOWN,
	GPIO_DS = Px_PCR_DS_HIGH,
	GPIO_IE = Px_PCR_IE,
    GPIO_SUMMIT = Px_PCR_CS_SUMMIT
}GPIOPad_TypeDef;


#define IS_GPIO_PUPU(PUPD)  (((PUPD) == GPIO_PuPd_UP) || ((PUPD) == GPIO_PuPd_DOWN))

typedef struct
{
    uint32_t GPIO_Pin;
    GPIOMode_TypeDef GPIO_Mode;
    GPIOPad_TypeDef GPIO_Pad;
}GPIO_InitTypeDef;

typedef enum
{
    Falling = 0,
    Rising = 1
}GPIOPol_TypeDef;

typedef enum
{
    Reset = 0,
    Set = 1
}GPIOSet_TypeDef;

typedef enum
{
    Bit_RESET = 0,
    Bit_SET
}BitAction;

typedef enum
{
    PAD_PA=0,
    PAD_PB,
    PAD_PC,
	  PAD_PD
}PAD_Type;

typedef enum
{
    PAD_AF0    = Px_AFSR_AF0,
    PAD_AF1    = Px_AFSR_AF1,
    PAD_AF2    = Px_AFSR_AF2,
    PAD_AF3    = Px_AFSR_AF3
}PAD_AF_TypeDef;

#define IS_PAD_TYPE(Px)  (((Px) == PAD_PA) || ((Px) == PAD_PB) || \
                          ((Px) == PAD_PC))

#define IS_PA_NUM(NUM) (((NUM)>=0) && ((NUM)<15))
#define IS_PB_NUM(NUM) ((((NUM)>=0) && ((NUM)<7)) || (((NUM)>=14) && ((NUM)<16))) /* MDIO+MDC on 14+15*/

#define IS_PC_NUM(NUM) ((((NUM)>=0) && ((NUM)<7)) || (((NUM)>=8) && ((NUM)<16)))

#define IS_PAD_AF(AF)       (((AF) == PAD_AF0) || ((AF) == PAD_AF1) || \
                             ((AF) == PAD_AF2) || ((AF) == PAD_AF3))


#define IS_GPIO_BIT_ACTION(ACTION)  (((ACTION_ == Bit_RESET) || (ACTION) ==Bit_SET))

void GPIO_DeInit(GPIO_TypeDef* GPIOx);
void GPIO_Init(GPIO_TypeDef* GPIOx, GPIO_InitTypeDef* GPIO_InitStruct);
void GPIO_StructInit(GPIO_InitTypeDef* GPIO_InitStruct);
uint8_t GPIO_ReadInputDataBit(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);
uint16_t GPIO_ReadInputData(GPIO_TypeDef* GPIOx);
uint8_t GPIO_ReadOutputDataBit(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);
uint16_t GPIO_ReadOutputData(GPIO_TypeDef* GPIOx);
void GPIO_SetBits(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);
void GPIO_ResetBits(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);
void GPIO_WriteBit(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, BitAction BitVal);
void GPIO_Write(GPIO_TypeDef* GPIOx, uint16_t PortVal);
void GPIO_INT_Enable_Bits(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, GPIOSet_TypeDef SetValue);
void GPIO_INT_Enable(GPIO_TypeDef* GPIOx, GPIOSet_TypeDef SetValue);
void GPIO_INT_Polarity_Bits(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, GPIOPol_TypeDef Polarity);
void GPIO_INT_Polarity(GPIO_TypeDef* GPIOx, GPIOPol_TypeDef Polarity);
void GPIO_INT_Clear(GPIO_TypeDef* GPIOx);
uint8_t GPIO_Read_INTstatus(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);
void PAD_AFConfig(PAD_Type Px, uint16_t Pnum, PAD_AF_TypeDef P_AF);
void GPIO_Configuration(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, GPIOMode_TypeDef GPIO_Mode, PAD_AF_TypeDef P_AF);
void GPIO_INT_Configuration(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, GPIOPol_TypeDef Polarity);


#ifdef __cplusplus
 }
#endif

#endif //__W7500X_GPIO_H
/**
  * @}
  */

/**
  * @}
  */
