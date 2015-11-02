/**
 * @file	httpUtil.h
 * @brief	Header File for HTTP Server Utilities
 * @version 1.0
 * @date	2014/07/15
 * @par Revision
 *			2014/07/15 - 1.0 Release
 * @author	
 * \n\n @par Copyright (C) 1998 - 2014 WIZnet. All rights reserved.
 */

#ifndef	__HTTPUTIL_H__
#define	__HTTPUTIL_H__

#include "httpParser.h"


#define RED        0
#define GREEN    4
#define BLUE      5

uint8_t http_get_cgi_handler(uint8_t * uri_name, uint8_t * buf, uint32_t * file_len);
uint8_t http_post_cgi_handler(uint8_t * uri_name, st_http_request * p_http_request, uint8_t * buf, uint32_t * file_len);

uint8_t predefined_get_cgi_processor(uint8_t * uri_name, uint8_t * buf, uint16_t * len);
uint8_t predefined_set_cgi_processor(uint8_t * uri_name, uint8_t * uri, uint8_t * buf, uint16_t * len);


// Pre-defined Get CGI functions
void make_json_netinfo(uint8_t * buf, uint16_t * len);
//void make_json_LEDR(uint8_t * buf, uint16_t * len);

// Pre-defined Set CGI functions
//int8_t set_diodir(uint8_t * uri);
//int8_t set_diostate(uint8_t * uri);
int8_t set_LED(uint8_t * uri);

#endif
