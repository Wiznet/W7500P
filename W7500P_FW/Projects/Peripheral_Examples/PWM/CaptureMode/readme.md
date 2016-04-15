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
#PWM Timer Mode example
******************************************************************************
(C) COPYRIGHT 2015 WIZnet Co.,Ltd.

  * file    : PWM/CaptureMode/readme.md
  * author  : IOP Team
  * version : V1.0.0
  * date    : 01-May-2015
  * brief   : Description of the PWM Capture Mode example.

******************************************************************************

THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
TIME. AS A RESULT, WIZnet SHALL NOT BE HELD LIABLE FOR ANY
DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.

******************************************************************************

### Example Description 

This example shows how to use the PWM peripheral to run capture mode.

The PWM channel 0 frequency is set to SystemCoreClock(Hz), the Prescaler is 2 
so the PWM0 counter clock is 10 MHz. SystemCoreClock is set to 20 MHz.

The PWM channel 0 is configured in Timer Mode and duty cycle is 50 %.
Timer/Counter is up-count mode and periodic mode. Capture mode is rising edge detection. 1 interrupts out of 3 interrupts
are enabled: capture interupt(match and overflow interrupt is excepted).

The Timer/Counter runs periodically and if capture signal(PC_00) is received, the Timer/Counter value is saved at capture register and capture interrupt is occurred. In capture interrupt handler, RED LED(PC_08) is toggled.

------------------------------------------------------------------------------------
### Directory contents 

  - PWM/CaptureMode/main.c                             (Main program) 
  - PWM/CaptureMode/W7500x_it.c                        (Interrupt Handlers)
  - PWM/CaptureMode/W7500x_it.h                        (Interrupt Handlers Header file)
  - PWM/CaptureMode/W7500x_conf.h                      (Library Configuration file)
  - PWM/CaptureMode/MDK/W7500x_PWM_CaptureMode.uvproj  (MDK Project file)
  - PWM/CaptureMode/GCC/Makefile                       (GCC Make file)
  
### Hardware and Software environment 

  - This example has been tested with WIZnet WIZwiki W7500 platform.
  - To select the WIZnet WIZwiki platform used to run the example.
  
  - WIZwiki W7500 Set-up
    - Use the RED LED connected to PC_08 pin.
    - Use the capture input connected to PC_00 pin.
    - In order to use the RED LED(PC_08) to be changed from PAD_AF0 to PAD_AF1.
    - In order to use the capature intput(PC_00) to be changed from PAD_AF0 to PAD_AF2.
    - External input button has to be configured separately.
  
### How to use it ? 

In order to make the program work, you must do the following :

 - Open your preferred toolchain.
 - Rebuild all files and load your image into target memory.
 - Run the example.
 - WIZwiki W7500 where the Flash memory density ranges 128Kbytes.
 - If you have any questions, please use the forum site.
   - "http://wizwiki.net/forum/"

 
 <h3><center>&copy; COPYRIGHT 2015 WIZnet Co.,Ltd. </center></h3>
 