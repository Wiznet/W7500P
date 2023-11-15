# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.27

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = "C:/Program Files/CMake/bin/cmake.exe"

# The command to remove a file.
RM = "C:/Program Files/CMake/bin/cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = D:/W7500P

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = D:/W7500P/build

# Include any dependencies generated for this target.
include Projects/Peripheral_Examples/PWM/DeadZoneGeneration/CMakeFiles/DeadZoneGeneration.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include Projects/Peripheral_Examples/PWM/DeadZoneGeneration/CMakeFiles/DeadZoneGeneration.dir/compiler_depend.make

# Include the progress variables for this target.
include Projects/Peripheral_Examples/PWM/DeadZoneGeneration/CMakeFiles/DeadZoneGeneration.dir/progress.make

# Include the compile flags for this target's objects.
include Projects/Peripheral_Examples/PWM/DeadZoneGeneration/CMakeFiles/DeadZoneGeneration.dir/flags.make

Projects/Peripheral_Examples/PWM/DeadZoneGeneration/CMakeFiles/DeadZoneGeneration.dir/main.c.obj: Projects/Peripheral_Examples/PWM/DeadZoneGeneration/CMakeFiles/DeadZoneGeneration.dir/flags.make
Projects/Peripheral_Examples/PWM/DeadZoneGeneration/CMakeFiles/DeadZoneGeneration.dir/main.c.obj: D:/W7500P/Projects/Peripheral_Examples/PWM/DeadZoneGeneration/main.c
Projects/Peripheral_Examples/PWM/DeadZoneGeneration/CMakeFiles/DeadZoneGeneration.dir/main.c.obj: Projects/Peripheral_Examples/PWM/DeadZoneGeneration/CMakeFiles/DeadZoneGeneration.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=D:/W7500P/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object Projects/Peripheral_Examples/PWM/DeadZoneGeneration/CMakeFiles/DeadZoneGeneration.dir/main.c.obj"
	cd D:/W7500P/build/Projects/Peripheral_Examples/PWM/DeadZoneGeneration && "C:/Program Files (x86)/GNU Arm Embedded Toolchain/10 2021.10/bin/arm-none-eabi-gcc.exe" $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT Projects/Peripheral_Examples/PWM/DeadZoneGeneration/CMakeFiles/DeadZoneGeneration.dir/main.c.obj -MF CMakeFiles/DeadZoneGeneration.dir/main.c.obj.d -o CMakeFiles/DeadZoneGeneration.dir/main.c.obj -c D:/W7500P/Projects/Peripheral_Examples/PWM/DeadZoneGeneration/main.c

Projects/Peripheral_Examples/PWM/DeadZoneGeneration/CMakeFiles/DeadZoneGeneration.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/DeadZoneGeneration.dir/main.c.i"
	cd D:/W7500P/build/Projects/Peripheral_Examples/PWM/DeadZoneGeneration && "C:/Program Files (x86)/GNU Arm Embedded Toolchain/10 2021.10/bin/arm-none-eabi-gcc.exe" $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E D:/W7500P/Projects/Peripheral_Examples/PWM/DeadZoneGeneration/main.c > CMakeFiles/DeadZoneGeneration.dir/main.c.i

Projects/Peripheral_Examples/PWM/DeadZoneGeneration/CMakeFiles/DeadZoneGeneration.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/DeadZoneGeneration.dir/main.c.s"
	cd D:/W7500P/build/Projects/Peripheral_Examples/PWM/DeadZoneGeneration && "C:/Program Files (x86)/GNU Arm Embedded Toolchain/10 2021.10/bin/arm-none-eabi-gcc.exe" $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S D:/W7500P/Projects/Peripheral_Examples/PWM/DeadZoneGeneration/main.c -o CMakeFiles/DeadZoneGeneration.dir/main.c.s

Projects/Peripheral_Examples/PWM/DeadZoneGeneration/CMakeFiles/DeadZoneGeneration.dir/__/__/__/__/Libraries/Startup/startup_W7500.s.obj: Projects/Peripheral_Examples/PWM/DeadZoneGeneration/CMakeFiles/DeadZoneGeneration.dir/flags.make
Projects/Peripheral_Examples/PWM/DeadZoneGeneration/CMakeFiles/DeadZoneGeneration.dir/__/__/__/__/Libraries/Startup/startup_W7500.s.obj: D:/W7500P/Libraries/Startup/startup_W7500.s
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=D:/W7500P/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building ASM object Projects/Peripheral_Examples/PWM/DeadZoneGeneration/CMakeFiles/DeadZoneGeneration.dir/__/__/__/__/Libraries/Startup/startup_W7500.s.obj"
	cd D:/W7500P/build/Projects/Peripheral_Examples/PWM/DeadZoneGeneration && "C:/Program Files (x86)/GNU Arm Embedded Toolchain/10 2021.10/bin/arm-none-eabi-gcc.exe" $(ASM_DEFINES) $(ASM_INCLUDES) $(ASM_FLAGS) -o CMakeFiles/DeadZoneGeneration.dir/__/__/__/__/Libraries/Startup/startup_W7500.s.obj -c D:/W7500P/Libraries/Startup/startup_W7500.s

Projects/Peripheral_Examples/PWM/DeadZoneGeneration/CMakeFiles/DeadZoneGeneration.dir/__/__/__/__/Libraries/Startup/startup_W7500.s.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing ASM source to CMakeFiles/DeadZoneGeneration.dir/__/__/__/__/Libraries/Startup/startup_W7500.s.i"
	cd D:/W7500P/build/Projects/Peripheral_Examples/PWM/DeadZoneGeneration && "C:/Program Files (x86)/GNU Arm Embedded Toolchain/10 2021.10/bin/arm-none-eabi-gcc.exe" $(ASM_DEFINES) $(ASM_INCLUDES) $(ASM_FLAGS) -E D:/W7500P/Libraries/Startup/startup_W7500.s > CMakeFiles/DeadZoneGeneration.dir/__/__/__/__/Libraries/Startup/startup_W7500.s.i

Projects/Peripheral_Examples/PWM/DeadZoneGeneration/CMakeFiles/DeadZoneGeneration.dir/__/__/__/__/Libraries/Startup/startup_W7500.s.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling ASM source to assembly CMakeFiles/DeadZoneGeneration.dir/__/__/__/__/Libraries/Startup/startup_W7500.s.s"
	cd D:/W7500P/build/Projects/Peripheral_Examples/PWM/DeadZoneGeneration && "C:/Program Files (x86)/GNU Arm Embedded Toolchain/10 2021.10/bin/arm-none-eabi-gcc.exe" $(ASM_DEFINES) $(ASM_INCLUDES) $(ASM_FLAGS) -S D:/W7500P/Libraries/Startup/startup_W7500.s -o CMakeFiles/DeadZoneGeneration.dir/__/__/__/__/Libraries/Startup/startup_W7500.s.s

Projects/Peripheral_Examples/PWM/DeadZoneGeneration/CMakeFiles/DeadZoneGeneration.dir/__/__/__/__/Libraries/W7500x_stdPeriph_Driver/src/W7500x_gpio.c.obj: Projects/Peripheral_Examples/PWM/DeadZoneGeneration/CMakeFiles/DeadZoneGeneration.dir/flags.make
Projects/Peripheral_Examples/PWM/DeadZoneGeneration/CMakeFiles/DeadZoneGeneration.dir/__/__/__/__/Libraries/W7500x_stdPeriph_Driver/src/W7500x_gpio.c.obj: D:/W7500P/Libraries/W7500x_stdPeriph_Driver/src/W7500x_gpio.c
Projects/Peripheral_Examples/PWM/DeadZoneGeneration/CMakeFiles/DeadZoneGeneration.dir/__/__/__/__/Libraries/W7500x_stdPeriph_Driver/src/W7500x_gpio.c.obj: Projects/Peripheral_Examples/PWM/DeadZoneGeneration/CMakeFiles/DeadZoneGeneration.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=D:/W7500P/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object Projects/Peripheral_Examples/PWM/DeadZoneGeneration/CMakeFiles/DeadZoneGeneration.dir/__/__/__/__/Libraries/W7500x_stdPeriph_Driver/src/W7500x_gpio.c.obj"
	cd D:/W7500P/build/Projects/Peripheral_Examples/PWM/DeadZoneGeneration && "C:/Program Files (x86)/GNU Arm Embedded Toolchain/10 2021.10/bin/arm-none-eabi-gcc.exe" $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT Projects/Peripheral_Examples/PWM/DeadZoneGeneration/CMakeFiles/DeadZoneGeneration.dir/__/__/__/__/Libraries/W7500x_stdPeriph_Driver/src/W7500x_gpio.c.obj -MF CMakeFiles/DeadZoneGeneration.dir/__/__/__/__/Libraries/W7500x_stdPeriph_Driver/src/W7500x_gpio.c.obj.d -o CMakeFiles/DeadZoneGeneration.dir/__/__/__/__/Libraries/W7500x_stdPeriph_Driver/src/W7500x_gpio.c.obj -c D:/W7500P/Libraries/W7500x_stdPeriph_Driver/src/W7500x_gpio.c

Projects/Peripheral_Examples/PWM/DeadZoneGeneration/CMakeFiles/DeadZoneGeneration.dir/__/__/__/__/Libraries/W7500x_stdPeriph_Driver/src/W7500x_gpio.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/DeadZoneGeneration.dir/__/__/__/__/Libraries/W7500x_stdPeriph_Driver/src/W7500x_gpio.c.i"
	cd D:/W7500P/build/Projects/Peripheral_Examples/PWM/DeadZoneGeneration && "C:/Program Files (x86)/GNU Arm Embedded Toolchain/10 2021.10/bin/arm-none-eabi-gcc.exe" $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E D:/W7500P/Libraries/W7500x_stdPeriph_Driver/src/W7500x_gpio.c > CMakeFiles/DeadZoneGeneration.dir/__/__/__/__/Libraries/W7500x_stdPeriph_Driver/src/W7500x_gpio.c.i

Projects/Peripheral_Examples/PWM/DeadZoneGeneration/CMakeFiles/DeadZoneGeneration.dir/__/__/__/__/Libraries/W7500x_stdPeriph_Driver/src/W7500x_gpio.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/DeadZoneGeneration.dir/__/__/__/__/Libraries/W7500x_stdPeriph_Driver/src/W7500x_gpio.c.s"
	cd D:/W7500P/build/Projects/Peripheral_Examples/PWM/DeadZoneGeneration && "C:/Program Files (x86)/GNU Arm Embedded Toolchain/10 2021.10/bin/arm-none-eabi-gcc.exe" $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S D:/W7500P/Libraries/W7500x_stdPeriph_Driver/src/W7500x_gpio.c -o CMakeFiles/DeadZoneGeneration.dir/__/__/__/__/Libraries/W7500x_stdPeriph_Driver/src/W7500x_gpio.c.s

Projects/Peripheral_Examples/PWM/DeadZoneGeneration/CMakeFiles/DeadZoneGeneration.dir/__/__/__/__/Libraries/CMSIS/Device/WIZnet/W7500/Source/system_W7500x.c.obj: Projects/Peripheral_Examples/PWM/DeadZoneGeneration/CMakeFiles/DeadZoneGeneration.dir/flags.make
Projects/Peripheral_Examples/PWM/DeadZoneGeneration/CMakeFiles/DeadZoneGeneration.dir/__/__/__/__/Libraries/CMSIS/Device/WIZnet/W7500/Source/system_W7500x.c.obj: D:/W7500P/Libraries/CMSIS/Device/WIZnet/W7500/Source/system_W7500x.c
Projects/Peripheral_Examples/PWM/DeadZoneGeneration/CMakeFiles/DeadZoneGeneration.dir/__/__/__/__/Libraries/CMSIS/Device/WIZnet/W7500/Source/system_W7500x.c.obj: Projects/Peripheral_Examples/PWM/DeadZoneGeneration/CMakeFiles/DeadZoneGeneration.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=D:/W7500P/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building C object Projects/Peripheral_Examples/PWM/DeadZoneGeneration/CMakeFiles/DeadZoneGeneration.dir/__/__/__/__/Libraries/CMSIS/Device/WIZnet/W7500/Source/system_W7500x.c.obj"
	cd D:/W7500P/build/Projects/Peripheral_Examples/PWM/DeadZoneGeneration && "C:/Program Files (x86)/GNU Arm Embedded Toolchain/10 2021.10/bin/arm-none-eabi-gcc.exe" $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT Projects/Peripheral_Examples/PWM/DeadZoneGeneration/CMakeFiles/DeadZoneGeneration.dir/__/__/__/__/Libraries/CMSIS/Device/WIZnet/W7500/Source/system_W7500x.c.obj -MF CMakeFiles/DeadZoneGeneration.dir/__/__/__/__/Libraries/CMSIS/Device/WIZnet/W7500/Source/system_W7500x.c.obj.d -o CMakeFiles/DeadZoneGeneration.dir/__/__/__/__/Libraries/CMSIS/Device/WIZnet/W7500/Source/system_W7500x.c.obj -c D:/W7500P/Libraries/CMSIS/Device/WIZnet/W7500/Source/system_W7500x.c

Projects/Peripheral_Examples/PWM/DeadZoneGeneration/CMakeFiles/DeadZoneGeneration.dir/__/__/__/__/Libraries/CMSIS/Device/WIZnet/W7500/Source/system_W7500x.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/DeadZoneGeneration.dir/__/__/__/__/Libraries/CMSIS/Device/WIZnet/W7500/Source/system_W7500x.c.i"
	cd D:/W7500P/build/Projects/Peripheral_Examples/PWM/DeadZoneGeneration && "C:/Program Files (x86)/GNU Arm Embedded Toolchain/10 2021.10/bin/arm-none-eabi-gcc.exe" $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E D:/W7500P/Libraries/CMSIS/Device/WIZnet/W7500/Source/system_W7500x.c > CMakeFiles/DeadZoneGeneration.dir/__/__/__/__/Libraries/CMSIS/Device/WIZnet/W7500/Source/system_W7500x.c.i

Projects/Peripheral_Examples/PWM/DeadZoneGeneration/CMakeFiles/DeadZoneGeneration.dir/__/__/__/__/Libraries/CMSIS/Device/WIZnet/W7500/Source/system_W7500x.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/DeadZoneGeneration.dir/__/__/__/__/Libraries/CMSIS/Device/WIZnet/W7500/Source/system_W7500x.c.s"
	cd D:/W7500P/build/Projects/Peripheral_Examples/PWM/DeadZoneGeneration && "C:/Program Files (x86)/GNU Arm Embedded Toolchain/10 2021.10/bin/arm-none-eabi-gcc.exe" $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S D:/W7500P/Libraries/CMSIS/Device/WIZnet/W7500/Source/system_W7500x.c -o CMakeFiles/DeadZoneGeneration.dir/__/__/__/__/Libraries/CMSIS/Device/WIZnet/W7500/Source/system_W7500x.c.s

Projects/Peripheral_Examples/PWM/DeadZoneGeneration/CMakeFiles/DeadZoneGeneration.dir/__/__/__/__/Libraries/W7500x_stdPeriph_Driver/src/W7500x_pwm.c.obj: Projects/Peripheral_Examples/PWM/DeadZoneGeneration/CMakeFiles/DeadZoneGeneration.dir/flags.make
Projects/Peripheral_Examples/PWM/DeadZoneGeneration/CMakeFiles/DeadZoneGeneration.dir/__/__/__/__/Libraries/W7500x_stdPeriph_Driver/src/W7500x_pwm.c.obj: D:/W7500P/Libraries/W7500x_stdPeriph_Driver/src/W7500x_pwm.c
Projects/Peripheral_Examples/PWM/DeadZoneGeneration/CMakeFiles/DeadZoneGeneration.dir/__/__/__/__/Libraries/W7500x_stdPeriph_Driver/src/W7500x_pwm.c.obj: Projects/Peripheral_Examples/PWM/DeadZoneGeneration/CMakeFiles/DeadZoneGeneration.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=D:/W7500P/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building C object Projects/Peripheral_Examples/PWM/DeadZoneGeneration/CMakeFiles/DeadZoneGeneration.dir/__/__/__/__/Libraries/W7500x_stdPeriph_Driver/src/W7500x_pwm.c.obj"
	cd D:/W7500P/build/Projects/Peripheral_Examples/PWM/DeadZoneGeneration && "C:/Program Files (x86)/GNU Arm Embedded Toolchain/10 2021.10/bin/arm-none-eabi-gcc.exe" $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT Projects/Peripheral_Examples/PWM/DeadZoneGeneration/CMakeFiles/DeadZoneGeneration.dir/__/__/__/__/Libraries/W7500x_stdPeriph_Driver/src/W7500x_pwm.c.obj -MF CMakeFiles/DeadZoneGeneration.dir/__/__/__/__/Libraries/W7500x_stdPeriph_Driver/src/W7500x_pwm.c.obj.d -o CMakeFiles/DeadZoneGeneration.dir/__/__/__/__/Libraries/W7500x_stdPeriph_Driver/src/W7500x_pwm.c.obj -c D:/W7500P/Libraries/W7500x_stdPeriph_Driver/src/W7500x_pwm.c

Projects/Peripheral_Examples/PWM/DeadZoneGeneration/CMakeFiles/DeadZoneGeneration.dir/__/__/__/__/Libraries/W7500x_stdPeriph_Driver/src/W7500x_pwm.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/DeadZoneGeneration.dir/__/__/__/__/Libraries/W7500x_stdPeriph_Driver/src/W7500x_pwm.c.i"
	cd D:/W7500P/build/Projects/Peripheral_Examples/PWM/DeadZoneGeneration && "C:/Program Files (x86)/GNU Arm Embedded Toolchain/10 2021.10/bin/arm-none-eabi-gcc.exe" $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E D:/W7500P/Libraries/W7500x_stdPeriph_Driver/src/W7500x_pwm.c > CMakeFiles/DeadZoneGeneration.dir/__/__/__/__/Libraries/W7500x_stdPeriph_Driver/src/W7500x_pwm.c.i

Projects/Peripheral_Examples/PWM/DeadZoneGeneration/CMakeFiles/DeadZoneGeneration.dir/__/__/__/__/Libraries/W7500x_stdPeriph_Driver/src/W7500x_pwm.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/DeadZoneGeneration.dir/__/__/__/__/Libraries/W7500x_stdPeriph_Driver/src/W7500x_pwm.c.s"
	cd D:/W7500P/build/Projects/Peripheral_Examples/PWM/DeadZoneGeneration && "C:/Program Files (x86)/GNU Arm Embedded Toolchain/10 2021.10/bin/arm-none-eabi-gcc.exe" $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S D:/W7500P/Libraries/W7500x_stdPeriph_Driver/src/W7500x_pwm.c -o CMakeFiles/DeadZoneGeneration.dir/__/__/__/__/Libraries/W7500x_stdPeriph_Driver/src/W7500x_pwm.c.s

# Object files for target DeadZoneGeneration
DeadZoneGeneration_OBJECTS = \
"CMakeFiles/DeadZoneGeneration.dir/main.c.obj" \
"CMakeFiles/DeadZoneGeneration.dir/__/__/__/__/Libraries/Startup/startup_W7500.s.obj" \
"CMakeFiles/DeadZoneGeneration.dir/__/__/__/__/Libraries/W7500x_stdPeriph_Driver/src/W7500x_gpio.c.obj" \
"CMakeFiles/DeadZoneGeneration.dir/__/__/__/__/Libraries/CMSIS/Device/WIZnet/W7500/Source/system_W7500x.c.obj" \
"CMakeFiles/DeadZoneGeneration.dir/__/__/__/__/Libraries/W7500x_stdPeriph_Driver/src/W7500x_pwm.c.obj"

# External object files for target DeadZoneGeneration
DeadZoneGeneration_EXTERNAL_OBJECTS =

Projects/Peripheral_Examples/PWM/DeadZoneGeneration/DeadZoneGeneration: Projects/Peripheral_Examples/PWM/DeadZoneGeneration/CMakeFiles/DeadZoneGeneration.dir/main.c.obj
Projects/Peripheral_Examples/PWM/DeadZoneGeneration/DeadZoneGeneration: Projects/Peripheral_Examples/PWM/DeadZoneGeneration/CMakeFiles/DeadZoneGeneration.dir/__/__/__/__/Libraries/Startup/startup_W7500.s.obj
Projects/Peripheral_Examples/PWM/DeadZoneGeneration/DeadZoneGeneration: Projects/Peripheral_Examples/PWM/DeadZoneGeneration/CMakeFiles/DeadZoneGeneration.dir/__/__/__/__/Libraries/W7500x_stdPeriph_Driver/src/W7500x_gpio.c.obj
Projects/Peripheral_Examples/PWM/DeadZoneGeneration/DeadZoneGeneration: Projects/Peripheral_Examples/PWM/DeadZoneGeneration/CMakeFiles/DeadZoneGeneration.dir/__/__/__/__/Libraries/CMSIS/Device/WIZnet/W7500/Source/system_W7500x.c.obj
Projects/Peripheral_Examples/PWM/DeadZoneGeneration/DeadZoneGeneration: Projects/Peripheral_Examples/PWM/DeadZoneGeneration/CMakeFiles/DeadZoneGeneration.dir/__/__/__/__/Libraries/W7500x_stdPeriph_Driver/src/W7500x_pwm.c.obj
Projects/Peripheral_Examples/PWM/DeadZoneGeneration/DeadZoneGeneration: Projects/Peripheral_Examples/PWM/DeadZoneGeneration/CMakeFiles/DeadZoneGeneration.dir/build.make
Projects/Peripheral_Examples/PWM/DeadZoneGeneration/DeadZoneGeneration: Libraries/libGPIO_FILES.a
Projects/Peripheral_Examples/PWM/DeadZoneGeneration/DeadZoneGeneration: Libraries/libPWM_FILES.a
Projects/Peripheral_Examples/PWM/DeadZoneGeneration/DeadZoneGeneration: Libraries/libSYSTEM_W7500X_FILES.a
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=D:/W7500P/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Linking C executable DeadZoneGeneration"
	cd D:/W7500P/build/Projects/Peripheral_Examples/PWM/DeadZoneGeneration && "C:/Program Files (x86)/GNU Arm Embedded Toolchain/10 2021.10/bin/arm-none-eabi-gcc.exe" -g -TD:/W7500P/Libraries/gcc_W7500.ld -mcpu=cortex-m0 -mthumb -specs=nano.specs -lc -lm -Wl,-Map=DeadZoneGeneration.map,--cref -Wl,--gc-sections -Xlinker -print-memory-usage $(DeadZoneGeneration_OBJECTS) $(DeadZoneGeneration_EXTERNAL_OBJECTS) -o DeadZoneGeneration  ../../../../Libraries/libGPIO_FILES.a ../../../../Libraries/libPWM_FILES.a ../../../../Libraries/libSYSTEM_W7500X_FILES.a 
	cd D:/W7500P/build/Projects/Peripheral_Examples/PWM/DeadZoneGeneration && "C:/Program Files (x86)/GNU Arm Embedded Toolchain/10 2021.10/bin/arm-none-eabi-objcopy" -Obinary D:/W7500P/build/Projects/Peripheral_Examples/PWM/DeadZoneGeneration/DeadZoneGeneration DeadZoneGeneration.bin

# Rule to build all files generated by this target.
Projects/Peripheral_Examples/PWM/DeadZoneGeneration/CMakeFiles/DeadZoneGeneration.dir/build: Projects/Peripheral_Examples/PWM/DeadZoneGeneration/DeadZoneGeneration
.PHONY : Projects/Peripheral_Examples/PWM/DeadZoneGeneration/CMakeFiles/DeadZoneGeneration.dir/build

Projects/Peripheral_Examples/PWM/DeadZoneGeneration/CMakeFiles/DeadZoneGeneration.dir/clean:
	cd D:/W7500P/build/Projects/Peripheral_Examples/PWM/DeadZoneGeneration && $(CMAKE_COMMAND) -P CMakeFiles/DeadZoneGeneration.dir/cmake_clean.cmake
.PHONY : Projects/Peripheral_Examples/PWM/DeadZoneGeneration/CMakeFiles/DeadZoneGeneration.dir/clean

Projects/Peripheral_Examples/PWM/DeadZoneGeneration/CMakeFiles/DeadZoneGeneration.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" D:/W7500P D:/W7500P/Projects/Peripheral_Examples/PWM/DeadZoneGeneration D:/W7500P/build D:/W7500P/build/Projects/Peripheral_Examples/PWM/DeadZoneGeneration D:/W7500P/build/Projects/Peripheral_Examples/PWM/DeadZoneGeneration/CMakeFiles/DeadZoneGeneration.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : Projects/Peripheral_Examples/PWM/DeadZoneGeneration/CMakeFiles/DeadZoneGeneration.dir/depend

