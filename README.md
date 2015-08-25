#Library and Peripheral Example

##Overview
The W7500p provides the CMSIS, driver and Peripheral Example.
The W7500p Standard Peripherals library provides a rich set of examples covering the main features of each peripheral. 
All the examples are independent from the WIZwiki-W7500 platform. 
Only source files are provided for each example and user can tailor the provided project template to run the selected example with his preferred toolchain. 

  - Directory Structure
  
![Fig.directory_structure](http://wizwiki.net/wiki/lib/exe/fetch.php?media=products:w7500p:iolib_directory.png)

  - ioLibrary
    - Application
      - loopback
    - Ethernet
    - Internet
      - DHCP
      - DNS
      - httpServer
    - MDIO
  - Libraies
    - CMSIS :CMSIS Library
    - W7500x_stdPeriph_Driver
	  - Each peripheral has a source code file W7500x_XXX.c and a header file W7500x_XXX.h. 
           The W7500x_XXX.c file contains all the firmware functions required to use the XXX peripheral.
      - A single memory mapping file, W7500x.h, is supplied for all peripherals. 
           It contains all the register declarations and bit definition. 
           This is the only file that needs to be included in the user application to interface with the library.
  - Projects
    - peripheral_Examples
      - The W7500 standard Peripherals library provides a rich set of examples covering the main features of each peripheral. 
  - Utilities
    - w7500p_flash_algo_mdk
      - The W7500 standard library provides W7500 128KB flash algorithm project to debug WIZwiki-W7500 with using ULINK debugger and CMSIS-DAP debugger. 

##Peripheral description and examples
- [Peripherals](http://wizwiki.net/wiki/doku.php?id=products:w7500p:peripherals)
