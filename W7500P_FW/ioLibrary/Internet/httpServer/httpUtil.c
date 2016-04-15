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
 * @file	httpUtil.c
 * @brief	HTTP Server Utilities	
 * @version 1.0
 * @date	2014/07/15
 * @par Revision
 *			2014/07/15 - 1.0 Release
 * @author	
 * \n\n @par Copyright (C) 1998 - 2014 WIZnet. All rights reserved.
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "W7500x_gpio.h"
#include "httpServer.h"
#include "httpParser.h"
#include "httpUtil.h"
#include "wizchip_conf.h"

uint8_t http_get_cgi_handler(uint8_t * uri_name, uint8_t * buf, uint32_t * file_len)
{
	uint8_t ret = HTTP_OK;
	uint16_t len = 0;
	
	if(predefined_get_cgi_processor(uri_name, buf, &len))
	{
		;
	}
	else if(strcmp((const char *)uri_name, "example.cgi") == 0)
	{
		// To do
		;
	}
	else
	{
		// CGI file not found
		ret = HTTP_FAILED;
	}

	if(ret)	*file_len = len;
	return ret;
}

uint8_t http_post_cgi_handler(uint8_t * uri_name, st_http_request * p_http_request, uint8_t * buf, uint32_t * file_len)
{
	uint8_t ret = HTTP_OK;
	uint16_t len = 0;
	uint8_t val = 0;
	
	if(predefined_set_cgi_processor(uri_name, p_http_request->URI, buf, &len))
	{
		;
	}
	else if(strcmp((const char *)uri_name, "example.cgi") == 0)
	{
		// To do
		val = 1;
		len = sprintf((char *)buf, "%d", val);
	}
	else
	{
		// CGI file not found
		ret = HTTP_FAILED;
	}

	if(ret)	*file_len = len;
	return ret;
}


uint8_t predefined_get_cgi_processor(uint8_t * uri_name, uint8_t * buf, uint16_t * len)
{
	uint8_t ret = 1;	// ret = 1 means 'uri_name' matched
	uint8_t cgibuf[14] = {0, };
	int8_t cgi_dio = -1;
	int8_t cgi_ain = -1;

	uint8_t i;

	if(strcmp((const char *)uri_name, "todo.cgi") == 0)
	{
		// to do
		;//make_json_todo(buf, len);
	}
	else if(strcmp((const char *)uri_name, "get_netinfo.cgi") == 0)
	{
		make_json_netinfo(buf, len);
	}
	else
	{
		;
	}

	return ret;
}


uint8_t predefined_set_cgi_processor(uint8_t * uri_name, uint8_t * uri, uint8_t * buf, uint16_t * len)
{
	uint8_t ret = 1;	// ret = '1' means 'uri_name' matched
	uint8_t val = 0;

	if(strcmp((const char *)uri_name, "todo.cgi") == 0)
	{
		// to do
		;//val = todo(uri);
		//*len = sprintf((char *)buf, "%d", val);
	}
	// Digital I/O; dio_s, dio_d
	else if(strcmp((const char *)uri_name, "set_LED.cgi") == 0)
	{
		val = set_LED(uri);
		*len = sprintf((char *)buf, "%d", val);
	}	
	else
	{
		ret = 0;
	}

	return ret;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Pre-defined Get CGI functions
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/* Example of make_jason function */
//void make_json_dio(uint8_t * buf, uint16_t * len, uint8_t pin)
//{
//	uint8_t pin_state 	= Chip_GPIO_GetPinState(LPC_GPIO, dio_ports[pin], dio_pins[pin]);
//	uint8_t pin_dir 	= Chip_GPIO_GetPinDIR(LPC_GPIO, dio_ports[pin], dio_pins[pin]);

//	*len = sprintf((char *)buf, "DioCallback({\"dio_p\":\"%d\",\
//											\"dio_s\":\"%d\",\
//											\"dio_d\":\"%d\"\
//											});",
//											pin,					// Digital io pin number
//											pin_state,				// Digital io status
//											pin_dir					// Digital io directions
//											);
//}

void make_json_netinfo(uint8_t * buf, uint16_t * len)
{
	wiz_NetInfo netinfo;
	ctlnetwork(CN_GET_NETINFO, (void*) &netinfo);

	// DHCP: 1 - Static, 2 - DHCP
	*len = sprintf((char *)buf, "NetinfoCallback({\"mac\":\"%.2X:%.2X:%.2X:%.2X:%.2X:%.2X\",\
											\"ip\":\"%d.%d.%d.%d\",\
											\"gw\":\"%d.%d.%d.%d\",\
											\"sn\":\"%d.%d.%d.%d\",\
											\"dns\":\"%d.%d.%d.%d\",\
											\"dhcp\":\"%d\"\
											});",
											netinfo.mac[0], netinfo.mac[1], netinfo.mac[2], netinfo.mac[3], netinfo.mac[4], netinfo.mac[5],
											netinfo.ip[0], netinfo.ip[1], netinfo.ip[2], netinfo.ip[3],
											netinfo.gw[0], netinfo.gw[1], netinfo.gw[2], netinfo.gw[3],
											netinfo.sn[0], netinfo.sn[1], netinfo.sn[2], netinfo.sn[3],
											netinfo.dns[0], netinfo.dns[1], netinfo.dns[2], netinfo.dns[3],
											netinfo.dhcp
											);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Pre-defined Set CGI functions
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int8_t set_LED(uint8_t * uri)
{
	uint8_t * param;
	uint8_t pin = 0, val = 0;

		
	if((param = get_http_param_value((char *)uri, "pin"))) // GPIO; D0 ~ D15
	{
		pin = (uint8_t)ATOI(param, 10);
		
		if(pin > 15) return -1;

		if((param = get_http_param_value((char *)uri, "val")))  // State; high(off)/low(on)
		{
			val = (uint8_t)ATOI(param, 10);
			
		}

		if(pin == RED)
		{
		    if(val == 0) 		GPIO_ResetBits(GPIOC, GPIO_Pin_0);	// Low(On)
		    else				GPIO_SetBits(GPIOC, GPIO_Pin_0);// High(off)
		}
		else if(pin == GREEN)
		{
		    if(val == 0) 		GPIO_ResetBits(GPIOC, GPIO_Pin_4);	// Low(On)
		    else				GPIO_SetBits(GPIOC, GPIO_Pin_4);// High(off)
		}
		else if(pin == BLUE)
		{
		    if(val == 0) 		GPIO_ResetBits(GPIOC, GPIO_Pin_5);	// Low(On)
		    else				GPIO_SetBits(GPIOC, GPIO_Pin_5);// High(off)
		}
	}

	return pin;
}

