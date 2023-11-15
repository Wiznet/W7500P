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
	*					- Initialization and Configuration
	*					- GPIO Read and Write
	*					- GPIO Interrupts and flags management
	*					- GPIO Alternate functions configuration
	*
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
  *  @verbatim
  *  
  *          ===================================================================
  *                                 How to use this driver
  *          ===================================================================
  *
  *          1. Select the GPIO(A..D), GPIO_Pin(case GPIOA..C : 0..15, case GPIOD : 0..4) 
  *             and mode(GPIO_Mode_OUT, GPIO_Mode_IN) using GPIO_Init()
  *                 
  *          2. Configure Alternative function(PAD_AF0..3) using PAD_AFConfig() 
  *             Check the datasheet 39 page(version106, 12.3 Functional description )
  *                   
  *          3. Read or Write the data
  *   
  *  @endverbatim        
  *
  ******************************************************************************
  */

/*includes -------------------------------------------*/
#include "W7500x_gpio.h"




/** @addtogroup W7500x_Periph_Driver
  * @{
  */
	

/** @defgroup GPIO
  * @brief GPIO driver modules
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/** @defgroup GPIO_Private_Functions
  * @{
  */ 



/** @defgroup GPIO_Group1 Initialization and Configuration
 *  @brief   Initialization and Configuration
 *
@verbatim   
 ===============================================================================
                        Initialization and Configuration
 ===============================================================================  

@endverbatim
  * @{
  */


/**
  * @brief  Deinitializes the GPIOx peripheral registers to their default reset values.
  * @note   By default, The GPIO pins are configured in input floating mode (except JTAG pins).
  * @param  GPIOx: where x can be (A..D) to select the GPIO peripheral.
  * @retval None
  */
void GPIO_DeInit(GPIO_TypeDef* GPIOx)
{
    uint32_t i, loop =16;
    P_Port_Def *px_pcr;
    P_Port_Def *px_afsr;

    /* Check the parameters */
    assert_param(IS_GPIO_ALL_PERIPH(GPIOx));

    /* DeInit GPIOx Registers */
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
		/* Select the specified port register to deinit */
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
	/* DeInit Pad Control Register */
        px_pcr->Port[i] = 0x60;
		/* DeInit Alternate Function Select Register */
        px_afsr->Port[i] = PAD_AF0;

    }
}


/**
  * @brief  Initializes the GPIOx peripheral according to the specified parameters in the GPIO_InitStruct.
  * @param  GPIOx: where x can be (A..D) to select the GPIO peripheral.
  * @param  GPIO_InitStruct: pointer to a GPIO_InitTypeDef structure that contains
  *         the configuration information for the specified GPIO peripheral.
  * @retval None
  */
void GPIO_Init(GPIO_TypeDef* GPIOx, GPIO_InitTypeDef* GPIO_InitStruct)
{
    uint32_t pinpos = 0x00, pos = 0x00, currentpin = 0x00, loop = 16;
    P_Port_Def *px_pcr;

		/* Check the parameters */
    assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
    assert_param(IS_GPIO_PIN(GPIO_InitStruct->GPIO_Pin));
	//A170223 becky
    assert_param(IS_GPIO_PIN(GPIO_InitStruct->GPIO_Mode));
	////////////////////////////////////////////////////////////
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
                GPIOx->OUTENSET |= pos;   /* Output Enable Set Register */ 
            }
            else        // GPIO_Mode_In
            {
                GPIOx->OUTENCLR = pos; 	/* Output Enable Clear Register  */ 
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


/**
  * @brief  Fills each GPIO_InitStruct member with its default value.
  * @param  GPIO_InitStruct : pointer to a GPIO_InitTypeDef structure which will be initialized.
  * @retval None
  */
void GPIO_StructInit(GPIO_InitTypeDef* GPIO_InitStruct)
{
    GPIO_InitStruct->GPIO_Pin  = GPIO_Pin_All;
    GPIO_InitStruct->GPIO_Mode = GPIO_Mode_IN;
    GPIO_InitStruct->GPIO_Pad = (GPIOPad_TypeDef)(GPIO_SUMMIT|GPIO_IE|GPIO_PuPd_UP);
}


/**
  * @}
  */




/** @defgroup GPIO_Group2  GPIO Read and Write
 *  @brief    GPIO Read and Write
 *
@verbatim   
 ===============================================================================
                        GPIO Read and Write
 ===============================================================================  

@endverbatim
  * @{
  */




/**
  * @brief  Reads the specified input port pin.
  * @param  GPIOx: where x can be (A..D) to select the GPIO peripheral.
  * @param  GPIO_Pin: specifies the port bit to read.
  *         This parameter can be one of  GPIO_Pin_x where x can be (0..15), except for GPIOD that can be one of (0..5). 
  * @retval The input port pin value.
  */
uint8_t GPIO_ReadInputDataBit(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
{
    uint8_t bitstatus = 0x00;

		/* Check the parameters */
    assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
    assert_param(IS_GET_GPIO_PIN(GPIO_Pin));

	
		/* Check the pin's value*/
    if((GPIOx->DATA & GPIO_Pin) != (uint32_t)Bit_RESET)
    {
        bitstatus = (uint8_t)Bit_SET;
    }
    else
    {
        bitstatus = (uint8_t)Bit_RESET;
    }

		/* Return the input port pin value */
    return bitstatus;
}


/**
  * @brief  Reads the specified GPIO input data port.
  * @param  GPIOx: where x can be (A..D) to select the GPIO peripheral.
  * @retval GPIO input data port value.
  */
uint16_t GPIO_ReadInputData(GPIO_TypeDef* GPIOx)
{
		/* Check the parameters */
    assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
	
	/*Return the input port value */
    return ((uint16_t)GPIOx->DATA);
}


/** 
  * @brief  Reads the specified output data port bit.
  * @param  GPIOx: where x can be (A..D) to select the GPIO peripheral.
  * @param  GPIO_Pin: specifies the port bit to read.
	*          This parameter can be one of  GPIO_Pin_x where x can be (0..15), except for GPIOD that can be one of (0..5). 
  * @retval The output port pin value.
  */


uint8_t GPIO_ReadOutputDataBit(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
{
    uint8_t bitstatus = 0x00;
		
		/* Check the parameters */
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

/**
  * @brief  Reads the specified GPIO output data port.
  * @param  GPIOx: where x can be (A..D) to select the GPIO peripheral.
  * @retval GPIO output data port value.
  */
uint16_t GPIO_ReadOutputData(GPIO_TypeDef* GPIOx)
{
    /* Check the parameters */
    assert_param(IS_GPIO_ALLPERIPH(GPIOx));
    return ((uint16_t)GPIOx->DATAOUT);
}


/**
  * @brief  Sets the selected data port bits.
  * @note   This functions uses GPIOx_LB_MASKED and GPIOx_UB_MASKED register to allow atomic read/modify 
  *         accesses. In this way, there is no risk of an IRQ occurring between
  *         the read and the modify access.
  * @param  GPIOx: where x can be (A..D) to select the GPIO peripheral.
  * @param  GPIO_Pin: specifies the port bits to be written.
  *          This parameter can be one of  GPIO_Pin_x where x can be (0..15), except for GPIOD that can be one of (0..5). 
  * @retval None
  */
void GPIO_SetBits(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
{
    /* Check the parameters */
    assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
    assert_param(IS_GPIO_PIN(GPIO_Pin)); 

    (GPIOx->LB_MASKED[(uint8_t)(GPIO_Pin)]) = GPIO_Pin;
    (GPIOx->UB_MASKED[(uint8_t)((GPIO_Pin)>>8)]) = GPIO_Pin;
}


/**
  * @brief  Clears the selected data port bits.
  * @note   This functions uses GPIOx_LB_MASKED and GPIOx_UB_MASKED register to allow atomic read/modify 
  *         accesses. In this way, there is no risk of an IRQ occurring between
  *         the read and the modify access.
  * @param  GPIOx: where x can be (A..D) to select the GPIO peripheral.
  * @param  GPIO_Pin: specifies the port bits to be written.
  *          This parameter can be one of  GPIO_Pin_x where x can be (0..15), except for GPIOD that can be one of (0..5). 
  * @retval None
  */
void GPIO_ResetBits(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
{
    /* Check the parameters */
    assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
    assert_param(IS_GPIO_PIN(GPIO_Pin));

    (GPIOx->LB_MASKED[(uint8_t)(GPIO_Pin)]) = ~(GPIO_Pin);
    (GPIOx->UB_MASKED[(uint8_t)(GPIO_Pin>>8)]) = ~(GPIO_Pin);
}


/**
  * @brief  Sets or clears the selected data port bit.
  * @param  GPIOx: where x can be (A..D) to select the GPIO peripheral.
  * @param  GPIO_Pin: specifies the port bit to be written.
  *          This parameter can be one of  GPIO_Pin_x where x can be (0..15), except for GPIOD that can be one of (0..5). 
  * @param  BitVal: specifies the value to be written to the selected bit.
  *          This parameter can be one of the BitAction enum values:
  *            @arg Bit_RESET: to clear the port pin
  *            @arg Bit_SET: to set the port pin
  * @retval None
  */
void GPIO_WriteBit(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, BitAction BitVal)
{
    uint32_t temp_gpio_lb;
    uint32_t temp_gpio_ub;
    
    /* Check the parameters */
    assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
    assert_param(IS_GET_GPIO_PIN(GPIO_Pin));
    assert_param(IS_GPIO_BIT_ACTION(BitVal)); 
    
    temp_gpio_lb = (GPIOx->LB_MASKED[(uint8_t)(GPIO_Pin)]);
    temp_gpio_ub = (GPIOx->UB_MASKED[(uint8_t)((GPIO_Pin)>>8)]);

    if( BitVal == Bit_SET)
    {
        (GPIOx->LB_MASKED[(uint8_t)(GPIO_Pin)]) = (temp_gpio_lb | GPIO_Pin);
        (GPIOx->UB_MASKED[(uint8_t)((GPIO_Pin)>>8)]) = (temp_gpio_ub | GPIO_Pin);
    }
    else
    {
        (GPIOx->LB_MASKED[(uint8_t)(GPIO_Pin)]) = (temp_gpio_lb & ~(GPIO_Pin));
        (GPIOx->UB_MASKED[(uint8_t)((GPIO_Pin)>>8)]) = (temp_gpio_ub & ~(GPIO_Pin));
    }
}




/**
  * @brief  Writes data to the specified GPIO data port.
  * @param  GPIOx: where x can be (A..D) to select the GPIO peripheral.
  * @param  PortVal: specifies the value to be written to the port output data register.
  * @retval None
  */
void GPIO_Write(GPIO_TypeDef* GPIOx, uint16_t PortVal)
{
    /* Check the parameters */
    assert_param(IS_GPIO_ALL_PERIPH(GPIOx));

    GPIOx->DATAOUT = PortVal;
}




/**
  * @brief  Toggles the specified GPIO pins..
  * @param  GPIOx: where x can be (A..D) to select the GPIO peripheral.
  * @param  GPIO_Pin: Specifies the pins to be toggled.
  * @retval None
  */
void GPIO_ToggleBits(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
{
  /* Check the parameters */
  assert_param(IS_GPIO_ALL_PERIPH(GPIOx));

  GPIOx->DATAOUT ^= GPIO_Pin;
}


/**
  * @}
  */




/** @defgroup GPIO_Group3 GPIO Interrupts and flags management
 *  @brief   GPIO Interrupts and flags management
 *
@verbatim   
 ===============================================================================
                              GPIO Interrupts and flags management
 ===============================================================================  

@endverbatim
  * @{
  */





/**
  * @brief  Set or Clear interrupt enable for the selected data port bits.
  * @param  GPIOx: where x can be (A..D) to select the GPIO peripheral.
  * @param  GPIO_Pin: specifies the port bits to be written.
  *          This parameter can be one of  GPIO_Pin_x where x can be (0..15), except for GPIOD that can be one of (0..5). 
  * @param  SetValue: specifies the value to be set to the selected bit.
  *          This parameter can be one of the GPIOSet_TypeDef enum values:
  *            @arg RESET: to clear tinterrupt enable
  *            @arg SET: to set interrupt enable
  * @retval None
  */

void GPIO_INT_Enable_Bits(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, GPIOSet_TypeDef SetValue)
{
    /* Check the parameters */
    assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
    assert_param(IS_GET_GPIO_PIN(GPIO_Pin));
    
	
	 /* Interrupt Type Set */
    GPIOx->INTTYPESET |= GPIO_Pin;

    if(SetValue == Set)
				/* Interrupt Enable Set */
        GPIOx->INTENSET  |= GPIO_Pin;  
		
    else // SetValue == Reset 
         /* Interrupt Enable Clear */
				GPIOx->INTENCLR |= GPIO_Pin; 
}


/**
  * @brief  Set or Clear interrupt enable for the selected data port.
  * @param  GPIOx: where x can be (A..D) to select the GPIO peripheral.
  * @param  SetValue: specifies the value to be set to the selected port.
  *          This parameter can be one of the GPIOSet_TypeDef enum values:
  *            @arg RESET: to clear interrupt enable
  *            @arg SET: to set interrupt enable
  * @retval None
  */
void GPIO_INT_Enable(GPIO_TypeDef* GPIOx, GPIOSet_TypeDef SetValue)
{
    /* Check the parameters */
    assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
    
		/* Interrupt Type Set */
    GPIOx->INTTYPESET = 0xffff;

    if(SetValue == Set)
				/* Set Interrupt Enable */
        GPIOx->INTENSET = 0xffff;
    else //SetValue == Reset
				/* Clear Interrupt Enable */
        GPIOx->INTENCLR = 0xffff;
}


/**
  * @brief  Sets or Clears Intterupt Porarity for the selected data port bit.
  * @param  GPIOx: where x can be (A..D) to select the GPIO peripheral.
  * @param  GPIO_Pin: specifies the port bits to be written.
  *          This parameter can be one of  GPIO_Pin_x where x can be (0..15), except for GPIOD that can be one of (0..5). 
  * @param  Polarity: specifies the value to be set to the selected bits.
  *          This parameter can be one of the GPIOPol_TypeDef enum values:
  *            @arg Falling: Clear Intterupt Poraity (indicates for LOW level or falling edge)
  *            @arg Rising: Set Intterupt Porarity (indicates HIGH level or rising edge)
  * @retval None
  */
void GPIO_INT_Polarity_Bits(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, GPIOPol_TypeDef Polarity)
{
    /* Check the parameters */
    assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
    assert_param(IS_GET_GPIO_PIN(GPIO_Pin));

    if(Polarity == Rising)
        GPIOx->INTPOLSET  |= GPIO_Pin; /* Set Interrupt Polarity  */ 
    else //Polarity == Falling
        GPIOx->INTPOLCLR |= GPIO_Pin;    /* Clear Interrupt Polarity  */
}


/**
  * @brief  Sets or Clears Intterupt Porarity for the selected data port.
  * @param  GPIOx: where x can be (A..D) to select the GPIO peripheral.
  * @param  Polarity: pecifies the value to be set to the selected port.
  *          This parameter can be one of the GPIOPol_TypeDef enum values:
  *            @arg Falling: Clear Intterupt Poraity (indicates for LOW level or falling edge)
  *            @arg Rising: Set Intterupt Porarity (indicates HIGH level or rising edge)
  * @retval None
  */
void GPIO_INT_Polarity(GPIO_TypeDef* GPIOx, GPIOPol_TypeDef Polarity)
{
    /* Check the parameters */
    assert_param(IS_GPIO_ALL_PERIPH(GPIOx));

    if(Polarity == Rising)
        GPIOx->INTPOLSET = 0xffff;  /* Set Interrupt Polarity  */ 
    else //Polarity == Falling
        GPIOx->INTPOLCLR = 0xffff;  /* Clear Interrupt Polarity  */
}


/**
  * @brief  Clear the interrupt.
  * @param  GPIOx: where x can be (A..D) to select the GPIO peripheral.
  * @retval None
  */
void GPIO_INT_Clear(GPIO_TypeDef* GPIOx)
{
    /* Check the parameters */
    assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
		
		/* Intterupt Clear */
    GPIOx->Interrupt.INTCLEAR = 0xffff;
}



/**
  * @brief  Read Intterupt status of selected data port pin.
  * @param  GPIOx: where x can be (A..D) to select the GPIO peripheral.
  * @param  GPIO_Pin: specifies the port bit to read.
  *          This parameter can be one of  GPIO_Pin_x where x can be (0..15), except for GPIOD that can be one of (0..5). 
  * @retval The intterupt status value of selected data port pin.
  */
uint8_t GPIO_Read_INTstatus(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
{
    uint8_t status = 0x0000;
		
	
		/* Check the parameters */
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


/**
  * @}
  */


/** @defgroup GPIO_Group4 GPIO Alternate functions configuration
 *  @brief   GPIO Alternate functions configuration
 *
@verbatim   
 ===============================================================================
               GPIO Alternate functions configuration
 ===============================================================================  

@endverbatim
  * @{
  */







/**
  * @brief   Changes the mapping of the specified pin.
  * @param  PAD_Px: where x can be (A..D) to select the PAD peripheral.
  * @param  GPIO_Pin: specifies the pin for the Alternate function.
  *          This parameter can be one of GPIO_Pin_x where x can be (0..15), except for PAD_PD that can be one of (0..5).
  * @param  P_AF: selects the pin to used as Alternate function.
  *          This parameter can be one of the PAD_AF_TypeDef enum values:
  *            @arg PAD_AF0, PAD_AF1, PAD_AF2, PAD_AF3
  * @retval None
  */

void PAD_AFConfig(PAD_Type Px, uint16_t GPIO_Pin, PAD_AF_TypeDef P_AF)
{
    int i;
    uint16_t idx =0x1;
	
		/* Check the parameters */
    assert_param(IS_PAD_Type(Px));
	//A170223 becky 
		assert_param(IS_GET_GPIO_PIN(GPIO_Pin));
	
	
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
  * @param  GPIOx: where x can be (A..D) to select the GPIO peripheral.
  * @param  GPIO_Pin: specifies the port bits to be written.
  *          This parameter can be one of  GPIO_Pin_x where x can be (0..15), except for GPIOD that can be one of (0..5). 
  * @param  GPIO_Mode: specifies the GPIO Mode
  *          This parameter can be one of the GPIOMode_TypeDef enum values:
	*            @arg GPIO_Mode_IN: GPIO Input Mode     
	*            @arg GPIO_Mode_OUT: GPIO Output Mode     
	*            @arg GPIO_Mode_AF: GPIO Alternate function Mode  
  * @param  P_AF: specifies the PAD alternate function type
  *          This parameter can be one of the PAD_AF_TypeDef enum values:
  *            @arg PAD_AF0, PAD_AF1, PAD_AF2, PAD_AF3
  * @retval None
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










/**
  * @brief  Interrupt Configuration Function
  * @param  GPIOx: where x can be (A..D) to select the GPIO peripheral.
  * @param  GPIO_Pin: specifies the port bits to be written.
  *          This parameter can be one of  GPIO_Pin_x where x can be (0..15), except for GPIOD that can be one of (0..5). 
  * @param  Polarity: specifies the value to be set to the selected bits.
  *          This parameter can be one of the GPIOPol_TypeDef enum values:
  *            @arg Falling: Clear Intterupt Poraity (indicates for LOW level or falling edge)
  *            @arg Rising: Set Intterupt Porarity (indicates HIGH level or rising edge)
  * @retval None
  */
void GPIO_INT_Configuration(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, GPIOPol_TypeDef Polarity)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    PAD_Type PADx;
    GPIO_StructInit(&GPIO_InitStructure);
    
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin;  
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;  //Set input mode
    GPIO_Init(GPIOx, &GPIO_InitStructure);

		/* Check the parameters */
    assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
    assert_param(IS_GPIO_PIN(GPIO_InitStruct->GPIO_Pin));

    GPIOx->INTENSET  |= GPIO_Pin; // Interrupt Enable Set 
    GPIOx->INTTYPESET |= GPIO_Pin;  //Interrupt Type Set 
    
	
		
    GPIO_INT_Polarity_Bits(GPIOx, GPIO_Pin, Polarity);
	
    if(GPIOx == GPIOA)
    {       
        PADx = PAD_PA;
			
				/* Configure Alternative function type that is the GPIO */
        PAD_AFConfig(PADx,GPIO_Pin, PAD_AF1);
			
			/* Enable External Interrupt*/
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


/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */
