#Delay example (System tick timer example)
******************************************************************************
(C) COPYRIGHT 2015 WIZnet Co.,Ltd.

  * file    : SysTick/Delay/readme.md
  * author  : IOP Team
  * version : V1.0.0
  * date    : 1-May-2015
  * brief   : Description of systic timer delay example.

******************************************************************************

THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME. AS A RESULT, WIZNET SHALL NOT BE HELD LIABLE FOR ANY DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.

******************************************************************************

### Example Description

This example shows how to use SysTick of W7500.

In this example:
  - 1) Configuration SysTick
  - 2) Run delay fucntion with 1sec
______________________________________________________________________________

### Directory contents

  - SysTick/Delay/main.c                                (Main program)
  - SysTick/Delay/W7500x_it.c                           (Interrupt Handlers)
  - SysTick/Delay/W7500x_it.h                           (Interrupt Handlers Header file)
  - SysTick/Delay/W7500x_conf.h                         (Library Configuration file)
  - SysTick/Delay/MDK/W7500x_SysTick_Delay.uvproj     (MDK Project file)
  - SysTick/Delay/GCC/Makefile                          (GCC Make file)
______________________________________________________________________________

### Hardware and Software environment 

  - This example has been tested with WIZnet WIZwiki W7500 platform.
  - To select the WIZnet WIZwiki platform used to run the example.

  - WIZwiki W7500 Set-up
    - No need to hardware setup
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


<h3><center>&copy; COPYRIGHT 2015 WIZnet Co.,Ltd.</center></h3>