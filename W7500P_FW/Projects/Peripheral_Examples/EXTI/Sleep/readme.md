#EXTI Sleep example
******************************************************************************
(C) COPYRIGHT 2015 WIZnet Co.,Ltd.

  * file    : EXTI/Sleep/readme.md
  * author  : IOP Team
  * version : V1.0.0
  * date    : 1-May-2015
  * brief   : Description of the EXTI Sleep example.

******************************************************************************

THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME. AS A RESULT, WIZNET SHALL NOT BE HELD LIABLE FOR ANY DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.

******************************************************************************

### Example Description

This example shows how to configure external interrupt lines.
In this example, EXTI line is configured to generate an interrupt on each rising or falling edge. In the interrupt routine connected to a specific GPIO pin.

In this example:
  - EXTI line is mapped to PA.00

After Go to Sleep Mode.
After EXTI configuration, a software interrupt is generated nothing.
After that, when rising edge is detected on EXTI, Wake-up!!

If WIZwiki W7500 is used, when button is pressed, Wake-up!!
but, Button has to be configured separately.
______________________________________________________________________________

### Directory contents

  - EXTI/Sleep/main.c                                (Main program)
  - EXTI/Sleep/W7500x_it.c                           (Interrupt Handlers)
  - EXTI/Sleep/W7500x_it.h                           (Interrupt Handlers Header file)
  - EXTI/Sleep/W7500x_conf.h                         (Library Configuration file)
  - EXTI/Sleep/MDK/W7500x_EXTI_Sleep.uvproj          (MDK Project file)
  - EXTI/Sleep/GCC/Makefile                          (GCC Make file)
______________________________________________________________________________

### Hardware and Software environment

  - This example has been tested with WIZnet WIZwiki W7500 platform.
  - To select the WIZnet WIZwiki platform used to run the example.

  - WIZwiki W7500 Set-up
    - Use LED(B) connected to PC_05 pin.
    - Use EXTI connected to PA_00 pin.
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
