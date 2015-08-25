#UART Interrupts example
******************************************************************************
(C) COPYRIGHT 2015 WIZnet Co.,Ltd.

  * file    : UART/Interrupt/readme.md 
  * author  : IOP Team
  * version : V1.0.0
  * date    : 1-May-2015
  * brief   : Description of the UART Interrupts example.

******************************************************************************

THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME. AS A RESULT, WIZNET SHALL NOT BE HELD LIABLE FOR ANY DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.

******************************************************************************

### Example Description

This example provides a basic communication between Uart0 and Uart1 using 
interrupts.
Uart1 sends TxBuffer2 to Uart0 which sends TxBuffer1 to Uart1. The data received 
by Uart0 and Uart1 are stored respectively in RxBuffer1 and RxBuffer2. The data
transfer is managed in Uart0_IRQHandler and Uart1_IRQHandler in W7500x_it.c file

The UART0/UART1 is configured as follow:
  - BaudRate = 115200 baud  
  - Word Length = 8 Bits
  - One Stop Bit
  - No parity
  - Hardware flow control disable
  - Receive and transmit enable
    
This example describes that the data send from UART0 to UART1.

______________________________________________________________________________
### Directory contents

  - UART/Interrupt/main.c                                            (Main program)
  - UART/Interrupt/W7500x_conf.h                                     (Library Configuration file)
  - UART/Interrupt/W7500x_it.h                                       (Interrupt handlers header file)
  - UART/Interrupt/W7500x_it.c                                       (Interrupt handlers)
  - UART/Interrupt/MDK/W7500x_Uart_Interrupt.uvproj                  (Project file)
  - UART/Interrupt/GCC/Makefile                        	             (GCC Make file)

### Hardware and Software environment 

  - This example runs on W7500 Connectivity line Devices.
  
  -  W7500 Set-up

![](http://wizwiki.net/wiki/lib/exe/fetch.php?media=products:w7500:peripherals:interrupt.png)

   - TXD(PA13) and RXD(PB_03) of UART1 connected.
   - RXD(PA14) and TXD(PB_02) of UART1 connected.
  
 
______________________________________________________________________________

### How to use it ? 
In order to make the program work, you must do the following:
 - Copy all source files from this example folder to the template folder under
   Project\Peripheral_Example
 - Open your preferred toolchain 
 - Rebuild all files and load your image into target memory
 - Run the example 

______________________________________________________________________________

<h3><center>&copy; COPYRIGHT 2015 WIZnet Co.,Ltd.</center></h3>
