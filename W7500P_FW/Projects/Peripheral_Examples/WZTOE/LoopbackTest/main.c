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
  * @file    WZTOE/Loopback/main.c 
  * @author  IOP Team
  * @version V1.0.0
  * @date    25-AUG-2015
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
#include <stdio.h>
#include "W7500x_crg.h"
#include "W7500x_gpio.h"
#include "W7500x_uart.h"
#include "W7500x_wztoe.h"
#include "loopback.h"
#include "W7500x_miim.h"
/* Private typedef -----------------------------------------------------------*/
UART_InitTypeDef UART_InitStructure;

/* Private define ------------------------------------------------------------*/
#define __DEF_USED_MDIO__ 
#define __W7500P__ // for W7500P

#ifndef __W7500P__ // for W7500
	#define __DEF_USED_IC101AG__ //for W7500 Test main Board V001
#endif
/* Private function prototypes -----------------------------------------------*/
void delay(__IO uint32_t milliseconds); //Notice: used ioLibray
void TimingDelay_Decrement(void);

/* Private variables ---------------------------------------------------------*/
static __IO uint32_t TimingDelay;
uint8_t test_buf[2048];

/**
  * @brief   Main program
  * @param  None
  * @retval None
  */
int main()
{

    //uint8_t tx_size[8] = { 2, 2, 2, 2, 2, 2, 2, 2 };
    //uint8_t rx_size[8] = { 2, 2, 2, 2, 2, 2, 2, 2 };
	  //uint8_t dns_server[4] = {8, 8, 8, 8};           // for Example domain name server
    uint8_t mac_addr[6] = {0x00, 0x08, 0xDC, 0x01, 0x02, 0x03}; 
    uint8_t src_addr[4] = {192, 168,  77,  123};
    uint8_t gw_addr[4]  = {192, 168,  77,  1};
    uint8_t sub_addr[4] = {255, 255, 255,  0};		

    uint8_t tmp[8];

    /* External Clock */
    CRG_PLL_InputFrequencySelect(CRG_OCLK);

    /* Set Systme init */
    SystemInit();

    /* Configure UART2 */
	  S_UART_Init(115200);
    printf("run \r\n");  
    /* SysTick_Config */
    SysTick_Config((GetSystemClock()/1000));

    /* Set WZ_100US Register */
    setTIC100US((GetSystemClock()/10000));
    //getTIC100US();	
    //printf(" GetSystemClock: %X, getTIC100US: %X, (%X) \r\n", 
    // GetSystemClock, getTIC100US(), *(uint32_t *)TIC100US);        
    

#ifdef __DEF_USED_MDIO__ 
    /* PHY Initialization */
    PHY_Init();
    
    /* PHY Link Check via gpio mdio */
    while( link() == 0x0)
    {
        printf(".");  
        delay(500);
    }
    printf("PHY is linked. \r\n");  
#else
    delay(1000);
    delay(1000);
#endif


    /* Network Configuration */
    setSHAR(mac_addr);
    setSIPR(src_addr);
    setGAR(gw_addr);
    setSUBR(sub_addr);

    getSHAR(tmp);
    printf("MAC ADDRESS : %.2X:%.2X:%.2X:%.2X:%.2X:%.2X\r\n",tmp[0],tmp[1],tmp[2],tmp[3],tmp[4],tmp[5]); 
    getSIPR(tmp);
    printf("IP ADDRESS : %.3d.%.3d.%.3d.%.3d\r\n",tmp[0],tmp[1],tmp[2],tmp[3]); 
    getGAR(tmp);
    printf("GW ADDRESS : %.3d.%.3d.%.3d.%.3d\r\n",tmp[0],tmp[1],tmp[2],tmp[3]); 
    getSUBR(tmp);
    printf("SN MASK: %.3d.%.3d.%.3d.%.3d\r\n",tmp[0],tmp[1],tmp[2],tmp[3]); 

    /* Set Network Configuration */
    //wizchip_init(tx_size, rx_size);

    printf("TEST- START \r\n");  
    while(1)
    {
        loopback_tcps(0, test_buf, 5000);
    }
}

/**
  * @brief  Inserts a delay time.
  * @param  nTime: specifies the delay time length, in milliseconds.
  * @retval None
  */
void delay(__IO uint32_t milliseconds)
{
  TimingDelay = milliseconds;

  while(TimingDelay != 0);
}

/**
  * @brief  Decrements the TimingDelay variable.
  * @param  None
  * @retval None
  */
void TimingDelay_Decrement(void)
{
  if (TimingDelay != 0x00)
  { 
    TimingDelay--;
  }
}

