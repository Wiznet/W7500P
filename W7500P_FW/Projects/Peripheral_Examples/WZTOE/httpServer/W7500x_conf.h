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
  * @file    WIZTOE/DNSClient/W7500x_conf.h 
  * @author  IOP Team
  * @version V1.0.0
  * @date    26-AUG-2015
  * @brief   Library configuration file.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __W7500X_CONF_H
#define __W7500X_CONF_H

/* Includes ------------------------------------------------------------------*/
/* Uncomment/Comment the line below to enable/disable peripheral header file inclusion */
#include "W7500x_gpio.h"	/* Use MDIO over GPIO */
#include "W7500x_adc.h"
#include "W7500x_crg.h"
#include "W7500x_exti.h"
#include "W7500x_dualtimer.h"
#include "W7500x_i2c.h"
#include "W7500x_pwm.h"
#include "W7500x_rng.h"
#include "W7500x_ssp.h"
#include "W7500x_uart.h"
#include "W7500x_wdt.h"
#include "W7500x_wztoe.h"	/* Use WZTOE */


/* ioLibrary */
//#include "../ioLibrary/Ethernet/socket.h"
#include "socket.h"
#include "wizchip_conf.h"

#include "httpServer.h"
#include "httpParser.h"
#include "httpUtil.h"

#include "webpage.h"
#include "loopback.h"
#include "W7500x_miim.h" /* Library for MDIO */

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Uncomment the line below to expanse the "assert_param" macro in the 
   Standard Peripheral Library drivers code */
/* #define USE_FULL_ASSERT    1 */

/* Exported macro ------------------------------------------------------------*/

#ifdef USE_FULL_ASSERT
    #define assert_param(expr)  ((expr) ? (void)0 : assert_failed((uint8_t *)__FILE__,__LINE__))
#else
    #define assert_param(expr)   ((void)0)
#endif /* USE_FULL_ASSERT */

#endif /* __W7500X_CONF_H */


/******************* (C) COPYRIGHT 2015 WIZnet Co.,Ltd. *****END OF FILE****/
