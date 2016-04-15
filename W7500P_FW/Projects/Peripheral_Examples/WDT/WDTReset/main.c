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
  * @file    WDT/WDTReset/main.c 
  * @author  IOP Team
  * @version V1.0.0
  * @date    26-AUG-2015
  * @brief   Main program body
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, WIZnet SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2015 WIZnet Co.,Ltd.</center></h2>
  ******************************************************************************
  */ 

/* Includes ------------------------------------------------------------------*/
#include "W7500x_gpio.h"
#include "W7500x_exti.h"
#include "W7500x_wdt.h"

/* Private typedef -----------------------------------------------------------*/
typedef struct
{
  __IO   uint32_t  REMAP;          /*!< Offset: 0x000 Remap Control Register (R/W) */
  __IO   uint32_t  PMUCTRL;        /*!< Offset: 0x004 PMU Control Register (R/W) */
  __IO   uint32_t  RESETOP;        /*!< Offset: 0x008 Reset Option Register  (R/W) */
  __IO   uint32_t  EMICTRL;        /*!< Offset: 0x00C EMI Control Register  (R/W) */
  __IO   uint32_t  RSTINFO;        /*!< Offset: 0x010 Reset Information Register (R/W) */
} W7500x_SYSCON_TypeDef;

/* Private define ------------------------------------------------------------*/
#define W7500x_SYSCON            ((W7500x_SYSCON_TypeDef *) W7500x_SYSCTRL_BASE)
#define W7500x_SYSCTRL_BASE      (0x4001F000)
#define SYSRESETREQ_Msk 0x1
#define WDTRESETREQ_Msk 0x2

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
WDT_InitTypeDef WDT_InitStructure;
int reset_test = 0;
int rst_info = 0;


/* Private function prototypes -----------------------------------------------*/
void GPIO_Setting(void);
void NVIC_Configuration(void);

/* Private functions ---------------------------------------------------------*/

/**
  * @brief   Main program
  * @param  None
  * @retval None
  */
int main()
{
    /*System clock configuration*/
    SystemInit();
//    *(volatile uint32_t *)(0x41001014) = 0x0060100; //clock setting 48MHz
    
    /* CLK OUT Set */
//    PAD_AFConfig(PAD_PA,GPIO_Pin_2, PAD_AF2); // PAD Config - CLKOUT used 3nd Function
    /* CPIO configuration */
    GPIO_Setting();
    
    /* NVIC Configuration */
    NVIC_Configuration();

    rst_info = W7500x_SYSCON->RSTINFO;
    // 0 : SYSRESETREQ
    // 1 : Watchdog reset
    // 2 : Processor LOCKUP reset
    
    if((rst_info & WDTRESETREQ_Msk) != 0) //Reset request is caused by WDT
    {
        WDT_IntClear();

        GPIO_SetBits(GPIOC, GPIO_Pin_0);
        GPIO_ResetBits(GPIOC, GPIO_Pin_4);
        while(1);
    }
    else if((rst_info & SYSRESETREQ_Msk) != 0) //Reset request is caused by SYSTEM
    {
        WDT_InitStructure.WDTLoad = 0xFF0000;
        WDT_InitStructure.WDTControl_RstEn = WDTControl_RstEnable;
        WDT_Init(&WDT_InitStructure);

        WDT_Start();
    }
    
    while(1)
    {

        if(WDT_GetWDTValue() < 0x1000)
        {
            WDT_SetWDTLoad(0xFF0000);
            // LED red is toggled /
            if(GPIO_ReadOutputDataBit(GPIOC,GPIO_Pin_0) != (uint32_t)Bit_RESET)
                GPIO_ResetBits(GPIOC, GPIO_Pin_0);
            else
                GPIO_SetBits(GPIOC, GPIO_Pin_0);
        }
    }
}

/**
  * @brief  Configure the GPIO Pins.
  * @param  None
  * @retval None
  */
void GPIO_Setting(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    EXTI_InitTypeDef EXTI_InitStructure;

    
     /* GPIO Configuration for red LED */
    GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_0; ///< Connecting GPIO_Pin_0(LED(R))
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT; ///< Set to GPIO Mode to Output Port
    GPIO_Init(GPIOC, &GPIO_InitStructure);
    PAD_AFConfig(PAD_PC, GPIO_Pin_0, PAD_AF1); ///< PAD Config - LED used 2nd Function
 
    /* GPIO Configuration for green LED */
    GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_4; ///< Connecting GPIO_Pin_4(LED(G))
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT; ///< Set to GPIO Mode to Output Port
    GPIO_Init(GPIOC, &GPIO_InitStructure);
    PAD_AFConfig(PAD_PC, GPIO_Pin_4, PAD_AF1); ///< PAD Config - LED used 2nd Function
    
    /* Set to GPIO_Pin_0 to Input Port */
    GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_0; 
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IN;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    /* Set to GPIO_Pin_0 to External Interrupt Port */
    EXTI_InitStructure.EXTI_Line = GPIO_Pin_0;
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising; ///< Set to Trigger to Rising
    EXTI_Init(PAD_PA, &EXTI_InitStructure);

    GPIO_SetBits(GPIOC, GPIO_Pin_0);
    GPIO_SetBits(GPIOC, GPIO_Pin_4);
}

/**
  * @brief  Configure the nested vectored interrupt controller.
  * @param  None
  * @retval None
  */
void NVIC_Configuration(void)
{
    NVIC_EnableIRQ(EXTI_IRQn);
}
