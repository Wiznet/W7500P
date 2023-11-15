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
#SSP SDcard_LED example
******************************************************************************
(C) COPYRIGHT 2015 WIZnet Co.,Ltd.

  * file    : SSP/SD_Card_LED/readme.md
  * author  : IOP Team
  * version : V1.0.0
  * date    : 1-May-2015
  * brief   : Description of the SSP SD_Card_LED example.

******************************************************************************

THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME. AS A RESULT, WIZNET SHALL NOT BE HELD LIABLE FOR ANY DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.

******************************************************************************

### Example Description

This example provides a description of how to set a communication to SDCard.

SDCard is configured SSP1 as master are with 8bit data size.

After enabling both SSP1, the first single data block to transfer Buffer Block Tx except the last ones.
block size is 512 and receive Buffer Block Rx read to SDCard except the last ones.

Once the transfer is completed a comparison is done and TransferStatus1 gives the data transfer status for each data transfer direction where it is PASSED if transmitted and received data are the same otherwise it is FAILED.
After check of TransferStatus1, if Status is PASSED LED ON BLUE and if Status is FAILED LED ON RED.

After single data block test, the second multi block data to transfer Buffer MultiBlock Tx except the last ones.
block size is 512 * 32 and receive Buffer MultiBlock Rx read to SDCard except the last ones.

Once the transfer is completed a comparison is done and TransferStatus2 gives the data transfer status for each data transfer direction where it is PASSED if transmitted and received data are the same otherwise it is FAILED.
After check of TransferStatus2, if Status is PASSED LED ON GREEN and if Status is FAILED LED ON RED.

______________________________________________________________________________

### Directory contents

  - SSP/Loopback/main.c                                   (Main program)
  - SSP/Loopback/W7500x_it.c                              (Interrupt Handlers)
  - SSP/Loopback/W7500x_it.h                              (Interrupt Handlers Header file)
  - SSP/Loopback/W7500x_conf.h                            (Library Configuration file)
  - SSP/Loopback/MDK/W7500x_SSP_SD_Card_LED.uvproj        (MDK Project file)
  - SSP/Loopback/GCC/Makefile                             (GCC Make file)
______________________________________________________________________________

### Hardware and Software environment

  - This example has been tested with WIZnet WIZwiki W7500 platform.
  - To select the WIZnet WIZwiki platform used to run the example.

  - WIZwiki W7500 Set-up
    - input micro SD card
    - Set SSP1 is master and datasize is 8bits
    - Use LED(R) connected to PC_08 pin.
    - Use LED(G) connected to PC_09 pin.
    - Use LED(B) connected to PC_05 pin.
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
