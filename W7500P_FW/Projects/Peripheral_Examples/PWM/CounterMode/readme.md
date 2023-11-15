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
#PWM Counter Mode example
******************************************************************************
(C) COPYRIGHT 2015 WIZnet

  * file    : PWM/CounterMode/readme.md
  * author  : IOP Team
  * version : V1.0.0
  * date    : 01-May-2015
  * brief   : Description of the PWM Counter Mode example.

******************************************************************************

THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
TIME. AS A RESULT, WIZnet SHALL NOT BE HELD LIABLE FOR ANY
DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.

******************************************************************************

### Example Description 

This example shows how to use the PWM peripheral to run counter mode.

The PWM channel 0 frequency is set to SystemCoreClock(Hz). SystemCoreClock is set to 20 MHz.

The PWM channel 0 is configured in rising edge counter mode, up-count mode, periodic mode. So the PWM channel 0 Timer/Counter is counted when input signal is triggered. 2 interrupts out of 3 interrupts are enabled: match and overflow interupt(capture interrupt is excepted).

The PWM channel 0 output pin(PC_00) is used for input.

When the Timer/Counter reaches the match value, RED LED(PC_08) is toggled every times, 
and when the Tiemr/Counter reaches the limit value, GREEN LED(PC_09) is toggled every times.

------------------------------------------------------------------------------------
### Directory contents 

  - PWM/CounterMode/main.c                               (Main program) 
  - PWM/CounterMode/W7500x_it.c                          (Interrupt Handlers)
  - PWM/CounterMode/W7500x_it.h                          (Interrupt Handlers Header file)
  - PWM/CounterMode/W7500x_conf.h                        (Library Configuration file)
  - PWM/CounterMode/MDK/W7500x_PWM_CounterMode.uvproj    (MDK Project file)
  - PWM/CounterMode/GCC/Makefile                         (GCC Make file)
  
### Hardware and Software environment 

  - This example has been tested with WIZnet WIZwiki W7500 platform.
  - To select the WIZnet WIZwiki platform used to run the example.
  
  - WIZwiki W7500 Set-up
    - Use RED LED connected to PC_08 pin.
    - Use GREEN LED connected to PC_09 pin.
    - Use PC_00 for input signal.
    - In order to use the RED LED(PC_08) to be changed from PAD_AF0 to PAD_AF1.
    - In order to use the GREEN LED(PC_09) to be changed from PAD_AF0 to PAD_AF1.
    - In order to use the PC_00 to be changed from PAD_AF0 to PAD_AF2.
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
 
