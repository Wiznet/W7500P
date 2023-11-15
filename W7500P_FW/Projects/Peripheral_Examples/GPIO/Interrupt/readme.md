/*******************************************************************************************************************************************************
 * Copyright �� 2016 <WIZnet Co.,Ltd.> 
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the ��Software��), 
 * to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, 
 * and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

 * THE SOFTWARE IS PROVIDED ��AS IS��, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. 
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, 
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*********************************************************************************************************************************************************/
#GPIO Interrupt example
******************************************************************************
(C) COPYRIGHT 2015 WIZnet Co.,Ltd.

  * file    : GPIO/Interrupt/readme.md
  * author  : IOP Team
  * version : V1.0.5
  * date    : 5-June-2015
  * brief   : Description of the GPIO Interrupt example.

******************************************************************************

THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME. AS A RESULT, WIZNET SHALL NOT BE HELD LIABLE FOR ANY DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.

******************************************************************************

### Example Description

This example shows how to configure GPIO Interrupt lines.
In this example, GPIO Interrupt is configured to generate an interrupt on each rising or falling edge. In the interrupt routine a LED connected to a specific GPIO pin is toggled.

In this example:
  - GPIO Interrupt line is mapped to PA.00

After GPIO Interrupt configuration, a software interrupt is generated on the GPIO Interrupt toggles LED(R).
After that, when rising edge is detected on GPIO Interrupt, LED(R) toggles.
If WIZwiki W7500 is used, when button is pressed, LED(R) toggles but, Button has to be configured separately.

______________________________________________________________________________

### Directory contents

  - GPIO/Interrupt/main.c                                (Main program)
  - GPIO/Interrupt/W7500x_it.c                           (Interrupt Handlers)
  - GPIO/Interrupt/W7500x_it.h                           (Interrupt Handlers Header file)
  - GPIO/Interrupt/W7500x_conf.h                         (Library Configuration file)
  - GPIO/Interrupt/MDK/W7500x_GPIO_Interrupt.uvproj     (MDK Project file)
  - GPIO/Interrupt/GCC/Makefile                          (GCC Make file)
______________________________________________________________________________

### Hardware and Software environment

  - This example has been tested with WIZnet WIZwiki W7500 platform.
  - To select the WIZnet WIZwiki platform used to run the example.

  - WIZwiki W7500 Set-up
    - Use LED(R) connected to PC_08 pin.
    - Use GPIO Interrupt connected to PA_00 pin.
    - In order to use the LED to be changed from PAD_AF0 to PAD_AF1.
    - Button has to be configured separately.
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