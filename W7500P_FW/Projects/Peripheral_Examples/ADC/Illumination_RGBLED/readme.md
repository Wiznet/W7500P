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
#ADC example (Illumination sensor)
******************************************************************************
(C) COPYRIGHT 2015 WIZnet Co.,Ltd.

  * file    : Illumination_RGBLED/readme.md
  * author  : IOP Team
  * version : V1.0.0
  * date    : 1-May-2015
  * brief   : Description of the Illumination sensor & RGB LED toggle example.

******************************************************************************

THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME. AS A RESULT, WIZNET SHALL NOT BE HELD LIABLE FOR ANY DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.

******************************************************************************

### Example Description

This example shows how to use ADC of W7500.
In this example, ADC input is connected with illumination sensor. And control RGB LED by illumination sensor value.

In this example:
  - 1) Set the Alternate function of PAD for this example.
  - 2) Sensing analog value of Illumination sensor.
  - 3) If dark, ON the led, if not, OFF the led with GPIO control.
______________________________________________________________________________

### Directory contents

  - ADC/Illumination_RGBLED/main.c                                (Main program)
  - ADC/Illumination_RGBLED/W7500x_it.c                           (Interrupt Handlers)
  - ADC/Illumination_RGBLED/W7500x_it.h                           (Interrupt Handlers Header file)
  - ADC/Illumination_RGBLED/W7500x_conf.h                         (Library Configuration file)
  - ADC/Illumination_RGBLED/MDK/W7500x_Illumination_regled.uvproj     (MDK Project file)
  - ADC/Illumination_RGBLED/GCC/Makefile                          (GCC Make file)
______________________________________________________________________________

### Hardware and Software environment 

  - This example has been tested with WIZnet WIZwiki W7500 platform.
  - To select the WIZnet WIZwiki platform used to run the example.

  - WIZwiki W7500 Set-up
    - Use ADC input connected to PC_15(A0) pin.
    - Use LED(R) connected to PC_08 pin.
    - Use LED(G) connected to PC_09 pin.
    - Use LED(B) connected to PC_05 pin.
    - In order to use the LEDs to be changed from PAD_AF0 to PAD_AF1.  
    
  - Hardware Connection
  
     5V - 10K ohm register - PC_15(A0) - Illumination sensor - GND
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

 - Power on ADC
 - Select ADC channel
 - ADC start
 - Wait until EOC (end of conversion)
 - Read ADC value

<h3><center>&copy; COPYRIGHT 2015 WIZnet Co.,Ltd.</center></h3>