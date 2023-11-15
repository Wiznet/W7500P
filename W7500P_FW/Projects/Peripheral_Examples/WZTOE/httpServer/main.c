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
 * @file    WZTOE/httpServer/main.c 
 * @author  IOP Team
 * @version V1.0.0
 * @date    01-May-2015
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
#include "W7500x_gpio.h"
#include "W7500x_uart.h"
#include "W7500x_crg.h"
#include "W7500x_wztoe.h"
#include "W7500x_miim.h"
#include "httpServer.h"
#include "loopback.h"
#include "webpage.h"

/* Private typedef -----------------------------------------------------------*/


/* Private define ------------------------------------------------------------*/
#define __DEF_USED_MDIO__ 
#define __W7500P__ // for W7500


#ifndef __W7500P__ // for W7500
	#define __DEF_USED_IC101AG__ //for W7500 Test main Board V001
#endif

#define SOCK_TCPS       0
#define SOCK_UDPS       1
#define PORT_TCPS		5000
#define PORT_UDPS       3000

#define MAX_HTTPSOCK	6


#define TICKRATE_HZ1 (1000)		/* 1 ticks per millisecond, for SysTick */
#define TICKRATE_HZ2 (1)		/* 1 ticks per second, for Timer0 */

#define _MAIN_DEBUG_

/* Private function prototypes -----------------------------------------------*/
void delay(__IO uint32_t milliseconds); //Notice: used ioLibray
void TimingDelay_Decrement(void);
void UART_Configuration(void);
void GPIO_Setting(void);

/* Private variables ---------------------------------------------------------*/
static __IO uint32_t TimingDelay;


uint8_t socknumlist[] = {2, 3, 4, 5, 6, 7};

uint8_t RX_BUF[DATA_BUF_SIZE];
uint8_t TX_BUF[DATA_BUF_SIZE];

/**
 * @brief   Main program
 * @param  None
 * @retval None
 */
int main()
{
    //uint8_t tx_size[8] = { 2, 2, 2, 2, 2, 2, 2, 2 };
    //uint8_t rx_size[8] = { 2, 2, 2, 2, 2, 2, 2, 2 };
    uint8_t mac_addr[6] = {0x00, 0x08, 0xDC, 0x71, 0x72, 0x77}; 
    uint8_t src_addr[4] = {192, 168,  1,  98};
    uint8_t gw_addr[4]  = {192, 168,  1,  1};
    uint8_t sub_addr[4] = {255, 255, 255,  0};	
		
    uint8_t tmp[8];
		
		uint8_t i;
        

    /* External Clock */
    //CRG_PLL_InputFrequencySelect(CRG_OCLK);

    /* Set Systme init */
    SystemInit();

    /* UART0 and UART1 configuration*/
    //UART_StructInit(&UART_InitStructure);
    /* Configure UART1 */
    //UART_Init(UART1,&UART_InitStructure);
		S_UART_Init(115200);

    /* SysTick_Config */
    SysTick_Config((GetSystemClock()/1000));
		
	/* LED configuration */
	GPIO_Setting();
		

    /* Set WZ_100US Register */
    setTIC100US((GetSystemClock()/10000));
    //getTIC100US();	
    //printf(" GetSystemClock: %X, getTIC100US: %X, (%X) \r\n", 
    //      GetSystemClock, getTIC100US(), *(uint32_t *)TIC100US);        


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
		

    /* Network Configuration (Default setting) */
    setSHAR(mac_addr);
    setSIPR(src_addr);
    setGAR(gw_addr);
    setSUBR(sub_addr);

    getSHAR(tmp);	printf("MAC ADDRESS : %.2X:%.2X:%.2X:%.2X:%.2X:%.2X\r\n",tmp[0],tmp[1],tmp[2],tmp[3],tmp[4],tmp[5]); 
    getSIPR(tmp); printf("IP ADDRESS : %.3d.%.3d.%.3d.%.3d\r\n",tmp[0],tmp[1],tmp[2],tmp[3]); 
    getGAR(tmp);  printf("GW ADDRESS : %.3d.%.3d.%.3d.%.3d\r\n",tmp[0],tmp[1],tmp[2],tmp[3]); 
    getSUBR(tmp); printf("SN MASK: %.3d.%.3d.%.3d.%.3d\r\n",tmp[0],tmp[1],tmp[2],tmp[3]); 

    /* Set Network Configuration */
    //wizchip_init(tx_size, rx_size);
		
		
	/* HTTP Server Initialization  */
	httpServer_init(TX_BUF, RX_BUF, MAX_HTTPSOCK, socknumlist);		// Tx/Rx buffers (1kB)
	reg_httpServer_cbfunc(NVIC_SystemReset, NULL); 					// Callback: MCU Reset

	{
		/* Web content registration (web content in webpage.h, Example web pages) */

		// Index page and netinfo / base64 image demo
		reg_httpServer_webContent((uint8_t *)"index.html", (uint8_t *)index_page);				// index.html 		: Main page example
		reg_httpServer_webContent((uint8_t *)"netinfo.html", (uint8_t *)netinfo_page);			// netinfo.html 	: Network information example page
		reg_httpServer_webContent((uint8_t *)"netinfo.js", (uint8_t *)WIZwiki_W7500_web_netinfo_js);	// netinfo.js 		: JavaScript for Read Network configuration 	(+ ajax.js)
		//reg_httpServer_webContent((uint8_t *)"img.html", (uint8_t *)img_page);					// img.html 		: Base64 Image data example page

		// Example #1
		reg_httpServer_webContent((uint8_t *)"dio.html", (uint8_t *)dio_page);					// dio.html 		: Digital I/O control example page
		reg_httpServer_webContent((uint8_t *)"dio.js", (uint8_t *)WIZwiki_W7500_web_dio_js);			// dio.js 			: JavaScript for digital I/O control 	(+ ajax.js)

		// Example #2
		//reg_httpServer_webContent((uint8_t *)"ain.html", (uint8_t *)ain_page);					// ain.html 		: Analog input monitor example page
		//reg_httpServer_webContent((uint8_t *)"ain.js", (uint8_t *)WIZwiki_W7500_web_ain_js);			// ain.js 			: JavaScript for Analog input monitor	(+ ajax.js)

		// Example #3
		//reg_httpServer_webContent((uint8_t *)"ain_gauge.html", (uint8_t *)ain_gauge_page);		// ain_gauge.html 	: Analog input monitor example page; using Google Gauge chart
		//reg_httpServer_webContent((uint8_t *)"ain_gauge.js", (uint8_t *)ain_gauge_js);			// ain_gauge.js 	: JavaScript for Google Gauge chart		(+ ajax.js)

		// AJAX JavaScript functions
		reg_httpServer_webContent((uint8_t *)"ajax.js", (uint8_t *)WIZwiki_W7500_web_ajax_js);			// ajax.js			: JavaScript for AJAX request transfer

#ifdef _MAIN_DEBUG_
		display_reg_webContent_list();
#endif
	}

	/* Main loop ***************************************/
    while(1)
    {
	   	

        // TODO: insert user's code here
        for(i = 0; i < MAX_HTTPSOCK; i++)	httpServer_run(i); 	// HTTP Server handler

        loopback_tcps(SOCK_TCPS, RX_BUF, 5000);	
    	
    } // End of Main loop

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
void UART_Configuration(void)
{
     UART_InitTypeDef UART_InitStructure;

     /* UART Configuration for UART1*/
     UART_StructInit(&UART_InitStructure);
     UART_Init(UART1,&UART_InitStructure);
}


void GPIO_Setting(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    /*GPIO Configuration for red,green,blue LED */
    PAD_AFConfig(PAD_PC,GPIO_Pin_0,PAD_AF1); ///< PAD Config - RED LED used 2nd Function
    PAD_AFConfig(PAD_PC,GPIO_Pin_5,PAD_AF1); ///< PAD Config - GREEN LED used 2nd Function	 
    PAD_AFConfig(PAD_PC,GPIO_Pin_4,PAD_AF1); ///< PAD Config - BLUE LED used 2nd Function
    
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_4 | GPIO_Pin_5; ///< Connecting GPIO_Pin_0(R),5(G),4(B)
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT; ///< Set to GPIO Mode to Output Port
    GPIO_Init(GPIOC, &GPIO_InitStructure);
	
	  GPIO_SetBits(GPIOC, GPIO_Pin_0);// Red - High(off)
	  GPIO_SetBits(GPIOC, GPIO_Pin_5);// Green - High(off)
	  GPIO_SetBits(GPIOC, GPIO_Pin_4);// Blue - High(off)
}
