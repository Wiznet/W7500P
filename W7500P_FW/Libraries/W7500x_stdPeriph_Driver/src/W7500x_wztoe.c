/*
 *********************************************************************
 * @file    : wztoe.c
 * @version : 0.0.1
 * @author  : WIZnet
 * @data    
 * @brief   : wztoe dirver for W7500
 *********************************************************************
 * @attention
 */
#include "W7500x.h"
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

