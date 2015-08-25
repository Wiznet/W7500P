#WDTReset example
******************************************************************************
(C) COPYRIGHT 2015 WIZnet Co.,Ltd.

  * file    : WDT/WDTReset/readme.md
  * author  : IOP Team
  * version : V1.0.0
  * date    : 01-May-2015
  * brief   : Description of the Watchdog timer reset example.

******************************************************************************

THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
TIME. AS A RESULT, WIZnet SHALL NOT BE HELD LIABLE FOR ANY
DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.

******************************************************************************

### Example Description 

This example shows how to use the Watchdog timer peripheral to run and generate watchdog reset request signal. External interrupt is used for generating hardfault and watchdog timer reset. EXTI line is mapped to PA_00

The Watchdog timer frequency is set to SystemCoreClock(Hz). SystemCoreClock is set to 20 MHz.
 
Reset information is checked at first, and then if reset is not occurred by watchdog timer, watchdog timer is set and started. Untill external interrupt is occurred, WDT counter is set and RED LED(PC_08) is toggled when WDT counter is under 0x1000.

If reset is occurred by watchdog timer, WDT interrupt is cleared and RED LED(PC_08) is off and GREEN LED(PC_09) is on.

------------------------------------------------------------------------------------
### Directory contents 

  - WDT/WDTReset/main.c                  (Main program) 
  - WDT/WDTReset/W7500x_it.c             (Interrupt Handlers)
  - WDT/WDTReset/W7500x_it.h             (Interrupt Handlers Header file)
  - WDT/WDTReset/W7500x_conf.h           (Library Configuration file)
  - WDT/WDTReset/MDK/WDTReset.uvproj     (MDK Project file)
  - WDT/WDTReset/GCC/Makefile            (GCC Make file)
  
### Hardware and Software environment 

  - This example has been tested with WIZnet WIZwiki W7500 platform.
  - To select the WIZnet WIZwiki platform used to run the example.  
  - WIZwiki W7500 Set-up
    - Use RED LED connected to PC_08 pin.
    - Use GREEN LED connected to PC_09 pin.
    - Use EXTI connected to PA_00 pin.
    - In order to use the RED LED(PC_08) to be changed from PAD_AF0 to PAD_AF1.
    - In order to use the GREEN LED(PC_08) to be changed from PAD_AF0 to PAD_AF1.
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
 