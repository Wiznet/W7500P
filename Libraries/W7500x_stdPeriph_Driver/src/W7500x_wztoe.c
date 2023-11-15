/**
  *********************************************************************
  * @file    : wztoe.c
  * @version : 0.0.1
  * @author  : WIZnet
  * @data    
  * @brief   : wztoe dirver for W7500
  *********************************************************************
  * @attention
  *
  *******************************************************************************************************************************************************
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
  ********************************************************************************************************************************************************/


/* Includes ------------------------------------------------------------------*/
#include "W7500x_wztoe.h"

/** @addtogroup W7500x_StdPeriph_Driver
  * @{
  */

/** @defgroup WZTOE 
  * @brief WZTOE driver modules
  * @{
  */ 

/** @defgroup WZTOE_Private_TypesDefinitions
  * @{
  */ 

/**
  * @}
  */

/** @defgroup WZTOE_Private_Defines
  * @{
  */

/**
  * @}
  */

/** @defgroup WZTOE_Private_Macros
  * @{
  */

/**
  * @}
  */

/** @defgroup WZTOE_Private_Variables
  * @{
  */

/**
  * @}
  */

/** @defgroup WZTOE_Private_FunctionPrototypes
  * @{
  */

/**
  * @}
  */

/** @defgroup WZTOE_Private_Functions
  * @{
  */

/**
  * @brief  This function reads the value from WZTOE register.
  * @param  Addr: select the WZTOE register address.
  * @retval value of reads from WZTOE register.
  */
uint8_t WIZCHIP_READ(uint32_t Addr)
{
    uint8_t ret;
    WIZCHIP_CRITICAL_ENTER();
    ret = (uint8_t)(*(volatile uint8_t *)(Addr));
    WIZCHIP_CRITICAL_EXIT();
    return ret;
}

void WIZCHIP_WRITE(uint32_t Addr, uint8_t Data)
{
    WIZCHIP_CRITICAL_ENTER();
    *(volatile uint8_t *)(Addr) = Data;
    WIZCHIP_CRITICAL_EXIT();
}
void WIZCHIP_READ_BUF (uint32_t BaseAddr, uint32_t ptr, uint8_t* pBuf, uint16_t len)
{
    uint16_t i = 0;
    WIZCHIP_CRITICAL_ENTER();

    for(i = 0; i < len; i++)
        pBuf[i] = *(volatile uint8_t *)(BaseAddr +((ptr+i)&0xFFFF));

    WIZCHIP_CRITICAL_EXIT();
}

void WIZCHIP_WRITE_BUF(uint32_t BaseAddr, uint32_t ptr, uint8_t* pBuf, uint16_t len)
{
    uint16_t i = 0;
    WIZCHIP_CRITICAL_ENTER();

    for( i=0; i<len; i++)
        *(volatile uint8_t *)(BaseAddr + ((ptr+i)&0xFFFF)) = pBuf[i];

    WIZCHIP_CRITICAL_EXIT();
}

void wiz_send_data(uint8_t sn, uint8_t *wizdata, uint16_t len)
{
    uint32_t ptr = 0;
    uint32_t sn_tx_base = 0;

    if(len == 0)  return;
    ptr = getSn_TX_WR(sn);
    sn_tx_base = (TXMEM_BASE) | ((sn&0x7)<<18);
    WIZCHIP_WRITE_BUF(sn_tx_base, ptr, wizdata, len);
    ptr += len;
    setSn_TX_WR(sn,ptr);
}

void wiz_recv_data(uint8_t sn, uint8_t *wizdata, uint16_t len)
{
    uint32_t ptr = 0;
    uint32_t sn_rx_base = 0; 

    if(len == 0) return;
    ptr = getSn_RX_RD(sn);
    sn_rx_base = (RXMEM_BASE) | ((sn&0x7)<<18);
    WIZCHIP_READ_BUF(sn_rx_base, ptr, wizdata, len);
    ptr += len;
    setSn_RX_RD(sn,ptr);
}

void wiz_recv_macraw_data(uint8_t sn, uint8_t *wizdata, uint16_t len)
{
    uint32_t ptr = 0;
    uint32_t sn_rx_base = 0; 

    if(len == 0) return;
    ptr = getSn_RX_RD(sn);
    sn_rx_base = (RXMEM_BASE) | ((sn&0x7)<<18);
    WIZCHIP_READ_BUF(sn_rx_base, ptr, wizdata, len);
    ptr += (len - ((len > 2) ? 2:0)); // Update Rx socket buffer ptr, excluding 2-bytes CRC length
    setSn_RX_RD(sn,ptr);
}

void wiz_recv_ignore(uint8_t sn, uint16_t len)
{
    uint32_t ptr = 0;
    uint32_t sn_rx_base = 0; 
    if(len == 0) return;
    ptr = getSn_RX_RD(sn);
    sn_rx_base = (RXMEM_BASE) | ((sn&0x7)<<18);
    ptr = sn_rx_base + ((ptr+len)&0xFFFF);
    setSn_RX_RD(sn,ptr);
}

