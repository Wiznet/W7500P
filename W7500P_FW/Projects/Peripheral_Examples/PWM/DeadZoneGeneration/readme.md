#Dead-Zone generation example
******************************************************************************
(C) COPYRIGHT 2015 WIZnet

  * file    : PWM/DeadZoneGeneration/readme.md
  * author  : IOP Team
  * version : V1.0.0
  * date    : 01-May-2015
  * brief   : Description of the Dead-zone generation example.

******************************************************************************

THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
TIME. AS A RESULT, WIZnet SHALL NOT BE HELD LIABLE FOR ANY
DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.

******************************************************************************

### Example Description 

This example shows how to use the PWM peripheral to run Dead-zone generation.

The PWM channel 0 frequency is set to SystemCoreClock(Hz), the Prescaler is 2 
so the PWM channel 0 counter clock is 10 MHz. SystemCoreClock is set to 20 MHz.

The PWM channel 0 is set as up-count and periodic mode, and the dead-zone counter value is set as 100. The PWM output is enabled. So as a result, the output of PWM channel 1 is inverted the PWM channel 0 output.

 - note:
   - If you want to use the PWM channel 0 as dead-zone generation, the PWM channel 1 output MUST be disabled.
  
The PWM channel 0 output is mapped to PC_00, and inverted output is mapped to PC_01(The PWM channel 1 output). 

------------------------------------------------------------------------------------
### Directory contents 

  - PWM/DeadZoneGeneration/main.c                                   (Main program) 
  - PWM/DeadZoneGeneration/W7500x_it.c                              (Interrupt Handlers)
  - PWM/DeadZoneGeneration/W7500x_it.h                              (Interrupt Handlers Header file)
  - PWM/DeadZoneGeneration/W7500x_conf.h                            (Library Configuration file)
  - PWM/DeadZoneGeneration/MDK/W7500x_PWM_DeadZoneGeneration.uvproj (MDK Project file)
  - PWM/DeadZoneGeneration/GCC/Makefile                             (GCC Make file)
  
### Hardware and Software environment 

  - This example has been tested with WIZnet WIZwiki W7500 platform.
  - To select the WIZnet WIZwiki platform used to run the example.
  
  - WIZwiki W7500 Set-up
    - PA_00 pin generates the PWM channel 0 output signal.
    - PA_01 pin generates the inverted PWM channel 0 output signal.        
    - In order to use the PWM channel 0(PA_00) to be changed from PAD_AF0 to PAD_AF2.
    - In order to use the inverted PWM channel 0(PA_01) to be changed from PAD_AF0 to PAD_AF2.
  
### How to use it ? 

In order to make the program work, you must do the following :

 - Open your preferred toolchain.
 - Rebuild all files and load your image into target memory.
 - Run the example.
 - WIZwiki W7500 where the Flash memory density ranges 128Kbytes.
 - If you have any questions, please use the forum site.
   - "http://wizwiki.net/forum/"

 
 <h3><center>&copy; COPYRIGHT 2015 WIZnet Co.,Ltd. </center></h3>
 