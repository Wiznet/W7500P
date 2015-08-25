#PWM Output example
******************************************************************************
(C) COPYRIGHT 2015 WIZnet

  * file    : PWM/PWMOutput/readme.md
  * author  : IOP Team
  * version : V1.0.0
  * date    : 01-May-2015
  * brief   : Description of generation of the PWM output signal example.

******************************************************************************

THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
TIME. AS A RESULT, WIZnet SHALL NOT BE HELD LIABLE FOR ANY
DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.

******************************************************************************

### Example Description 

This example shows how to use the PWM peripheral to generate PWM output signal.

The PWM channel 3, 4, 5 frequency is set to SystemCoreClock(Hz), the Prescaler is 2 
so the PWM channel 3, 4, 5 counter clock is 10 MHz. SystemCoreClock is set to 20 MHz.

The PWM channel 3, 4 is set as up-count and periodic mode and 5 is set as down-count and one-shot mode. So PWM channel 5 generates output signal once. The PWM channel 3, 4, 5 are all PWM output enabled.

The PWM channel 3 is configured in Timer Mode and duty cycle is 80 % and 4 is 30 %.

The PWM channel 3 is mapped to PA_06, 4 is mapped to PA_07 and 5 is mapped to PA_08.

------------------------------------------------------------------------------------
### Directory contents 

  - PWM/PWMOutput/main.c                             (Main program) 
  - PWM/PWMOutput/W7500x_it.c                        (Interrupt Handlers)
  - PWM/PWMOutput/W7500x_it.h                        (Interrupt Handlers Header file)
  - PWM/PWMOutput/W7500x_conf.h                      (Library Configuration file)
  - PWM/PWMOutput/MDK/W7500x_PWM_PWMOutput.uvproj    (MDK Project file)
  - PWM/PWMOutput/GCC/Makefile                       (GCC Make file)
  
### Hardware and Software environment 

  - This example has been tested with WIZnet WIZwiki W7500 platform.
  - To select the WIZnet WIZwiki platform used to run the example.
  
  - WIZwiki W7500 Set-up
    - PA_06 pin generates the PWM channel 4 output signal.
    - PA_07 pin generates the PWM channel 5 output signal.
    - PA_08 pin generates the PWM channel 6 output signal.    
    - In order to use the PWM channel 4(PA_06) to be changed from PAD_AF0 to PAD_AF3.
    - In order to use the PWM channel 5(PA_07) to be changed from PAD_AF0 to PAD_AF3.
    - In order to use the PWM channel 6(PA_08) to be changed from PAD_AF0 to PAD_AF3.    
  
### How to use it ? 

In order to make the program work, you must do the following :

 - Open your preferred toolchain.
 - Rebuild all files and load your image into target memory.
 - Run the example.
 - WIZwiki W7500 where the Flash memory density ranges 128Kbytes.
 - If you have any questions, please use the forum site.
   - "http://wizwiki.net/forum/"

 
 <h3><center>&copy; COPYRIGHT 2015 WIZnet Co.,Ltd. </center></h3>
 