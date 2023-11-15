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
#UART HardwareControl example
******************************************************************************
(C) COPYRIGHT 2015 WIZnet Co.,Ltd.

  * file    : UART/Uart_HardwareFlowControl/readme.md 
  * author  : IOP Team
  * version : V1.0.0
  * date    : 1-May-2015
  * brief   : Description of the Uart HardwareFlowControl example.

******************************************************************************

THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME. AS A RESULT, WIZNET SHALL NOT BE HELD LIABLE FOR ANY DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.

******************************************************************************

### Example Description

This example provides a description of how to use the UART with hardware flow
control and communicate with another UART.(UART0 and UART1 connect)
First, the UART2 send the debug data to the hyperterminal.
The receive buffer have a RxBufferSize bytes as maximum.

The UART0/UART1 is configured as follow:
  - BaudRate = 115200 baud  
  - Word Length = 8 Bits
  - One Stop Bit
  - No parity
  - Hardware flow control enabled (RTS and CTS signals)
  - Receive and transmit enable
  - Enable FIFOs(FEN of UART_LCR-H)

This example describes that the data send from UART0 to UART1.
The interrupts are generated when the fill level progresses through the
trigger level.

UART1 Check Point when RX status operate
  1. The bit RXFF of UARTFR(6) confirm '1'
  2. The bit BUSY of UARTFR(3) confirm '1'
  3. Send RTS as '1' (RTS of UARTCR(11))and the nUARTRTS pin is LOW.

________________________________________
### Directory contents

  - UART/Uart_HardwareFlowControl/main.c                                            (Main program)
  - UART/Uart_HardwareFlowControl/W7500x_conf.h                                     (Library Configuration file)
  - UART/Uart_HardwareFlowControl/W7500x_it.h                                       (Interrupt handlers header file)
  - UART/Uart_HardwareFlowControl/W7500x_it.c                                       (Interrupt handlers)
  - UART/Uart_HardwareFlowControl/MDK/W7500x_Uart_HardwareFlowContolTest.uvproj     (Project file)
  - UART/Uart_HardwareFlowControl/GCC/Makefile                      				(GCC Make file)


### Hardware and Software environment 

  - This example runs on W7500 Connectivity line Devices.
  
  -  W7500 Set-up

![](http://wizwiki.net/wiki/lib/exe/fetch.php?media=products:w7500:peripherals:flowcontrol.png)
  
   - CTS(PA11) and RTS(PB00) connected.
   - RTS(PA12) and CTS(PB01) connected.
   - TXD(PA13) and RXD(PB02) connected.
   - RXD(PA14) and TXD(PB03) connected.
  
 
______________________________________________________________________________

### How to use it ? 
In order to make the program work, you must do the following:
 - Copy all source files from this example folder to the template folder under
   Project\Peripheral_Example
 - Open your preferred toolchain 
 - Rebuild all files and load your image into target memory
 - Run the example 

<h3><center>&copy; COPYRIGHT 2015 WIZnet Co.,Ltd.</center></h3>
