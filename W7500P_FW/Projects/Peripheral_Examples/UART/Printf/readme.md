#UART Printf example
******************************************************************************
(C) COPYRIGHT 2015 WIZnet Co.,Ltd.

  * file    : UART/Printf/readme.md 
  * author  : IOP Team
  * version : V1.0.0
  * date    : 1-May-2015
  * brief   : Description of the UART Printf example.

******************************************************************************

THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME. AS A RESULT, WIZNET SHALL NOT BE HELD LIABLE FOR ANY DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.

******************************************************************************

### Example Description

This example shows how to retarget the C library printf function to the UART. 
This implementation output the printf message on the Hyperterminal using UARTx.
UARTx can be UART0 or UART1 depending on the board you are using

The UART0/UART1 is configured as follow:
    - BaudRate = 115200 baud  
    - Word Length = 8 Bits
    - One Stop Bit
    - No parity
    - Hardware flow control disable
    - Receive and transmit enable
    
This example describes that the data send from UART0 to PC.


______________________________________________________________________________
### Directory contents

  - UART/Printf/main.c                                            (Main program)
  - UART/Printf/W7500x_conf.h                                     (Library Configuration file)
  - UART/Printf/W7500x_it.h                                       (Interrupt handlers header file)
  - UART/Printf/W7500x_it.c                                       (Interrupt handlers)
  - UART/Printf/MDK/W7500x_Uart_Print.uvproj                      (Project file)
  - UART/Printf/GCC/Makefile                      			   	  (GCC Make file)


### Hardware and Software environment 

  - This example runs on W7500 Connectivity line Devices.
  
  -  W7500 Set-up

![](http://wizwiki.net/wiki/lib/exe/fetch.php?media=products:w7500:peripherals:printf.png)
  

   - TXD(PA13) and RXD of PC connected.
   - RXD(PA14) and TXD of PC connected.
  

______________________________________________________________________________

### How to use it ? 
In order to make the program work, you must do the following:
 - Copy all source files from this example folder to the template folder under
   Project\Peripheral_Example
 - Open your preferred toolchain 
 - Rebuild all files and load your image into target memory
 - Run the example 

<h3><center>&copy; COPYRIGHT 2015 WIZnet Co.,Ltd.</center></h3>
