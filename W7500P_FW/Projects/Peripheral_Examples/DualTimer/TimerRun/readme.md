#Dual Timer TimerRun example
******************************************************************************
(C) COPYRIGHT 2015 WIZnet Co.,Ltd.

  * file    : DualTimer/TimerRun/readme.md
  * author  : IOP Team
  * version : V1.0.0
  * date    : 01-May-2015
  * brief   : Description of the Dual timer TimerRun example.
  
******************************************************************************

THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
TIME. AS A RESULT, WIZnet SHALL NOT BE HELD LIABLE FOR ANY
DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.

******************************************************************************

### Example Description 

This example shows how to use the Dual timer peripheral to run. Only dual timer 0-0 is working in this example.

The Dual timer 0-0 frequency is set to SystemCoreClock(Hz), and the clock is divided by 16.
SystemCoreClock is set to 20 MHz.

The dual timer is configured in wrapping mode and periodic mode. The counter size is 32-bit.
The interrupt is enabled. 

When the Counter reaches 0, the interrupt is occurred and RED LED(PC.08) is toggled every times. 

------------------------------------------------------------------------------------
### Directory contents 

  - DualTimer/TimerRun/main.c                  (Main program) 
  - DualTimer/TimerRun/W7500x_it.c             (Interrupt Handlers)
  - DualTimer/TimerRun/W7500x_it.h             (Interrupt Handlers Header file)
  - DualTimer/TimerRun/W7500x_conf.h           (Library Configuration file)
  - DualTimer/TimerRun/MDK/TimerRun.uvproj     (MDK Project file)
  - DualTimer/TimerRun/GCC/Makefile            (GCC Make file)
  
### Hardware and Software environment 

  - This example has been tested with WIZnet WIZwiki W7500 platform.
  - To select the WIZnet WIZwiki platform used to run the example.  
  - WIZwiki W7500 Set-up
    - Use RED LED connected to PC_08 pin.    
    - In order to use the RED LED(PC_08) to be changed from PAD_AF0 to PAD_AF1.    
  
### How to use it ? 

In order to make the program work, you must do the following :

 - Open your preferred toolchain.
 - Rebuild all files and load your image into target memory.
 - Run the example.
 - WIZwiki W7500 where the Flash memory density ranges 128Kbytes.
 - If you have any questions, please use the forum site.
   - "http://wizwiki.net/forum/"

 
 <h3><center>&copy; COPYRIGHT 2015 WIZnet Co.,Ltd. </center></h3>
 