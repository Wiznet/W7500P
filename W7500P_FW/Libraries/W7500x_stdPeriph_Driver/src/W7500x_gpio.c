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
  * @file    W7500x_stdPeriph_Driver/src/W7500x_gpio.c    
  * @author  IOP Team
  * @version V1.0.5
  * @date    05-June-2015
  * @brief   This file contains all the functions prototypes for the gpio 
  *          firmware library.
  ******************************************************************************
  * @par Revision history
  *    <2015/06/03> Update about Interrupt (add Interrupt Function)
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

/*includes -------------------------------------------*/
#include "W7500x_gpio.h"

void GPIO_DeInit(GPIO_TypeDef* GPIOx)
{
    uint32_t i, loop =16;
    P_Port_Def *px_pcr;
    P_Port_Def *px_afsr;

    /* Check the parameters */
    assert_param(IS_GPIO_ALL_PERIPH(GPIOx));

    /* DeInit GPIOx Regsters */
    GPIOx->DATA = 0x0000;        
    GPIOx->DATAOUT = 0x0000;     
    //GPIOx->OUTENSET = 0x0000;    
    GPIOx->OUTENCLR = 0xFFFF;    
    //GPIOx->INTENSET = 0x0000;    
    GPIOx->INTENCLR = 0xFFFF;    
    GPIOx->INTTYPESET = 0x0000;  
    //GPIOx->INTTYPECLR = 0xFFFF;  
    //GPIOx->intpolset = 0x0000;   
    GPIOx->INTPOLCLR = 0xFFFF;   


    /* DeInit GPIOx 
     *      Pad Control Register
     *      Pad Extern interrupt Enable Register
     *      Pad Alternate Function Select Register
     */     
    if (GPIOx == GPIOA)
    {
        px_pcr = (P_Port_Def*)PA_PCR;
        px_afsr = (P_Port_Def*)PA_AFSR;
    }
    else if (GPIOx == GPIOB)
    {
        px_pcr = (P_Port_Def*)PB_PCR;
        px_afsr = (P_Port_Def*)PB_AFSR;
    }
    else // if  (GPIOx == GPIOC)
    {
        px_pcr = PC_PCR;
        px_afsr = PC_AFSR;
    }  

    for(i=0; i<loop; i++)
    {
        px_pcr->Port[i] = 0x60;
        px_afsr->Port[i] = PAD_AF0;

    }
}

void GPIO_Init(GPIO_TypeDef* GPIOx, GPIO_InitTypeDef* GPIO_InitStruct)
{
    uint32_t pinpos = 0x00, pos = 0x00, currentpin = 0x00, loop = 16;
    P_Port_Def *px_pcr;

    assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
    assert_param(IS_GPIO_PIN(GPIO_InitStruct->GPIO_Pin));
    assert_param(IS_GPIO_PUPD(GPIO_InitStruct->GPIO_PuPd));

    if      (GPIOx == GPIOA)       
    {
        px_pcr  =(P_Port_Def*)PA_PCR;
    }
    else if (GPIOx == GPIOB)        
    {
        px_pcr  = (P_Port_Def*)PB_PCR;
    }
    else 
    {
        px_pcr  = PC_PCR;
    }

    for(pinpos = 0x00; pinpos < loop; pinpos++)
    {
        pos = ((uint32_t)0x01) << pinpos;

        currentpin = (GPIO_InitStruct->GPIO_Pin) & pos;

        if(currentpin == pos)
        {
            if(GPIO_InitStruct->GPIO_Mode == GPIO_Mode_OUT)
            {
                GPIOx->OUTENSET |= pos;
            }
            else        // GPIO_Mode_In
            {
                GPIOx->OUTENCLR = pos;
            }

            // Configure pull-up pull-down bits 
            if(GPIO_InitStruct->GPIO_Pad & Px_PCR_PUPD_UP)
            {
                px_pcr->Port[pinpos] &= ~(Px_PCR_PUPD_UP | Px_PCR_PUPD_DOWN);
                px_pcr->Port[pinpos] |= Px_PCR_PUPD_UP;
            }
            else
            {
                px_pcr->Port[pinpos] &= ~(Px_PCR_PUPD_UP | Px_PCR_PUPD_DOWN);
                px_pcr->Port[pinpos] |= Px_PCR_PUPD_DOWN;
            }

            // Configure Driving stregnth selections bit 
            if(GPIO_InitStruct->GPIO_Pad & Px_PCR_DS_HIGH)
            {
                px_pcr->Port[pinpos] |= Px_PCR_DS_HIGH;
            }
            else
            {
                px_pcr->Port[pinpos] &= ~(Px_PCR_DS_HIGH);
            }

            // Configure Input buffer enable selection bit 
            if(GPIO_InitStruct->GPIO_Pad & Px_PCR_IE)
            {
                px_pcr->Port[pinpos] |= Px_PCR_IE;
            }
            else
            {
                px_pcr->Port[pinpos] &= ~(Px_PCR_IE);
            }

            // Configure input type (CMOS input or Summit trigger input) select bit 
            if(GPIO_InitStruct->GPIO_Pad & Px_PCR_CS_SUMMIT)
            {
                px_pcr->Port[pinpos] |= Px_PCR_CS_SUMMIT;
            }
            else
            {
                px_pcr->Port[pinpos] &= ~(Px_PCR_CS_SUMMIT);
            }
        }
    }
}

void GPIO_StructInit(GPIO_InitTypeDef* GPIO_InitStruct)
{
    GPIO_InitStruct->GPIO_Pin  = GPIO_Pin_All;
    GPIO_InitStruct->GPIO_Mode = GPIO_Mode_IN;
    GPIO_InitStruct->GPIO_Pad = (GPIOPad_TypeDef)(GPIO_SUMMIT|GPIO_IE|GPIO_PuPd_UP);
}


uint8_t GPIO_ReadInputDataBit(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
{
    uint8_t bitstatus = 0x00;

    assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
    assert_param(IS_GET_GPIO_PIN(GPIO_Pin));

    if((GPIOx->DATA & GPIO_Pin) != (uint32_t)Bit_RESET)
    {
        bitstatus = (uint8_t)Bit_SET;
    }
    else
    {
        bitstatus = (uint8_t)Bit_RESET;
    }

    return bitstatus;
}

uint16_t GPIO_ReadInputData(GPIO_TypeDef* GPIOx)
{
    assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
    return ((uint16_t)GPIOx->DATA);
}

uint8_t GPIO_ReadOutputDataBit(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
{
    uint8_t bitstatus = 0x00;

    assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
    assert_param(IS_GET_GPIO_PIN(GPIO_Pin));

    if((GPIOx->DATAOUT & GPIO_Pin) != (uint32_t)Bit_RESET)
    {
        bitstatus = (uint8_t)Bit_SET;
    }
    else
    {
        bitstatus = (uint8_t)Bit_RESET;
    }

    return bitstatus;
}
uint16_t GPIO_ReadOutputData(GPIO_TypeDef* GPIOx)
{
    /* Check the parameters */
    assert_param(IS_GPIO_ALLPERIPH(GPIOx));
    return ((uint16_t)GPIOx->DATAOUT);
}

void GPIO_SetBits(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
{
    /* Check the parameters */
    assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
    assert_param(IS_GPIO_PIN(GPIO_Pin)); 

    (GPIOx->LB_MASKED[(uint8_t)(GPIO_Pin)]) = GPIO_Pin;
    (GPIOx->UB_MASKED[(uint8_t)((GPIO_Pin)>>8)]) = GPIO_Pin;
}

void GPIO_ResetBits(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
{
    /* Check the parameters */
    assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
    assert_param(IS_GPIO_PIN(GPIO_Pin));

    (GPIOx->LB_MASKED[(uint8_t)(GPIO_Pin)]) = ~(GPIO_Pin);
    (GPIOx->UB_MASKED[(uint8_t)(GPIO_Pin>>8)]) = ~(GPIO_Pin);
}

void GPIO_WriteBit(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, BitAction BitVal)
{
    /* Check the parameters */
    assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
    assert_param(IS_GET_GPIO_PIN(GPIO_Pin));
    assert_param(IS_GPIO_BIT_ACTION(BitVal)); 

    (GPIOx->LB_MASKED[(uint8_t)(GPIO_Pin)]) = BitVal;
    (GPIOx->UB_MASKED[(uint8_t)((GPIO_Pin)>>8)]) = BitVal;
}

void GPIO_Write(GPIO_TypeDef* GPIOx, uint16_t PortVal)
{
    /* Check the parameters */
    assert_param(IS_GPIO_ALL_PERIPH(GPIOx));

    GPIOx->DATAOUT = PortVal;
}

void GPIO_INT_Enable_Bits(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, GPIOSet_TypeDef SetValue)
{
    /* Check the parameters */
    assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
    assert_param(IS_GET_GPIO_PIN(GPIO_Pin));
    
    GPIOx->INTTYPESET |= GPIO_Pin;

    if(SetValue == Set)
        GPIOx->INTENSET  |= GPIO_Pin;
    else //SetValue == Reset
        GPIOx->INTENCLR |= GPIO_Pin;
}

void GPIO_INT_Enable(GPIO_TypeDef* GPIOx, GPIOSet_TypeDef SetValue)
{
    /* Check the parameters */
    assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
    
    GPIOx->INTTYPESET = 0xffff;

    if(SetValue == Set)
        GPIOx->INTENSET = 0xffff;
    else //SetValue == Reset
        GPIOx->INTENCLR = 0xffff;
}

void GPIO_INT_Polarity_Bits(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, GPIOPol_TypeDef Polarity)
{
    /* Check the parameters */
    assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
    assert_param(IS_GET_GPIO_PIN(GPIO_Pin));

    if(Polarity == Rising)
        GPIOx->INTPOLSET  |= GPIO_Pin;
    else //Polarity == Falling
        GPIOx->INTPOLCLR |= GPIO_Pin;
}

void GPIO_INT_Polarity(GPIO_TypeDef* GPIOx, GPIOPol_TypeDef Polarity)
{
    /* Check the parameters */
    assert_param(IS_GPIO_ALL_PERIPH(GPIOx));

    if(Polarity == Rising)
        GPIOx->INTPOLSET = 0xffff;
    else //Polarity == Falling
        GPIOx->INTPOLCLR = 0xffff;
}

void GPIO_INT_Clear(GPIO_TypeDef* GPIOx)
{
    /* Check the parameters */
    assert_param(IS_GPIO_ALL_PERIPH(GPIOx));

    GPIOx->Interrupt.INTCLEAR = 0xffff;
}

uint8_t GPIO_Read_INTstatus(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
{
    uint8_t status = 0x0000;

    assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
    assert_param(IS_GET_GPIO_PIN(GPIO_Pin));

    if((GPIOx->Interrupt.INTSTATUS & GPIO_Pin) != (uint32_t)Bit_RESET)
    {
        status = (uint8_t)Bit_SET;
    }
    else
    {
        status = (uint8_t)Bit_RESET;
    }

    return status;
}

void PAD_AFConfig(PAD_Type Px, uint16_t GPIO_Pin, PAD_AF_TypeDef P_AF)
{
    int i;
    uint16_t idx =0x1;
    assert_param(IS_PAD_Type(Px));

    for(i=0;i<16;i++)
    {
        if(GPIO_Pin & (idx<<i))
        {
            if(Px == PAD_PA)
            {
                assert_param(IS_PA_NUM(i));
                PA_AFSR->Port[i] &= ~(0x03ul);
                PA_AFSR->Port[i] |= P_AF;
            }
            else if(Px == PAD_PB)
            {
                assert_param(IS_PB_NUM(i));
                PB_AFSR->Port[i] &= ~(0x03ul);
                PB_AFSR->Port[i] |= P_AF;
            }
            else 
            {
                assert_param(IS_PC_NUM(i));
                PC_AFSR->Port[i] &= ~(0x03ul);
                PC_AFSR->Port[i] |= P_AF;
            }				
        }
    }
}

/**
  * @brief GPIO Configuration Function
  */
void GPIO_Configuration(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, GPIOMode_TypeDef GPIO_Mode, PAD_AF_TypeDef P_AF)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    PAD_Type PADx;
    GPIO_StructInit(&GPIO_InitStructure);
    
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode;
    GPIO_Init(GPIOx, &GPIO_InitStructure);
	
    if(GPIOx == GPIOA)
    {       
        PADx = PAD_PA;
        PAD_AFConfig(PADx,GPIO_Pin, P_AF);
    }
    else if(GPIOx == GPIOB)
    {
        PADx = PAD_PB;
        PAD_AFConfig(PADx,GPIO_Pin, P_AF);
    }
    else 
    {
        PADx = PAD_PC;
        PAD_AFConfig(PADx,GPIO_Pin, P_AF);
    }
}


void GPIO_INT_Configuration(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, GPIOPol_TypeDef Polarity)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    PAD_Type PADx;
    GPIO_StructInit(&GPIO_InitStructure);
    
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
    GPIO_Init(GPIOx, &GPIO_InitStructure);

    assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
    assert_param(IS_GPIO_PIN(GPIO_InitStruct->GPIO_Pin));

    GPIOx->INTENSET  |= GPIO_Pin;
    GPIOx->INTTYPESET |= GPIO_Pin;
    
    GPIO_INT_Polarity_Bits(GPIOx, GPIO_Pin, Polarity);
	
    if(GPIOx == GPIOA)
    {       
        PADx = PAD_PA;
        PAD_AFConfig(PADx,GPIO_Pin, PAD_AF1);
        NVIC_EnableIRQ(PORT0_IRQn);
    }
    else if(GPIOx == GPIOB)
    {
        PADx = PAD_PB;
        PAD_AFConfig(PADx,GPIO_Pin, PAD_AF1);
        NVIC_EnableIRQ(PORT1_IRQn);
    }
    else
    {
        PADx = PAD_PC;
        PAD_AFConfig(PADx,GPIO_Pin, PAD_AF1);
        NVIC_EnableIRQ(PORT2_IRQn);
    }
}
