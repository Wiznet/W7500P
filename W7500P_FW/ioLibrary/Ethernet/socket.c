/*******************************************************************************************************************************************************
 * Copyright ¡§I 2016 <WIZnet Co.,Ltd.> 
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the ¢®¡ÆSoftware¢®¡¾), 
 * to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, 
 * and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

 * THE SOFTWARE IS PROVIDED ¢®¡ÆAS IS¢®¡¾, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. 
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, 
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*********************************************************************************************************************************************************/
//*****************************************************************************
//
//! \file socket.c
//! \brief SOCKET APIs Implements file.
//! \details SOCKET APIs like as Berkeley Socket APIs. 
//! \version 1.0.5
//! \date 2017/04/20
//! \par  Revision history
//!       <2017/04/20> V1.0.5 // by Eric Jung
//!         Several functions have been changed to fix the abnormal operation at MACRAW mode receive.
//!         1. recvfrom(): The wiz_recv_data() function has been replaced by the wiz_recv_macraw_data() function for MACRAW mode only.
//!         2. sendto(): Changed to not check for IP invalid error and port zero error in MACRAW mode
//!       <2016/04/11> V1.0.4. Refer to M20160411 // by justinkim
//!         1. not having break statements -> break statements added
//!         2. errata correct typos
//!       <2014/05/01> V1.0.3. Refer to M20140501
//!         1. Implicit type casting -> Explicit type casting.
//!         2. replace 0x01 with PACK_REMAINED in recvfrom()
//!         3. Validation a destination ip in connect() & sendto(): 
//!            It occurs a fatal error on converting unint32 address if uint8* addr parameter is not aligned by 4byte address.
//!            Copy 4 byte addr value into temporary uint32 variable and then compares it.
//!       <2013/12/20> V1.0.2 Refer to M20131220
//!                    Remove Warning.
//!       <2013/11/04> V1.0.1 2nd Release. Refer to "20131104".
//!                    In sendto(), Add to clear timeout interrupt status (Sn_IR_TIMEOUT)
//!       <2013/10/21> 1st Release
//! \author MidnightCow
//! \copyright
//!
//! Copyright (c)  2013, WIZnet Co., LTD.
//! All rights reserved.
//! 
//! Redistribution and use in source and binary forms, with or without 
//! modification, are permitted provided that the following conditions 
//! are met: 
//! 
//!     * Redistributions of source code must retain the above copyright 
//! notice, this list of conditions and the following disclaimer. 
//!     * Redistributions in binary form must reproduce the above copyright
//! notice, this list of conditions and the following disclaimer in the
//! documentation and/or other materials provided with the distribution. 
//!     * Neither the name of the <ORGANIZATION> nor the names of its 
//! contributors may be used to endorse or promote products derived 
//! from this software without specific prior written permission. 
//! 
//! THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
//! AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE 
//! IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
//! ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE 
//! LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR 
//! CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF 
//! SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
//! INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN 
//! CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) 
//! ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF 
//! THE POSSIBILITY OF SUCH DAMAGE.
//
//*****************************************************************************
#include "socket.h"
#include "W7500x_wztoe.h"

#define SOCK_ANY_PORT_NUM  (0xC000) //M20160411

static uint16_t sock_any_port = SOCK_ANY_PORT_NUM;
static uint16_t sock_io_mode = 0;
static uint16_t sock_is_sending = 0;
static uint16_t sock_remained_size[_WIZCHIP_SOCK_NUM_] = {0,}; //M20160411
static uint8_t  sock_pack_info[_WIZCHIP_SOCK_NUM_] = {0,};

#if _WIZCHIP_ == 5200
static uint16_t sock_next_rd[_WIZCHIP_SOCK_NUM_] ={0,};
#endif

#define CHECK_SOCKNUM()   \
    do{                    \
        if(sn > _WIZCHIP_SOCK_NUM_) return SOCKERR_SOCKNUM;   \
    }while(0);             \

#define CHECK_SOCKMODE(mode)  \
    do{                     \
        if((getSn_MR(sn) & 0x0F) != mode) return SOCKERR_SOCKMODE;  \
    }while(0);              \

#define CHECK_SOCKINIT()   \
    do{                     \
        if((getSn_SR(sn) != SOCK_INIT)) return SOCKERR_SOCKINIT; \
    }while(0);              \

#define CHECK_SOCKDATA()   \
    do{                     \
        if(len == 0) return SOCKERR_DATALEN;   \
    }while(0);              \



int8_t socket(uint8_t sn, uint8_t protocol, uint16_t port, uint8_t flag)
{
    CHECK_SOCKNUM();
    switch(protocol)
    {
        case Sn_MR_TCP :
        case Sn_MR_UDP :
        case Sn_MR_MACRAW :
            break;
#if ( _WIZCHIP_ < 5200 )
        case Sn_MR_IPRAW :
        case Sn_MR_PPPoE :
            break;
#endif
        default :
            return SOCKERR_SOCKMODE;
    }
    if((flag & 0x06) != 0) return SOCKERR_SOCKFLAG;
#if _WIZCHIP_ == 5200
    if(flag & 0x10) return SOCKERR_SOCKFLAG;
#endif

    if(flag != 0)
    {
        switch(protocol)
        {
            case Sn_MR_TCP:
                if((flag & (SF_TCP_NODELAY|SF_IO_NONBLOCK))==0) return SOCKERR_SOCKFLAG;
                break;
            case Sn_MR_UDP:
                if(flag & SF_IGMP_VER2)
                {
                    if((flag & SF_MULTI_ENABLE)==0) return SOCKERR_SOCKFLAG;
                }
#if _WIZCHIP_ == 5500
                if(flag & SF_UNI_BLOCK)
                {
                    if((flag & SF_MULTI_ENABLE) == 0) return SOCKERR_SOCKFLAG;
                }
#endif
                break;
            default:
                break;
        }
    }
    close(sn);
    setSn_MR(sn, (protocol | (flag & 0xF0)));
    if(!port)
    {
        port = sock_any_port++;
        if(sock_any_port == 0xFFF0) sock_any_port = SOCK_ANY_PORT_NUM;
    }
    setSn_PORT(sn,port);	
    setSn_CR(sn,Sn_CR_OPEN);
    while(getSn_CR(sn));
    sock_io_mode |= ((flag & SF_IO_NONBLOCK) << sn);   
    sock_is_sending &= ~(1<<sn);
    sock_remained_size[sn] = 0;
    sock_pack_info[sn] = 0;
    while(getSn_SR(sn) == SOCK_CLOSED);
    return (int8_t)sn;
}	   

int8_t close(uint8_t sn)
{
    CHECK_SOCKNUM();

    setSn_CR(sn,Sn_CR_CLOSE);
    /* wait to process the command... */
    while( getSn_CR(sn) );
    /* clear all interrupt of the socket. */
    setSn_IR(sn, 0xFF);
    sock_is_sending &= ~(1<<sn);
    sock_remained_size[sn] = 0;
    sock_pack_info[sn] = 0;
    while(getSn_SR(sn) != SOCK_CLOSED);
    return SOCK_OK;
}

int8_t listen(uint8_t sn)
{
    CHECK_SOCKNUM();
    CHECK_SOCKMODE(Sn_MR_TCP);
    CHECK_SOCKINIT();
    setSn_CR(sn,Sn_CR_LISTEN);
    while(getSn_CR(sn));
    while(getSn_SR(sn) != SOCK_LISTEN)
    {
        close(sn);
        return SOCKERR_SOCKCLOSED;
    }
    return SOCK_OK;
}


int8_t connect(uint8_t sn, uint8_t * addr, uint16_t port)
{
    CHECK_SOCKNUM();
    CHECK_SOCKMODE(Sn_MR_TCP);
    CHECK_SOCKINIT();
    //M20140501 : For avoiding fatal error on memory align mismatched
    //if( *((uint32_t*)addr) == 0xFFFFFFFF || *((uint32_t*)addr) == 0) return SOCKERR_IPINVALID;
    {
        uint32_t taddr;
        taddr = ((uint32_t)addr[0] & 0x000000FF);
        taddr = (taddr << 8) + ((uint32_t)addr[1] & 0x000000FF);
        taddr = (taddr << 8) + ((uint32_t)addr[2] & 0x000000FF);
        taddr = (taddr << 8) + ((uint32_t)addr[3] & 0x000000FF);
        if( taddr == 0xFFFFFFFF || taddr == 0) return SOCKERR_IPINVALID;
    }
    //

    if(port == 0) return SOCKERR_PORTZERO;
    setSn_DIPR(sn,addr);
    setSn_DPORT(sn,port);
#if _WIZCHIP_ == 5200   // for W5200 ARP errata 
    setSUBR(0);
#endif
    setSn_CR(sn,Sn_CR_CONNECT);
    while(getSn_CR(sn));
    if(sock_io_mode & (1<<sn)) return SOCK_BUSY;
    while(getSn_SR(sn) != SOCK_ESTABLISHED)
    {   
        if (getSn_IR(sn) & Sn_IR_TIMEOUT)
        {
            setSn_IR(sn, Sn_IR_TIMEOUT);
#if _WIZCHIP_ == 5200   // for W5200 ARP errata 
            setSUBR((uint8_t*)"\x00\x00\x00\x00");
#endif
            return SOCKERR_TIMEOUT;
        }
        if(getSn_SR(sn) == SOCK_CLOSED)
        {
            return SOCKERR_SOCKCLOSED;
        }
    }
#if _WIZCHIP_ == 5200   // for W5200 ARP errata 
    setSUBR((uint8_t*)"\x00\x00\x00\x00");
#endif

    return SOCK_OK;
}

int8_t disconnect(uint8_t sn)
{
    CHECK_SOCKNUM();
    CHECK_SOCKMODE(Sn_MR_TCP);
    setSn_CR(sn,Sn_CR_DISCON);
    /* wait to process the command... */
    while(getSn_CR(sn));
    sock_is_sending &= ~(1<<sn);
    if(sock_io_mode & (1<<sn)) return SOCK_BUSY;
    while(getSn_SR(sn) != SOCK_CLOSED)
    {
        if(getSn_IR(sn) & Sn_IR_TIMEOUT)
        {
            close(sn);
            return SOCKERR_TIMEOUT;
        }
    }
    return SOCK_OK;
}

int32_t send(uint8_t sn, uint8_t * buf, uint16_t len)
{
    uint8_t tmp=0;
    uint16_t freesize=0;

    CHECK_SOCKNUM();
    CHECK_SOCKMODE(Sn_MR_TCP);
    CHECK_SOCKDATA();
    tmp = getSn_SR(sn);
    if(tmp != SOCK_ESTABLISHED && tmp != SOCK_CLOSE_WAIT) return SOCKERR_SOCKSTATUS;
    if( sock_is_sending & (1<<sn) )
    {
        tmp = getSn_IR(sn);
        if(tmp & Sn_IR_SENDOK)
        {
            setSn_IR(sn, Sn_IR_SENDOK);
#if _WZICHIP_ == 5200
            if(getSn_TX_RD(sn) != sock_next_rd[sn])
            {
                setSn_CR(sn,Sn_CR_SEND);
                while(getSn_CR(sn));
                return SOCKERR_BUSY;
            }
#endif
            sock_is_sending &= ~(1<<sn);         
        }
        else if(tmp & Sn_IR_TIMEOUT)
        {
            close(sn);
            return SOCKERR_TIMEOUT;
        }
        else return SOCK_BUSY;
    }
    freesize = getSn_TxMAX(sn);
    if (len > freesize) len = freesize; // check size not to exceed MAX size.
    while(1)
    {
        freesize = getSn_TX_FSR(sn);
        tmp = getSn_SR(sn);
        if ((tmp != SOCK_ESTABLISHED) && (tmp != SOCK_CLOSE_WAIT))
        {
            close(sn);
            return SOCKERR_SOCKSTATUS;
        }
        if( (sock_io_mode & (1<<sn)) && (len > freesize) ) return SOCK_BUSY;
        if(len <= freesize) break;
    }
    wiz_send_data(sn, buf, len);
#if _WIZCHIP_ == 5200
    sock_next_rd[sn] = getSn_TX_RD(sn) + len;
#endif
    setSn_CR(sn,Sn_CR_SEND);
    /* wait to process the command... */
    while(getSn_CR(sn));
    sock_is_sending |= (1 << sn);
    return len;
}


int32_t recv(uint8_t sn, uint8_t * buf, uint16_t len)
{
    uint8_t  tmp = 0;
    uint16_t recvsize = 0;
    CHECK_SOCKNUM();
    CHECK_SOCKMODE(Sn_MR_TCP);
    CHECK_SOCKDATA();

    recvsize = getSn_RxMAX(sn);
    if(recvsize < len) len = recvsize;
    while(1)
    {
        recvsize = getSn_RX_RSR(sn);
        tmp = getSn_SR(sn);
        if (tmp != SOCK_ESTABLISHED)
        {
            if(tmp == SOCK_CLOSE_WAIT)
            {
                if(recvsize != 0) break;
                else if(getSn_TX_FSR(sn) == getSn_TxMAX(sn))
                {
                    close(sn);
                    return SOCKERR_SOCKSTATUS;
                }
            }
            else
            {
                close(sn);
                return SOCKERR_SOCKSTATUS;
            }
        }
        if((sock_io_mode & (1<<sn)) && (recvsize == 0)) return SOCK_BUSY;
        if(recvsize != 0) break;
    };
    if(recvsize < len) len = recvsize;
    wiz_recv_data(sn, buf, len);
    setSn_CR(sn,Sn_CR_RECV);
    while(getSn_CR(sn));
    return len;
}

int32_t sendto(uint8_t sn, uint8_t * buf, uint16_t len, uint8_t * addr, uint16_t port)
{
    uint8_t tmp = 0;
    uint16_t freesize = 0;
    uint32_t taddr;
    CHECK_SOCKNUM();
    
    tmp = (getSn_MR(sn) & 0x0F);
    switch(tmp)
    {
        case Sn_MR_UDP:
        case Sn_MR_MACRAW:
            break;
        default:
            return SOCKERR_SOCKMODE;
    }
    CHECK_SOCKDATA();
    //M20140501 : For avoiding fatal error on memory align mismatched
    //if(*((uint32_t*)addr) == 0) return SOCKERR_IPINVALID;
    {
        taddr = ((uint32_t)addr[0]) & 0x000000FF;
        taddr = (taddr << 8) + ((uint32_t)addr[1] & 0x000000FF);
        taddr = (taddr << 8) + ((uint32_t)addr[2] & 0x000000FF);
        taddr = (taddr << 8) + ((uint32_t)addr[3] & 0x000000FF);
    }
    
    if((taddr == 0)&(tmp != Sn_MR_MACRAW)) return SOCKERR_IPINVALID;
    if((port  == 0)&(tmp != Sn_MR_MACRAW)) return SOCKERR_PORTZERO;
    
    tmp = getSn_SR(sn);
    if(tmp != SOCK_MACRAW && tmp != SOCK_UDP) return SOCKERR_SOCKSTATUS;
    
    setSn_DIPR(sn, addr);
    setSn_DPORT(sn, port); 
   
    freesize = getSn_TxMAX(sn);
    if (len > freesize) len = freesize; // check size not to exceed MAX size.
    while(1)
    {
        freesize = getSn_TX_FSR(sn);
        if(getSn_SR(sn) == SOCK_CLOSED) return SOCKERR_SOCKCLOSED;
        if( (sock_io_mode & (1<<sn)) && (len > freesize) ) return SOCK_BUSY;
        if(len <= freesize) break;
    };
    wiz_send_data(sn, buf, len);

#if _WIZCHIP_ == 5200   // for W5200 ARP errata 
    setSUBR(0);
#endif

    setSn_CR(sn,Sn_CR_SEND);
    /* wait to process the command... */
    while(getSn_CR(sn));

#if _WIZCHIP_ == 5200   // for W5200 ARP errata 
    setSUBR((uint8_t*)"\x00\x00\x00\x00");
#endif

    while(1)
    {
        tmp = getSn_IR(sn);
        if(tmp & Sn_IR_SENDOK)
        {
            setSn_IR(sn, Sn_IR_SENDOK);
            break;
        }
        //M:20131104
        //else if(tmp & Sn_IR_TIMEOUT) return SOCKERR_TIMEOUT;
        else if(tmp & Sn_IR_TIMEOUT)
        {
            setSn_IR(sn, Sn_IR_TIMEOUT);
            return SOCKERR_TIMEOUT;
        }
        ////////////
    }
    return len;
}



int32_t recvfrom(uint8_t sn, uint8_t * buf, uint16_t len, uint8_t * addr, uint16_t *port)
{
    uint8_t  mr;
    uint8_t  head[8];
    uint16_t pack_len=0;

    CHECK_SOCKNUM();
    //CHECK_SOCKMODE(Sn_MR_UDP);
    switch((mr=getSn_MR(sn)) & 0x0F)
    {
        case Sn_MR_UDP:
        case Sn_MR_MACRAW:
            break;
#if ( _WIZCHIP_ < 5200 )         
        case Sn_MR_IPRAW:
        case Sn_MR_PPPoE:
            break;
#endif
        default:
            return SOCKERR_SOCKMODE;
    }
    CHECK_SOCKDATA();
    if(sock_remained_size[sn] == 0)
    {
        while(1)
        {
            pack_len = getSn_RX_RSR(sn);
            if(getSn_SR(sn) == SOCK_CLOSED) return SOCKERR_SOCKCLOSED;
            if( (sock_io_mode & (1<<sn)) && (pack_len == 0) ) return SOCK_BUSY;
            if(pack_len != 0) break;
        };
    }
    sock_pack_info[sn] = PACK_COMPLETED;
    switch (mr & 0x07)
    {
        case Sn_MR_UDP :
            if(sock_remained_size[sn] == 0)
            {
                wiz_recv_data(sn, head, 8);
                setSn_CR(sn,Sn_CR_RECV);
                while(getSn_CR(sn));
                // read peer's IP address, port number & packet length
                addr[0] = head[0];
                addr[1] = head[1];
                addr[2] = head[2];
                addr[3] = head[3];
                *port = head[4];
                *port = (*port << 8) + head[5];
                sock_remained_size[sn] = head[6];
                sock_remained_size[sn] = (sock_remained_size[sn] << 8) + head[7];
                sock_pack_info[sn] = PACK_FIRST;
            }
            if(len < sock_remained_size[sn]) pack_len = len;
            else pack_len = sock_remained_size[sn];
            //
            // Need to packet length check (default 1472)
            //
            wiz_recv_data(sn, buf, pack_len); // data copy
            break;
        case Sn_MR_MACRAW :
            if(sock_remained_size[sn] == 0)
            {
                wiz_recv_data(sn, head, 2);
                setSn_CR(sn,Sn_CR_RECV);
                while(getSn_CR(sn));
                // read peer's IP address, port number & packet length
                sock_remained_size[sn] = head[0];
                sock_remained_size[sn] = (sock_remained_size[sn] <<8) + head[1];
                if(sock_remained_size[sn] > 1516)
                {
                    close(sn);
                    return SOCKFATAL_PACKLEN;
                }
                sock_pack_info[sn] = PACK_FIRST;
            }
            if(len < sock_remained_size[sn]) pack_len = len;
            else pack_len = sock_remained_size[sn];
            
            wiz_recv_macraw_data(sn, buf, pack_len); // data copy
            break;
#if ( _WIZCHIP_ < 5200 )
        case Sn_MR_IPRAW:
            if(sock_remained_size[sn] == 0)
            {
                wiz_recv_data(sn, head, 6);
                setSn_CR(sn,Sn_CR_RECV);
                while(getSn_CR(sn));
                addr[0] = head[0];
                addr[1] = head[1];
                addr[2] = head[2];
                addr[3] = head[3];
                sock_remained_size[sn] = head[4];
                sock_remaiend_size[sn] = (sock_remained_size[sn] << 8) + head[5];
                sock_pack_info[sn] = PACK_FIRST;
            }
            //
            // Need to packet length check
            //
            if(len < sock_remained_size[sn]) pack_len = len;
            else pack_len = sock_remained_size[sn];
            wiz_recv_data(sn, buf, pack_len); // data copy
            break;
#endif
        default:
            wiz_recv_ignore(sn, pack_len);
            sock_remained_size[sn] = pack_len;
            break;
    }
    setSn_CR(sn,Sn_CR_RECV);
    /* wait to process the command... */
    while(getSn_CR(sn)) ;
    sock_remained_size[sn] -= pack_len;
    //M20140501 : replace 0x01 with PACK_REMAINED
    //if(sock_remained_size[sn] != 0) sock_pack_info[sn] |= 0x01;
    if(sock_remained_size[sn] != 0) sock_pack_info[sn] |= PACK_REMAINED;
    //
    return pack_len;
}


int8_t  ctlsocket(uint8_t sn, ctlsock_type cstype, void* arg)
{
    uint8_t tmp = 0;
    CHECK_SOCKNUM();
    switch(cstype)
    {
        case CS_SET_IOMODE:
            tmp = *((uint8_t*)arg);
            if(tmp == SOCK_IO_NONBLOCK)  sock_io_mode |= (1<<sn);
            else if(tmp == SOCK_IO_BLOCK) sock_io_mode &= ~(1<<sn);
            else return SOCKERR_ARG;
            break;
        case CS_GET_IOMODE:   
            //M20140501 : implict type casting -> explict type casting
            //*((uint8_t*)arg) = (sock_io_mode >> sn) & 0x0001;
            *((uint8_t*)arg) = (uint8_t)((sock_io_mode >> sn) & 0x0001);
            //
            break;
        case CS_GET_MAXTXBUF:
            *((uint16_t*)arg) = getSn_TxMAX(sn);
            break;
        case CS_GET_MAXRXBUF:    
            *((uint16_t*)arg) = getSn_RxMAX(sn);
            break;
        case CS_CLR_INTERRUPT:
            if( (*(uint8_t*)arg) > SIK_ALL) return SOCKERR_ARG;
            setSn_IR(sn,*(uint8_t*)arg);
            break;
        case CS_GET_INTERRUPT:
            *((uint8_t*)arg) = getSn_IR(sn);
            break;
        case CS_SET_INTMASK:  
            if( (*(uint8_t*)arg) > SIK_ALL) return SOCKERR_ARG;
            setSn_IMR(sn,*(uint8_t*)arg);
            break;
        case CS_GET_INTMASK:   
            *((uint8_t*)arg) = getSn_IMR(sn);
            break; //M20160411
        default:
            return SOCKERR_ARG;
    }
    return SOCK_OK;
}

int8_t  setsockopt(uint8_t sn, sockopt_type sotype, void* arg)
{
    // M20131220 : Remove warning
    //uint8_t tmp;
    CHECK_SOCKNUM();
    switch(sotype)
    {
        case SO_TTL:
            setSn_TTL(sn,*(uint8_t*)arg);
            break;
        case SO_TOS:
            setSn_TOS(sn,*(uint8_t*)arg);
            break;
        case SO_MSS:
            setSn_MSSR(sn,*(uint16_t*)arg);
            break;
        case SO_DESTIP:
					  //setSn_DIPR(sn, (uint8_t*)arg);
            break;
        case SO_DESTPORT:
            setSn_DPORT(sn, *(uint16_t*)arg);
            break;
#if _WIZCHIP_ != 5100
        case SO_KEEPALIVESEND:
            CHECK_SOCKMODE(Sn_MR_TCP);
#if _WIZCHIP_ > 5200
            if(getSn_KPALVTR(sn) != 0) return SOCKERR_SOCKOPT;
#endif
            setSn_CR(sn,Sn_CR_SEND_KEEP);
            while(getSn_CR(sn) != 0)
            {
                // M20131220
                //if ((tmp = getSn_IR(sn)) & Sn_IR_TIMEOUT)
                if (getSn_IR(sn) & Sn_IR_TIMEOUT)
                {
                    setSn_IR(sn, Sn_IR_TIMEOUT);
                    return SOCKERR_TIMEOUT;
                }
            }
            break;
#if _WIZCHIP_ > 5200
        case SO_KEEPALIVEAUTO:
            CHECK_SOCKMODE(Sn_MR_TCP);
            setSn_KPALVTR(sn,*(uint8_t*)arg);
            break;
#endif      
#endif   
        default:
            return SOCKERR_ARG;
    }   
    return SOCK_OK;
}

int8_t  getsockopt(uint8_t sn, sockopt_type sotype, void* arg)
{
    CHECK_SOCKNUM();
    switch(sotype)
    {
        case SO_FLAG:
            *(uint8_t*)arg = getSn_MR(sn) & 0xF0;
            break;
        case SO_TTL:
            *(uint8_t*) arg = getSn_TTL(sn);
            break;
        case SO_TOS:
            *(uint8_t*) arg = getSn_TOS(sn);
            break;
        case SO_MSS:   
            *(uint8_t*) arg = getSn_MSSR(sn);
            break; //M20160411
        case SO_DESTIP:
					  getSn_DIPR(sn, (uint8_t*)arg);
            break;
        case SO_DESTPORT:  
            *(uint16_t*) arg = getSn_DPORT(sn);
            break;
#if _WIZCHIP_ > 5200   
        case SO_KEEPALIVEAUTO:
            CHECK_SOCKMODE(Sn_MR_TCP);
            *(uint16_t*) arg = getSn_KPALVTR(sn);
            break;
#endif      
        case SO_SENDBUF:
            *(uint16_t*) arg = getSn_TX_FSR(sn);
            break; //M20160411
        case SO_RECVBUF:
            *(uint16_t*) arg = getSn_RX_RSR(sn);
            break; //M20160411
        case SO_STATUS:
            *(uint8_t*) arg = getSn_SR(sn);
            break;
        case SO_REMAINSIZE:
            if(getSn_MR(sn) == Sn_MR_TCP)
                *(uint16_t*)arg = getSn_RX_RSR(sn);
            else
                *(uint16_t*)arg = sock_remained_size[sn];
            break;
        case SO_PACKINFO:
            CHECK_SOCKMODE(Sn_MR_TCP);
            *(uint8_t*)arg = sock_pack_info[sn];
            break;
        default:
            return SOCKERR_SOCKOPT;
    }
    return SOCK_OK;
}
