#SSP Loopback example
******************************************************************************
(C) COPYRIGHT 2015 WIZnet Co.,Ltd.

  * file    : SSP/Loopback/readme.md
  * author  : IOP Team
  * version : V1.0.0
  * date    : 1-May-2015
  * brief   : Description of the SSP Loopback example.

******************************************************************************

THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME. AS A RESULT, WIZNET SHALL NOT BE HELD LIABLE FOR ANY DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.

******************************************************************************

### Example Description

This example provides a description of how to set a communication between two SSPs in MO mode and performs a transfer from Master to Slave by Interrnal Loopback.

SSP0 is configured as master and SSP1 as slave both are with 16bit data size.

After enabling both SSPs, the first data from set value 0x50 followed by the first data send by the master. The same procedure is done for the remaining data to transfer except the last ones.

Last data from SSP0 transmit buffer is save to SSP1 receive buffer.

Once the transfer is completed a comparison is done and TransferStatus gives the data transfer status for each data transfer direction where it is PASSED if transmitted and received data are the same otherwise it is FAILED.
After check of TransferStatus, if Status is PASSED LED ON GREEN and if Status is FAILED LED ON RED.

______________________________________________________________________________

### Directory contents

  - SSP/Loopback/main.c                                   (Main program)
  - SSP/Loopback/W7500x_it.c                              (Interrupt Handlers)
  - SSP/Loopback/W7500x_it.h                              (Interrupt Handlers Header file)
  - SSP/Loopback/W7500x_conf.h                            (Library Configuration file)
  - SSP/Loopback/MDK/W7500x_SSP_Loopback.uvproj           (MDK Project file)
  - SSP/Loopback/GCC/Makefile                             (GCC Make file)
______________________________________________________________________________

### Hardware and Software environment

  - This example has been tested with WIZnet WIZwiki W7500 platform.
  - To select the WIZnet WIZwiki platform used to run the example.

  - WIZwiki W7500 Set-up
    - Set SSP0 is master and datasize is 16bits
    - Set SSP1 is Slave and datasize is 16bits
    - Connect SSP0 SSEL (PA.05) pin to SSP1 SSEL (PB.00) Pin
    - Connect SSP0 SCLK (PA.06) pin to SSP1 SCLK (PB.01) Pin
    - Connect SSP0 MISO (PA.07) pin to SSP1 MISO (PB.02) Pin
    - Connect SSP0 MOSI (PA.08) pin to SSP1 MOSI (PB.03) Pin
    - Use LED(R) connected to PC_08 pin.
    - Use LED(G) connected to PC_09 pin.
    - In order to use the LED to be changed from PAD_AF0 to PAD_AF1.
______________________________________________________________________________

### How to use it ?

In order to make the program work, you must do the following :

 - Open your preferred toolchain.
 - Rebuild all files and load your image into target memory.
 - Run the example.
 - WIZwiki W7500 where the Flash memory density ranges 128Kbytes.
 - If you have any questions, please use the forum site.
   - "http://wizwiki.net/forum/"

<h3><center>&copy; COPYRIGHT 2015 WIZnet Co.,Ltd.</center></h3>
