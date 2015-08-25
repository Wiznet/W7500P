<markdown>
#I2C and M24CXX EEPROM communication example
******************************************************************************

(C) COPYRIGHT 2015 WIZnet Co.,Ltd.

  * file    : I2C/I2C_EEPROM_24LC02B/readme.md 
  * author  : IOP Team
  * version : V1.0.0
  * date    : 1-May-2015
  * brief   : Description of the I2C and M24CXX EEPROM communication example.

******************************************************************************

THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME. AS A RESULT, WIZNET SHALL NOT BE HELD LIABLE FOR ANY DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.

******************************************************************************

### Example Description

This example provides a basic example of how to use the I2C firmware library and
an associate I2C EEPROM driver to communicate with an I2C EEPROM device (here the
example is interfacing with M24CXX EEPROMs where XX={01, 02, 04, 08, 16, 32, 64}.

I2C peripheral is configured in Master transmitter during write operation and in
Master receiver during read operation from I2C EEPROM. 

For M24C02 to M24C15 devices, one I2C EEPROM Block address where the program
will write the buffer have to be selected from the four address available,
The EEPROM addresses where the progran start the write and the read operations
is defined in the main.c file

______________________________________________________________________________

### Directory contents

  - I2C/I2C_EEPROM_24LC02B/main.c                            		(Main program)
  - I2C/I2C_EEPROM_24LC02B/W7500x_it.c                       		(Interrupt Handlers)
  - I2C/I2C_EEPROM_24LC02B/W7500x_it.h                       		(Interrupt Handlers Header file)
  - I2C/I2C_EEPROM_24LC02B/W7500x_conf.h                     		(Library Configuration file)
  - I2C/I2C_EEPROM_24LC02B/MDK/W7500x_I2C_EEPROM_24LC02B.uvproj		(Project file)
  - I2C/I2C_EEPROM_24LC02B/GCC/Makefile                      		(GCC Make file)
______________________________________________________________________________

### Hardware and Software environment 

![](http://wizwiki.net/wiki/lib/exe/fetch.php?media=products:w7500:peripherals:i2c:eeprom_hardware_and_software.png)

EEPROM M24Cxx Pin Configuration

![](http://wizwiki.net/wiki/lib/exe/fetch.php?media=products:w7500:peripherals:i2c:eeprom_pin_configuration.png)
       
EEPROM M24Cxx Pin Description

-------------------------------------------------------------------------------
PIN | SYMBOL | DESCRIPTION
----|--------|------------------------------------------------------------------
 1  | A0     | Digital input. User-defined address bit0.
 2  | A1     | Digital input. User-defined address bit1.
 3  | A2     | Digital input. User-defined address bit2.
 4  | GND    | Ground. To be connected to the system ground.
 5  | SDA    | Digital I/O. I2C serial bi-directional data line. Open Drain
 6  | SCL    | Digital input. I2C serial clock input.
 7  | WP     | Write Protect
 8  | VCC    | Power supply.



EEPROM M24Cxx Write Protect

![](http://wizwiki.net/wiki/lib/exe/fetch.php?media=products:w7500:peripherals:i2c:eeprom_m24cxx_write_protect.png)


EEPROM M24Cxx Device Address

![](http://wizwiki.net/wiki/lib/exe/fetch.php?media=products:w7500:peripherals:i2c:eeprom_device_address.png)


______________________________________________________________________________

### How to use it ? 
In order to make the program work, you must do the following:
 - Copy all source files from this example folder to the template folder under
   Project\Peripheral_Example
 - Open your preferred toolchain 
 - Rebuild all files and load your image into target memory
 - Run the example 

______________________________________________________________________________

### Flow Chart

 - Master Init
 - Device address send from W7500 to EEPROM
 - START enable
 - Confirm the Ack Receive
 - Slave address send from W7500 to EEPROM
 - Confirm the Ack Receive
 - Send the data from W7500 to EEPROM
 - Restart enable
 - Confirm the Ack Receive
 - Receive the data
 - Transmit the Ack transmission
 - STOP enable

<h3><center>&copy; COPYRIGHT 2015 WIZnet Co.,Ltd.</center></h3>