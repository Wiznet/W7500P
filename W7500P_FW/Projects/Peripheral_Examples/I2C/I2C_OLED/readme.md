#I2C and I2C_OLED communication example
******************************************************************************
(C) COPYRIGHT 2015 WIZnet Co.,Ltd.

  * file    : I2C/I2C_OLED/readme.md 
  * author  : IOP Team
  * version : V1.0.0
  * date    : 1-May-2015
  * brief   :  Description of the I2C and I2C_OLED communication example.
******************************************************************************
THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME. AS A RESULT, WIZNET SHALL NOT BE HELD LIABLE FOR ANY DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
******************************************************************************

### Example Description

This example provides a description of how to use I2C to communicate with a
OLED is mounted on the evaluation board and used to get
instantaneous external temperature.

______________________________________________________________________________
### Directory contents

  - I2C/I2C_OLED/main.c                            					(Main program)
  - I2C/I2C_OLED/W7500x_it.c                       					(Interrupt Handlers)
  - I2C/I2C_OLED/W7500x_it.h                     				  	(Interrupt Handlers Header file)
  - I2C/I2C_OLED/W7500x_conf.h                     					(Library Configuration file)
  - I2C/I2C_OLED/MDK/W7500x_I2C_OLED.uvproj         				(Project file)
  - I2C/I2C_OLED/GCC/Makefile                      					(GCC Make file)
______________________________________________________________________________

### Hardware and Software environment 

    --W7500--        --OLED--
   |         |      |        |
   |     SDA |------| SDA    |
   |     SCL |------| SCL    |
   |         |      |        |
   |         |      |        |
    ---------       ---------


OLED Device Address
         --- --- --- --- --- --- --- 
        | 0 | 1 | 1 | 1 |1 | 0| 0|
         --- --- --- --- --- --- --- 
                                  LSB



______________________________________________________________________________

### How to use it ? 
In order to make the program work, you must do the following :

 - Open your preferred toolchain.
 - Rebuild all files and load your image into target memory.
 - Run the example.
 - WIZwiki W7500 where the Flash memory density ranges 128Kbytes.
 - If you have any questions, please use the forum site.
   - "http://wizwiki.net/forum/"
______________________________________________________________________________

### Flow Chart
 - Master Init
 - Slave address send from W7500 to LM75
 - START enable
 - Confirm the Ack Receive
 - Send the data from W7500 to LM75
 - Restart enable
 - Confirm the Ack Receive
 - Receive the data
 - Transmit the Ack transmission
 - STOP enable


<h3><center>&copy; COPYRIGHT 2015 WIZnet Co.,Ltd.</center></h3>