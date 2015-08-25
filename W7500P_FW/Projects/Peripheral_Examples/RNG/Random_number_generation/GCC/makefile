#-----------------------------------------------------------------------------
#
# W7500 example project compilation make file
#
#-----------------------------------------------------------------------------
#
#  Configurations
#
# Choose the core instantiated, can be
#  - CORTEX_M0
#  - CORTEX_M0PLUS
#CPU_PRODUCT = CORTEX_M0PLUS
CPU_PRODUCT = CORTEX_M0
TOOL_CHAIN	= gcc
CPU_TYPE	= -mcpu=cortex-m0

GNU_CC      = arm-none-eabi-gcc
GNU_OBJDUMP = arm-none-eabi-objdump
GNU_OBJCOPY = arm-none-eabi-objcopy

#GNU_CC_FLAGS = -g -O3 -mthumb $(CPU_TYPE)
GNU_CC_FLAGS = -O3 -mthumb $(CPU_TYPE) -nostdlib


TESTNAME		= W7500x_Random_number_generation

SOFTWARE_DIR = ../../../../../Libraries
CMSIS_DIR    = $(SOFTWARE_DIR)/CMSIS
CORE_INC     = $(CMSIS_DIR)/Include

DEVICE_DIR   = $(CMSIS_DIR)/Device/WIZnet/W7500
DEVICE_INC   = $(DEVICE_DIR)/Include
DEVICE_SRC   = $(DEVICE_DIR)/Source

STD_PERIPH_DIR = $(SOFTWARE_DIR)/W7500x_stdPeriph_Driver
STD_PERIPH_INC = $(STD_PERIPH_DIR)/inc
STD_PERIPH_SRC = $(STD_PERIPH_DIR)/src

LINKER_SCRIPT_PATH = $(DEVICE_SRC)/GCC
LINKER_SCRIPT = $(LINKER_SCRIPT_PATH)/gcc_W7500.ld
STARTUP_FILE	= $(LINKER_SCRIPT_PATH)/startup_W7500.S


#INCLUDE_DIR = ~/gcc-arm-none-eabi-4_8-2014q3/lib/gcc/arm-none-eabi/4.8.4/include

USER_DEFINE    = -DCORTEX_M0 -DUSE_STDPERIPH_DRIVER

# ---------------------------------------------------------------------------------------
all: all_$(TOOL_CHAIN)

# ---------------------------------------------------------------------------------------
# ---------------------------------------------------------------------------------------
# gcc : 
all_gcc:
	$(GNU_CC) $(GNU_CC_FLAGS)\
		$(STARTUP_FILE) \
		../*.c \
        $(STD_PERIPH_SRC)/W7500x_rng.c \
        $(STD_PERIPH_SRC)/W7500x_gpio.c \
        $(STD_PERIPH_SRC)/W7500x_uart.c \
		$(DEVICE_SRC)/system_W7500x.c \
		-I $(CORE_INC) -I $(DEVICE_INC) -I $(STD_PERIPH_INC) -I ../\
		-L $(LINKER_SCRIPT_PATH) \
		$(USER_DEFINE) -T $(LINKER_SCRIPT) -o $(TESTNAME).o \

    # Generate disassembly code
	$(GNU_OBJDUMP) -S $(TESTNAME).o > $(TESTNAME).lst
    # Generate binary file
	$(GNU_OBJCOPY) -S $(TESTNAME).o -O binary $(TESTNAME).bin
    # Generate hex file
	$(GNU_OBJCOPY) -S $(TESTNAME).o -O verilog $(TESTNAME).hex

# ---------------------------------------------------------------------------------------
# Clean
clean :
	@rm -rf *.o
	@if [ -e $(TESTNAME).hex ] ; then \
		rm -rf $(TESTNAME).hex ; \
	fi
	@if [ -e $(TESTNAME).lst ] ; then \
		rm -rf $(TESTNAME).lst ; \
	fi
	@if [ -e $(TESTNAME).ELF ] ; then \
		rm -rf $(TESTNAME).ELF ; \
	fi
	@if [ -e $(TESTNAME).bin ] ; then \
	rm -rf $(TESTNAME).bin ; \
	fi
	@rm -rf *.crf
	@rm -rf *.plg
	@rm -rf *.tra
	@rm -rf *.htm
	@rm -rf *.dep
	@rm -rf *.d
	@rm -rf *.lnp
	@rm -rf *.bak
	@rm -rf *.lst
	@rm -rf *.axf
	@rm -rf *.sct
	@rm -rf *.__i
	@rm -rf *._ia
SHELL=C:\Windows\System32\cmd.exe
