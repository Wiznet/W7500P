#GPIO Blink_LED example
******************************************************************************
(C) COPYRIGHT 2015 WIZnet

  * file    : GPIO/Blink_LED/readme.md
  * author  : IOP Team
  * version : V1.0.0
  * date    : 1-May-2015
  * brief   : Description of the GPIO Blink_LED example.

******************************************************************************

THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME. AS A RESULT, WIZNET SHALL NOT BE HELD LIABLE FOR ANY DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.

******************************************************************************

### Example Description

GPIO ports are connected on APB2 bus, using UB_MASKED and LB_MASKED registers 
2 cycles are required to set a pin and another cycle to reset it. So GPIO pins
can toggle at AHB clock divided by 4.

This example describes how to use UB_MASKED and LB_MASKED
(Port Bit GPIO_SetBits/GPIO_ResetBits Register)

PC_05, PC_08, PC_09(configured in output pushpull mode) toggles in a forever 
loop:
 - Set Pin_5 and Pin_8 and Pin_9 by setting corresponding bits 
   in GPIO_SetBits register.
 - Reset Pin_5 and Pin_8 and Pin_9 by setting corresponding bits 
   in GPIO_ResetBits register.

______________________________________________________________________________

### Directory contents

  - GPIO/LED_Blink/main.c                                 (Main program)
  - GPIO/LED_Blink/MDK/W7500x_GPIO_Blink_LED.uvproj       (Project file)
______________________________________________________________________________

### Hardware and Software environment 

  - This example has been tested with WIZnet WIZwiki W7500 platform.
  - To select the WIZnet WIZwiki platform used to run the example.

  - WIZwiki W7500 Set-up 
    - Use LED(R) connected to PC_08 pin
    - Use LED(G) connected to PC_09 pin
    - Use LED(B) connected to PC_05 pin
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