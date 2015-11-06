/**
  ******************************************************************************
  * @file    GPIO/Blink_LED/main.c 
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

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/
GPIO_InitTypeDef GPIO_InitDef;

/* Private function prototypes -----------------------------------------------*/
void delay_ms(__IO uint32_t nCount);

/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Main Function
  */
int main()
{
    /* Set Systme init */
    SystemInit();
    
    /* GPIO LED(R) Set */
    GPIO_InitDef.GPIO_Pin = GPIO_Pin_0; // Set to Pin_0 (LED(R))
    GPIO_InitDef.GPIO_Mode = GPIO_Mode_OUT; // Set to Mode Output
    GPIO_Init(GPIOC, &GPIO_InitDef);
    PAD_AFConfig(PAD_PC,GPIO_Pin_0, PAD_AF1); // PAD Config - LED used 2nd Function
	
    /* GPIO LED(G) Set */
    GPIO_InitDef.GPIO_Pin = GPIO_Pin_4; // Set to Pin_4 (LED(G))
    GPIO_InitDef.GPIO_Mode = GPIO_Mode_OUT; // Set to Mode Output
    GPIO_Init(GPIOC, &GPIO_InitDef);
    PAD_AFConfig(PAD_PC,GPIO_Pin_4, PAD_AF1);	// PAD Config - LED used 2nd Function
	  
    /* GPIO LED(B) Set */
    GPIO_InitDef.GPIO_Pin = GPIO_Pin_5; // Set to Pin_5 (LED(B))
    GPIO_InitDef.GPIO_Mode = GPIO_Mode_OUT; // Set to Mode Output
    GPIO_Init(GPIOC, &GPIO_InitDef);
    PAD_AFConfig(PAD_PC,GPIO_Pin_5, PAD_AF1); // PAD Config - LED used 2nd Function
		
    GPIO_SetBits(GPIOC, GPIO_Pin_0); // LED(R) Off
    GPIO_SetBits(GPIOC, GPIO_Pin_4); // LED(G) Off
    GPIO_SetBits(GPIOC, GPIO_Pin_5); // LED(B) Off
	
    while(1)
    {
        // LED(RGB) On/off
        delay_ms(500);
  	    GPIO_ResetBits(GPIOC, GPIO_Pin_0);			
	    GPIO_ResetBits(GPIOC, GPIO_Pin_4);
	    GPIO_ResetBits(GPIOC, GPIO_Pin_5);		  
	    delay_ms(500);
        GPIO_SetBits(GPIOC, GPIO_Pin_0);
        GPIO_SetBits(GPIOC, GPIO_Pin_4);
        GPIO_SetBits(GPIOC, GPIO_Pin_5);

        // LED(RG) On/off			
	    delay_ms(500);
  	    GPIO_ResetBits(GPIOC, GPIO_Pin_0);				
	    GPIO_ResetBits(GPIOC, GPIO_Pin_4);
	    delay_ms(500);
		GPIO_SetBits(GPIOC, GPIO_Pin_0);
        GPIO_SetBits(GPIOC, GPIO_Pin_4);

	    // LED(GB) On/off
		delay_ms(500);
  	    GPIO_ResetBits(GPIOC, GPIO_Pin_4);				
		GPIO_ResetBits(GPIOC, GPIO_Pin_5);			
		delay_ms(500);
  	    GPIO_SetBits(GPIOC, GPIO_Pin_4);				
		GPIO_SetBits(GPIOC, GPIO_Pin_5);
				
        // LED(BR) On/off
		delay_ms(500);
        GPIO_ResetBits(GPIOC, GPIO_Pin_0);				
        GPIO_ResetBits(GPIOC, GPIO_Pin_5);			
        delay_ms(500);
        GPIO_SetBits(GPIOC, GPIO_Pin_0);				
        GPIO_SetBits(GPIOC, GPIO_Pin_5);

        // LED(R) On/off
        delay_ms(500);
        GPIO_ResetBits(GPIOC, GPIO_Pin_0);
        delay_ms(500);
        GPIO_SetBits(GPIOC, GPIO_Pin_0);

        // LED(G) On/off
        delay_ms(500);
        GPIO_ResetBits(GPIOC, GPIO_Pin_4);
        delay_ms(500);
        GPIO_SetBits(GPIOC, GPIO_Pin_4);
        
        // LED(B) On/off
        delay_ms(500);
        GPIO_ResetBits(GPIOC, GPIO_Pin_5);
        delay_ms(500);
        GPIO_SetBits(GPIOC, GPIO_Pin_5);			
    }
}

/**
  * @brief  Delay Function
  */
void delay_ms(__IO uint32_t nCount)
{
    volatile uint32_t delay = nCount * 2500; // approximate loops per ms at 24 MHz, Debug config
    for(; delay != 0; delay--)
        __NOP();
}
