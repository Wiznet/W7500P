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
#include <stdio.h>
#include "W7500x_gpio.h"
#include "W7500x_uart.h"
#include "W7500x_crg.h"
#include "W7500x_wztoe.h"
#include "W7500x_miim.h"
#include "../../../../ioLibrary/Ethernet/wizchip_conf.h"
#include "../../../../ioLibrary/Internet/DHCP/dhcp.h"
#include "../../../../ioLibrary/Internet/DNS/dns.h"


/* Private typedef -----------------------------------------------------------*/
UART_InitTypeDef UART_InitStructure;
GPIO_InitTypeDef GPIO_InitDef;
/* Private define ------------------------------------------------------------*/
#define __DEF_USED_MDIO__ 
#define __W7500P__

#ifndef __W7500P__ // for W7500
	#define __DEF_USED_IC101AG__ //for W7500 Test main Board V001
#endif
#define _MAIN_DEBUG_
#define _HTTPCLI_DEBUG_
//#define _DNS_DEBUG_

#define TICKRATE_HZ1 (1000)		/* 1000 ticks per second, for SysTick */
#define TICKRATE_HZ2 (1)		/* 1 ticks per second, for Timer0 */
volatile uint32_t msTicks; 		/* counts 1ms timeTicks */

///////////////////////////
// Demo Firmware Version //
///////////////////////////
#define VER_H		1
#define VER_L		00

#define	MAX_DNS_RETRY     2        ///< DNS query retry Count
#define	DNS_WAIT_TIME     3        ///< Wait response time. unit 1s.
#define MY_MAX_DHCP_RETRY   3

#define SOCK_TCPS	0
#define SOCK_DNS	1
#define SOCK_DHCP	2

#define PORT_HTTPS      80
#define SOCK_HTTPC       0
#define false   0
#define true    1

uint16_t PORT_HTTPC = 3000;

/////////////////////
// PHYStatus check //
/////////////////////
#define SEC_PHYSTATUS_CHECK 		1		// sec
uint8_t PHYStatus_check_enable = false;
uint8_t PHYStatus_check_flag = true;

/////////////////////
// RGB LED Control //
/////////////////////

////////////////
// DHCP client//
////////////////
#define MY_MAX_DHCP_RETR 2
uint8_t my_dhcp_retry = 0;
//
////////////////
// DNS client //
////////////////
//uint8_t Domain_name[] = "www.google.com";    // for example domain name
    
uint8_t dns_server[4]    = {8, 8, 8, 8};            	// Secondary DNS server IP
uint8_t Domain_IP[4]  = {0, };               		// Translated IP address by DNS Server
uint8_t Domain_name[] = "www.accuweather.com";    		// for Example domain name
uint8_t URI[] = "/en/kr/sourth-korea-weather";


/* Private function prototypes -----------------------------------------------*/
void delay(__IO uint32_t milliseconds); //Notice: used ioLibray
void TimingDelay_Decrement(void);
//static void PHYStatus_Check(void);
void Board_LED_Toggle(void);
void Board_LED_Set(uint16_t gpio_pin);
/*****************************************************************************
 * Private Application functions
 ****************************************************************************/
uint8_t run_user_applications = false;
int32_t httpclient(uint8_t sn, uint8_t* buf, uint16_t port);
int32_t dns_do(uint8_t sn, uint8_t* buf);
void dhcp_do(void);

/*****************************************************************************
 * Public functions
 ****************************************************************************/
void SysTick_Handler(void);
void Timer32_0_Init(uint32_t tickrate);
void TIMER32_0_IRQHandler(void);


// Callback function : User defined DHCP functions

/* Private variables ---------------------------------------------------------*/
static __IO uint32_t TimingDelay;
uint8_t test_buf[1024];

/**
  * @brief   Main program
  * @param  None
  * @retval None
  */
#define DATA_BUF_SIZE   2048
uint8_t gDATABUF[DATA_BUF_SIZE];



/**
 * @brief    Main routine for WIZwiki-W7500
 * @return   Function should not exit.
 */
int main(void) {

    uint8_t mac_addr[6] = {0x00, 0x08, 0xDC, 0x71, 0x72, 0x77}; 
    uint8_t src_addr[4] = {192, 168,  77,  9};
    uint8_t gw_addr[4]  = {192, 168,  77,  1};
    uint8_t sub_addr[4] = {255, 255, 255,  0};	
    
    uint8_t tmp[8];
    uint32_t toggle = 1;
    /* Set Systme init */
    SystemInit();

    /* UART0 and UART1 configuration*/
    //UART_StructInit(&UART_InitStructure);
    /* Configure UART1 */
    //UART_Init(UART1,&UART_InitStructure);
		S_UART_Init(115200);

    /* SysTick_Config */
    SysTick_Config((GetSystemClock()/1000));

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
    printf("======W%d NET CONF : DHCP======\r\n",_WIZCHIP_);
    getSHAR(tmp);	printf("MAC ADDRESS : %.2X:%.2X:%.2X:%.2X:%.2X:%.2X\r\n",tmp[0],tmp[1],tmp[2],tmp[3],tmp[4],tmp[5]); 
    getSIPR(tmp); printf("IP ADDRESS : %.3d.%.3d.%.3d.%.3d\r\n",tmp[0],tmp[1],tmp[2],tmp[3]); 
    getGAR(tmp);  printf("GW ADDRESS : %.3d.%.3d.%.3d.%.3d\r\n",tmp[0],tmp[1],tmp[2],tmp[3]); 
    getSUBR(tmp); printf("SN MASK: %.3d.%.3d.%.3d.%.3d\r\n",tmp[0],tmp[1],tmp[2],tmp[3]); 

    /* Set Network Configuration */
    //wizchip_init(tx_size, rx_size);
			
    /* DHCP client Initialization */
    DHCP_init(SOCK_DHCP, test_buf);
    /* DHCP IP allocation and check the DHCP lease time (for IP renewal) */
    while(1)
    {
        switch(DHCP_run())
        {
            case DHCP_IP_ASSIGN:
            case DHCP_IP_CHANGED:
                /* If this block empty, act with default_ip_assign & default_ip_update  */
                //
                // This example calls the registered 'my_ip_assign' in the two case.
                //
                // Add to ...
                //
                //
                break;
            case DHCP_IP_LEASED:
                //
                if(toggle)
                {
									  getSIPR(tmp); printf("> DHCP IP : %d.%d.%d.%d\r\n", tmp[0], tmp[1], tmp[2], tmp[3]);
                    getGAR(tmp);  printf("> DHCP GW : %d.%d.%d.%d\r\n", tmp[0], tmp[1], tmp[2], tmp[3]);
                    getSUBR(tmp); printf("> DHCP SN : %d.%d.%d.%d\r\n", tmp[0], tmp[1], tmp[2], tmp[3]);
                     toggle = 0;
                    printf("===========================\r\n");
                    printf("DHCP LEASED TIME : %d Sec\r\n", getDHCPLeasetime());
                }  
                

                // TO DO YOUR NETWORK APPs.
                while(1)
                {
                    httpclient(SOCK_HTTPC, gDATABUF, PORT_HTTPC);
                }								
                break;
                
            case DHCP_FAILED:
                /* ===== Example pseudo code =====  */
                // The below code can be replaced your code or omitted.
                // if omitted, retry to process DHCP
                my_dhcp_retry++;
                if(my_dhcp_retry > MY_MAX_DHCP_RETRY)
                {
#if DEBUG_MODE != DEBUG_NO
                    printf(">> DHCP %d Failed\r\n",my_dhcp_retry);
#endif
                    my_dhcp_retry = 0;
                    DHCP_stop();      // if restart, recall DHCP_init()
                }
                break;
            default:
                break;
        }	


    }
}





/* Public functions **********************************************************/




/*******************************************
 * @ brief Call back for Simple HTTP Client 
 *******************************************/
int32_t httpclient(uint8_t sn, uint8_t* buf, uint16_t port)
{
   int32_t ret;
   uint16_t size = 0,  i=0;
#ifdef _HTTPCLI_DEBUG_
   uint8_t destip[4];
   uint16_t destport;
   uint16_t http_cmd_sz = 800;
   uint8_t http_cmd[800];
#endif

   switch(getSn_SR(sn))
   {
      case SOCK_ESTABLISHED :
         if(getSn_IR(sn) & Sn_IR_CON)
         {
#ifdef _HTTPCLI_DEBUG_
        	 getSn_DIPR(sn, destip);
        	 destport = getSn_DPORT(sn);

        	 printf("%d:Connected - %d.%d.%d.%d : %d\r\n",sn, destip[0], destip[1], destip[2], destip[3], destport);
#endif
            setSn_IR(sn,Sn_IR_CON);

            snprintf(http_cmd, http_cmd_sz,  "GET %s HTTP/1.1\r\nHost: %s\r\nConnection: close\r\n\r\n", URI, Domain_name);
            ret = send(sn, http_cmd, http_cmd_sz-1);
               if(ret < 0)
               {
                  close(sn);
                  return ret;
               }
    
         }
         if((size = getSn_RX_RSR(sn)) > 0)
         {
            if(size > DATA_BUF_SIZE) size = DATA_BUF_SIZE;
            ret = recv(sn, buf, size);
            for(i=0; i<ret; i++)
            {
                printf("%c",buf[i]);           
            }
            printf("\r\n");
            if(ret <= 0) return ret;
         }
         break;
      case SOCK_CLOSE_WAIT :
#ifdef _HTTPCLI_DEBUG_
         //printf("%d:CloseWait\r\n",sn);
#endif
         if((size = getSn_RX_RSR(sn)) > 0)
         {
             if(size > DATA_BUF_SIZE) size = DATA_BUF_SIZE;
             ret = recv(sn, buf, size);
             if(ret <= 0) return ret;
         }
         if((ret=disconnect(sn)) != SOCK_OK) return ret;
#ifdef _HTTPCLI_DEBUG_
         printf("%d:Socket closed\r\n",sn);
#endif
         break;
      case SOCK_INIT :
         /* do dns */
         ret = dns_do(SOCK_DNS, buf);

         /* do tcp connection */
         if(ret)
         {
             ret = connect(sn, Domain_IP, PORT_HTTPS);
#ifdef _HTTPCLI_DEBUG_
             if(ret)
             {
                 printf("%d:, Connect... HTTP Server\r\n",sn);
             }
#endif
         }
         break;
      case SOCK_CLOSED:
#ifdef _HTTPCLI_DEBUG_
         //printf("%d:TCP server loopback start\r\n",sn);
#endif
         if((ret=socket(sn, Sn_MR_TCP, port, 0x00)) != sn)
         //if((ret=socket(sn, Sn_MR_TCP, port, Sn_MR_ND)) != sn) // no delay ack
            return ret;
#ifdef _HTTPCLI_DEBUG_
         //printf("%d:Socket opened\r\n",sn);
#endif
         break;
      default:
         break;
   }
   return 1;
}

/*******************************************
 * @ brief Call back for DNS Client
 *******************************************/
int32_t dns_do(uint8_t sn, uint8_t* buf)
{
    int32_t ret;
#ifdef _DNS_DEBUG_
    printf("\r\n===== DNS Servers =====\r\n");
    printf("> DNS  : %d.%d.%d.%d\r\n", dns_server[0], dns_server[1], dns_server[2], dns_server[3]);
    printf("=======================================\r\n");
    printf("> [Example] Target Domain Name : %s\r\n", Domain_name);
#endif

    /* DNS client Initialization */
    DNS_init(sn, buf);
    if (((ret = DNS_run(dns_server, Domain_name, Domain_IP))>0))     // retry to 2nd DNS
    {

     	printf("> Translated %s to %d.%d.%d.%d\r\n",Domain_name,Domain_IP[0],Domain_IP[1],Domain_IP[2],Domain_IP[3]);

    }
    else
    {
#ifdef _DNS_DEBUG_
        printf("> DNS Failed\r\n");
#endif
        if(ret == -1)
        {
#ifdef _DNS_DEBUG_
            printf("> MAX_DOMAIN_NAME3 is too small. Should be redefined it.\r\n");
#endif
            ;
        }
        ;
    }
	delay(1000);
#ifdef _DNS_DEBUG_
    if(ret>0)
    {
        printf("> Domain_IP : %d.%d.%d.%d\r\n", Domain_IP[0], Domain_IP[1], Domain_IP[2], Domain_IP[3]);
    }        
#endif
    return ret;
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

void Board_LED_Toggle(void)
{
     /* GPIO LED(R) Set */
    GPIO_InitDef.GPIO_Pin = GPIO_Pin_8; // Set to Pin_5 (LED(R))
    GPIO_InitDef.GPIO_Mode = GPIO_Mode_OUT; // Set to Mode Output
    GPIO_Init(GPIOC, &GPIO_InitDef);
    PAD_AFConfig(PAD_PC,GPIO_Pin_8, PAD_AF1); // PAD Config - LED used 2nd Function
    
    delay(500);
  	GPIO_ResetBits(GPIOC, GPIO_Pin_8);	
    delay(500);
    GPIO_SetBits(GPIOC, GPIO_Pin_8);
    delay(500);
    GPIO_ResetBits(GPIOC, GPIO_Pin_8);	
}

void Board_LED_Set(uint16_t GPIO_Pin)
{
    GPIO_InitDef.GPIO_Pin = GPIO_Pin; // Set to Pin_5 (LED(R))
    GPIO_InitDef.GPIO_Mode = GPIO_Mode_OUT; // Set to Mode Output
    GPIO_Init(GPIOC, &GPIO_InitDef);
    PAD_AFConfig(PAD_PC,GPIO_Pin, PAD_AF1); // PAD Config - LED used 2nd Function
    
    delay(500);
  	GPIO_ResetBits(GPIOC, GPIO_Pin);	
    delay(500);
    GPIO_SetBits(GPIOC, GPIO_Pin);
    delay(500);
    GPIO_ResetBits(GPIOC, GPIO_Pin);	
}
