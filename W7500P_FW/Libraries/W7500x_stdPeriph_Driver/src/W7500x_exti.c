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
  * @file    W7500x_stdPeriph_Driver/src/W7500x_exti.c    
  * @author  IOP Team
  * @version v1.0.0
  * @date    26-AUG-2015
  * @brief   This file contains all the functions prototypes for the exti 
  *          firmware library.
  ******************************************************************************
  *
  ******************************************************************************
  */

/*include -------------------------------------*/
#include "W7500x_exti.h"
#include "W7500x_gpio.h"

/**
  * @brief  Deinitializes the EXTI peripheral registers to their default reset values.
  * @param  None
  * @retval None
  */
void EXTI_DeInit(void)
{
    uint32_t i;
    for(i=0; i<15; i++)
    {
        EXTI_PA->Port[i] = 0x00;
    }
    for(i=0; i<4; i++)
    {
        EXTI_PB->Port[i] = 0x00;
    }
		for(i=0; i<16; i++)
    {
				EXTI_PC->Port[i] = 0x00;
    }
}

/**
  * @brief  Initializes the EXTI peripheral according to the specified
  *         parameters in the EXTI_InitStruct.
  * @param  EXTI_InitStruct: pointer to a EXTI_InitTypeDef structure
  *         that contains the configuration information for the EXTI peripheral.
  * @retval None
  */
void EXTI_Init(PAD_Type Px, EXTI_InitTypeDef* EXTI_InitStruct)
{
    uint32_t pinpos = 0x00, pos = 0x00, currentpin = 0x00, loop = 16;
    P_Port_Def *px_exti;

    assert_param(IS_PAD_TYPE(Px));

    if      (Px == PAD_PA)        
		{
				px_exti  =(P_Port_Def*)EXTI_PA;
			  loop = 15;
		}
    else if (Px == PAD_PB)        
		{
				px_exti  = (P_Port_Def*)EXTI_PB;
				loop = 4;
		}
     else
    {        
        px_exti  = (P_Port_Def*)EXTI_PC;
        loop = 16;
		}
    for(pinpos = 0x00; pinpos < loop; pinpos++)
    {
        pos = ((uint32_t)0x01) << pinpos;

        currentpin = (EXTI_InitStruct->EXTI_Line) & pos;
        if(currentpin == pos)
        {   
            px_exti->Port[pinpos] |= EXTI_Px_INTEN_ENABLE;

            if(EXTI_InitStruct->EXTI_Trigger == EXTI_Trigger_Rising)
                px_exti->Port[pinpos] |=  EXTI_Px_INTPOR_RISING_EDGE;
            else
                px_exti->Port[pinpos] |= EXTI_Px_INTPOR_FALLING_EDGE;
        }
    }

}

void EXTI_Polarity_Set(PAD_Type Px, uint16_t GPIO_Pin, uint16_t Polarity )
{
    uint32_t pinpos = 0x00, pos = 0x00, currentpin = 0x00, loop = 16;
    P_Port_Def *px_exti;

    assert_param(IS_PAD_TYPE(Px));

   
    if      (Px == PAD_PA)        
		{
				px_exti  =(P_Port_Def*)EXTI_PA;
			  loop = 15;
		}
    else if (Px == PAD_PB)        
		{
				px_exti  = (P_Port_Def*)EXTI_PB;
				loop = 4;
		}
     else
    {        
        px_exti  = (P_Port_Def*)EXTI_PC;
        loop = 16;
		}

    for(pinpos = 0x00; pinpos < loop; pinpos++)
    {
        pos = ((uint32_t)0x01) << pinpos;

        currentpin = GPIO_Pin & pos;
        if(currentpin == pos)
        {   
            if(Polarity == EXTI_Trigger_Rising)
                px_exti->Port[pinpos] |= EXTI_Px_INTPOR_RISING_EDGE;
            else
                px_exti->Port[pinpos] |= EXTI_Px_INTPOR_FALLING_EDGE;
        }
    }

}

/**
  * @brief  Fills each EXTI_InitStruct member with its reset value.
  * @param  EXTI_InitStruct: pointer to a EXTI_InitTypeDef structure which will
  *         be initialized.
  * @retval None
  */
void EXTI_StructInit(EXTI_InitTypeDef* EXTI_InitStruct)
{
  EXTI_InitStruct->EXTI_Line = 0xFF;
  EXTI_InitStruct->EXTI_Mode = EXTI_Mode_Interrupt;
  EXTI_InitStruct->EXTI_Trigger = EXTI_Trigger_Falling;
}

uint16_t EXTI_Px_GetEXTEN(PAD_Type Px)
{
    uint32_t i, loop = 16;
	  uint16_t ret=0;
    P_Port_Def *px_exti;

    assert_param(IS_PAD_TYPE(Px));

    
    if      (Px == PAD_PA)        
		{
				px_exti  =(P_Port_Def*)EXTI_PA;
			  loop = 15;
		}
    else if (Px == PAD_PB)        
		{
				px_exti  = (P_Port_Def*)EXTI_PB;
				loop = 4;
		}
     else
    {        
        px_exti  = (P_Port_Def*)EXTI_PC;
        loop = 16;
		}

    for(i = 0x00; i < loop; i++)
    {
             ret |= (((px_exti->Port[i]&0x2)>>1)<<i);
		}
		return ret;
}

uint16_t EXTI_Px_GetEXTINTPOL(PAD_Type Px)
{
    uint32_t i, loop = 16;
	uint16_t ret=0;
    P_Port_Def *px_exti;

    assert_param(IS_PAD_TYPE(Px));

    
    if      (Px == PAD_PA)        
		{
				px_exti  =(P_Port_Def*)EXTI_PA;
			  loop = 15;
		}
    else if (Px == PAD_PB)        
		{
				px_exti  = (P_Port_Def*)EXTI_PB;
				loop = 4;
		}
     else
    {        
        px_exti  = (P_Port_Def*)EXTI_PC;
        loop = 16;
		}

    for(i = 0x00; i < loop; i++)
    {
             ret |= ((px_exti->Port[i]&0x1)<<i);
		}
		return ret;
}
