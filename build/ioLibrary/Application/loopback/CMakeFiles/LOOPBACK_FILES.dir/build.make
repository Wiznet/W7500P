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
include ioLibrary/Application/loopback/CMakeFiles/LOOPBACK_FILES.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include ioLibrary/Application/loopback/CMakeFiles/LOOPBACK_FILES.dir/compiler_depend.make

# Include the progress variables for this target.
include ioLibrary/Application/loopback/CMakeFiles/LOOPBACK_FILES.dir/progress.make

# Include the compile flags for this target's objects.
include ioLibrary/Application/loopback/CMakeFiles/LOOPBACK_FILES.dir/flags.make

ioLibrary/Application/loopback/CMakeFiles/LOOPBACK_FILES.dir/loopback.c.obj: ioLibrary/Application/loopback/CMakeFiles/LOOPBACK_FILES.dir/flags.make
ioLibrary/Application/loopback/CMakeFiles/LOOPBACK_FILES.dir/loopback.c.obj: D:/W7500P/ioLibrary/Application/loopback/loopback.c
ioLibrary/Application/loopback/CMakeFiles/LOOPBACK_FILES.dir/loopback.c.obj: ioLibrary/Application/loopback/CMakeFiles/LOOPBACK_FILES.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=D:/W7500P/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object ioLibrary/Application/loopback/CMakeFiles/LOOPBACK_FILES.dir/loopback.c.obj"
	cd D:/W7500P/build/ioLibrary/Application/loopback && "C:/Program Files (x86)/GNU Arm Embedded Toolchain/10 2021.10/bin/arm-none-eabi-gcc.exe" $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT ioLibrary/Application/loopback/CMakeFiles/LOOPBACK_FILES.dir/loopback.c.obj -MF CMakeFiles/LOOPBACK_FILES.dir/loopback.c.obj.d -o CMakeFiles/LOOPBACK_FILES.dir/loopback.c.obj -c D:/W7500P/ioLibrary/Application/loopback/loopback.c

ioLibrary/Application/loopback/CMakeFiles/LOOPBACK_FILES.dir/loopback.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/LOOPBACK_FILES.dir/loopback.c.i"
	cd D:/W7500P/build/ioLibrary/Application/loopback && "C:/Program Files (x86)/GNU Arm Embedded Toolchain/10 2021.10/bin/arm-none-eabi-gcc.exe" $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E D:/W7500P/ioLibrary/Application/loopback/loopback.c > CMakeFiles/LOOPBACK_FILES.dir/loopback.c.i

ioLibrary/Application/loopback/CMakeFiles/LOOPBACK_FILES.dir/loopback.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/LOOPBACK_FILES.dir/loopback.c.s"
	cd D:/W7500P/build/ioLibrary/Application/loopback && "C:/Program Files (x86)/GNU Arm Embedded Toolchain/10 2021.10/bin/arm-none-eabi-gcc.exe" $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S D:/W7500P/ioLibrary/Application/loopback/loopback.c -o CMakeFiles/LOOPBACK_FILES.dir/loopback.c.s

ioLibrary/Application/loopback/CMakeFiles/LOOPBACK_FILES.dir/__/__/Ethernet/socket.c.obj: ioLibrary/Application/loopback/CMakeFiles/LOOPBACK_FILES.dir/flags.make
ioLibrary/Application/loopback/CMakeFiles/LOOPBACK_FILES.dir/__/__/Ethernet/socket.c.obj: D:/W7500P/ioLibrary/Ethernet/socket.c
ioLibrary/Application/loopback/CMakeFiles/LOOPBACK_FILES.dir/__/__/Ethernet/socket.c.obj: ioLibrary/Application/loopback/CMakeFiles/LOOPBACK_FILES.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=D:/W7500P/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object ioLibrary/Application/loopback/CMakeFiles/LOOPBACK_FILES.dir/__/__/Ethernet/socket.c.obj"
	cd D:/W7500P/build/ioLibrary/Application/loopback && "C:/Program Files (x86)/GNU Arm Embedded Toolchain/10 2021.10/bin/arm-none-eabi-gcc.exe" $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT ioLibrary/Application/loopback/CMakeFiles/LOOPBACK_FILES.dir/__/__/Ethernet/socket.c.obj -MF CMakeFiles/LOOPBACK_FILES.dir/__/__/Ethernet/socket.c.obj.d -o CMakeFiles/LOOPBACK_FILES.dir/__/__/Ethernet/socket.c.obj -c D:/W7500P/ioLibrary/Ethernet/socket.c

ioLibrary/Application/loopback/CMakeFiles/LOOPBACK_FILES.dir/__/__/Ethernet/socket.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/LOOPBACK_FILES.dir/__/__/Ethernet/socket.c.i"
	cd D:/W7500P/build/ioLibrary/Application/loopback && "C:/Program Files (x86)/GNU Arm Embedded Toolchain/10 2021.10/bin/arm-none-eabi-gcc.exe" $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E D:/W7500P/ioLibrary/Ethernet/socket.c > CMakeFiles/LOOPBACK_FILES.dir/__/__/Ethernet/socket.c.i

ioLibrary/Application/loopback/CMakeFiles/LOOPBACK_FILES.dir/__/__/Ethernet/socket.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/LOOPBACK_FILES.dir/__/__/Ethernet/socket.c.s"
	cd D:/W7500P/build/ioLibrary/Application/loopback && "C:/Program Files (x86)/GNU Arm Embedded Toolchain/10 2021.10/bin/arm-none-eabi-gcc.exe" $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S D:/W7500P/ioLibrary/Ethernet/socket.c -o CMakeFiles/LOOPBACK_FILES.dir/__/__/Ethernet/socket.c.s

ioLibrary/Application/loopback/CMakeFiles/LOOPBACK_FILES.dir/__/__/__/Libraries/CMSIS/Device/WIZnet/W7500/Source/system_W7500x.c.obj: ioLibrary/Application/loopback/CMakeFiles/LOOPBACK_FILES.dir/flags.make
ioLibrary/Application/loopback/CMakeFiles/LOOPBACK_FILES.dir/__/__/__/Libraries/CMSIS/Device/WIZnet/W7500/Source/system_W7500x.c.obj: D:/W7500P/Libraries/CMSIS/Device/WIZnet/W7500/Source/system_W7500x.c
ioLibrary/Application/loopback/CMakeFiles/LOOPBACK_FILES.dir/__/__/__/Libraries/CMSIS/Device/WIZnet/W7500/Source/system_W7500x.c.obj: ioLibrary/Application/loopback/CMakeFiles/LOOPBACK_FILES.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=D:/W7500P/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object ioLibrary/Application/loopback/CMakeFiles/LOOPBACK_FILES.dir/__/__/__/Libraries/CMSIS/Device/WIZnet/W7500/Source/system_W7500x.c.obj"
	cd D:/W7500P/build/ioLibrary/Application/loopback && "C:/Program Files (x86)/GNU Arm Embedded Toolchain/10 2021.10/bin/arm-none-eabi-gcc.exe" $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT ioLibrary/Application/loopback/CMakeFiles/LOOPBACK_FILES.dir/__/__/__/Libraries/CMSIS/Device/WIZnet/W7500/Source/system_W7500x.c.obj -MF CMakeFiles/LOOPBACK_FILES.dir/__/__/__/Libraries/CMSIS/Device/WIZnet/W7500/Source/system_W7500x.c.obj.d -o CMakeFiles/LOOPBACK_FILES.dir/__/__/__/Libraries/CMSIS/Device/WIZnet/W7500/Source/system_W7500x.c.obj -c D:/W7500P/Libraries/CMSIS/Device/WIZnet/W7500/Source/system_W7500x.c

ioLibrary/Application/loopback/CMakeFiles/LOOPBACK_FILES.dir/__/__/__/Libraries/CMSIS/Device/WIZnet/W7500/Source/system_W7500x.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/LOOPBACK_FILES.dir/__/__/__/Libraries/CMSIS/Device/WIZnet/W7500/Source/system_W7500x.c.i"
	cd D:/W7500P/build/ioLibrary/Application/loopback && "C:/Program Files (x86)/GNU Arm Embedded Toolchain/10 2021.10/bin/arm-none-eabi-gcc.exe" $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E D:/W7500P/Libraries/CMSIS/Device/WIZnet/W7500/Source/system_W7500x.c > CMakeFiles/LOOPBACK_FILES.dir/__/__/__/Libraries/CMSIS/Device/WIZnet/W7500/Source/system_W7500x.c.i

ioLibrary/Application/loopback/CMakeFiles/LOOPBACK_FILES.dir/__/__/__/Libraries/CMSIS/Device/WIZnet/W7500/Source/system_W7500x.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/LOOPBACK_FILES.dir/__/__/__/Libraries/CMSIS/Device/WIZnet/W7500/Source/system_W7500x.c.s"
	cd D:/W7500P/build/ioLibrary/Application/loopback && "C:/Program Files (x86)/GNU Arm Embedded Toolchain/10 2021.10/bin/arm-none-eabi-gcc.exe" $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S D:/W7500P/Libraries/CMSIS/Device/WIZnet/W7500/Source/system_W7500x.c -o CMakeFiles/LOOPBACK_FILES.dir/__/__/__/Libraries/CMSIS/Device/WIZnet/W7500/Source/system_W7500x.c.s

ioLibrary/Application/loopback/CMakeFiles/LOOPBACK_FILES.dir/__/__/__/Libraries/W7500x_stdPeriph_Driver/src/W7500x_wztoe.c.obj: ioLibrary/Application/loopback/CMakeFiles/LOOPBACK_FILES.dir/flags.make
ioLibrary/Application/loopback/CMakeFiles/LOOPBACK_FILES.dir/__/__/__/Libraries/W7500x_stdPeriph_Driver/src/W7500x_wztoe.c.obj: D:/W7500P/Libraries/W7500x_stdPeriph_Driver/src/W7500x_wztoe.c
ioLibrary/Application/loopback/CMakeFiles/LOOPBACK_FILES.dir/__/__/__/Libraries/W7500x_stdPeriph_Driver/src/W7500x_wztoe.c.obj: ioLibrary/Application/loopback/CMakeFiles/LOOPBACK_FILES.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=D:/W7500P/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building C object ioLibrary/Application/loopback/CMakeFiles/LOOPBACK_FILES.dir/__/__/__/Libraries/W7500x_stdPeriph_Driver/src/W7500x_wztoe.c.obj"
	cd D:/W7500P/build/ioLibrary/Application/loopback && "C:/Program Files (x86)/GNU Arm Embedded Toolchain/10 2021.10/bin/arm-none-eabi-gcc.exe" $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT ioLibrary/Application/loopback/CMakeFiles/LOOPBACK_FILES.dir/__/__/__/Libraries/W7500x_stdPeriph_Driver/src/W7500x_wztoe.c.obj -MF CMakeFiles/LOOPBACK_FILES.dir/__/__/__/Libraries/W7500x_stdPeriph_Driver/src/W7500x_wztoe.c.obj.d -o CMakeFiles/LOOPBACK_FILES.dir/__/__/__/Libraries/W7500x_stdPeriph_Driver/src/W7500x_wztoe.c.obj -c D:/W7500P/Libraries/W7500x_stdPeriph_Driver/src/W7500x_wztoe.c

ioLibrary/Application/loopback/CMakeFiles/LOOPBACK_FILES.dir/__/__/__/Libraries/W7500x_stdPeriph_Driver/src/W7500x_wztoe.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/LOOPBACK_FILES.dir/__/__/__/Libraries/W7500x_stdPeriph_Driver/src/W7500x_wztoe.c.i"
	cd D:/W7500P/build/ioLibrary/Application/loopback && "C:/Program Files (x86)/GNU Arm Embedded Toolchain/10 2021.10/bin/arm-none-eabi-gcc.exe" $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E D:/W7500P/Libraries/W7500x_stdPeriph_Driver/src/W7500x_wztoe.c > CMakeFiles/LOOPBACK_FILES.dir/__/__/__/Libraries/W7500x_stdPeriph_Driver/src/W7500x_wztoe.c.i

ioLibrary/Application/loopback/CMakeFiles/LOOPBACK_FILES.dir/__/__/__/Libraries/W7500x_stdPeriph_Driver/src/W7500x_wztoe.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/LOOPBACK_FILES.dir/__/__/__/Libraries/W7500x_stdPeriph_Driver/src/W7500x_wztoe.c.s"
	cd D:/W7500P/build/ioLibrary/Application/loopback && "C:/Program Files (x86)/GNU Arm Embedded Toolchain/10 2021.10/bin/arm-none-eabi-gcc.exe" $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S D:/W7500P/Libraries/W7500x_stdPeriph_Driver/src/W7500x_wztoe.c -o CMakeFiles/LOOPBACK_FILES.dir/__/__/__/Libraries/W7500x_stdPeriph_Driver/src/W7500x_wztoe.c.s

ioLibrary/Application/loopback/CMakeFiles/LOOPBACK_FILES.dir/__/__/Ethernet/wizchip_conf.c.obj: ioLibrary/Application/loopback/CMakeFiles/LOOPBACK_FILES.dir/flags.make
ioLibrary/Application/loopback/CMakeFiles/LOOPBACK_FILES.dir/__/__/Ethernet/wizchip_conf.c.obj: D:/W7500P/ioLibrary/Ethernet/wizchip_conf.c
ioLibrary/Application/loopback/CMakeFiles/LOOPBACK_FILES.dir/__/__/Ethernet/wizchip_conf.c.obj: ioLibrary/Application/loopback/CMakeFiles/LOOPBACK_FILES.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=D:/W7500P/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building C object ioLibrary/Application/loopback/CMakeFiles/LOOPBACK_FILES.dir/__/__/Ethernet/wizchip_conf.c.obj"
	cd D:/W7500P/build/ioLibrary/Application/loopback && "C:/Program Files (x86)/GNU Arm Embedded Toolchain/10 2021.10/bin/arm-none-eabi-gcc.exe" $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT ioLibrary/Application/loopback/CMakeFiles/LOOPBACK_FILES.dir/__/__/Ethernet/wizchip_conf.c.obj -MF CMakeFiles/LOOPBACK_FILES.dir/__/__/Ethernet/wizchip_conf.c.obj.d -o CMakeFiles/LOOPBACK_FILES.dir/__/__/Ethernet/wizchip_conf.c.obj -c D:/W7500P/ioLibrary/Ethernet/wizchip_conf.c

ioLibrary/Application/loopback/CMakeFiles/LOOPBACK_FILES.dir/__/__/Ethernet/wizchip_conf.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/LOOPBACK_FILES.dir/__/__/Ethernet/wizchip_conf.c.i"
	cd D:/W7500P/build/ioLibrary/Application/loopback && "C:/Program Files (x86)/GNU Arm Embedded Toolchain/10 2021.10/bin/arm-none-eabi-gcc.exe" $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E D:/W7500P/ioLibrary/Ethernet/wizchip_conf.c > CMakeFiles/LOOPBACK_FILES.dir/__/__/Ethernet/wizchip_conf.c.i

ioLibrary/Application/loopback/CMakeFiles/LOOPBACK_FILES.dir/__/__/Ethernet/wizchip_conf.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/LOOPBACK_FILES.dir/__/__/Ethernet/wizchip_conf.c.s"
	cd D:/W7500P/build/ioLibrary/Application/loopback && "C:/Program Files (x86)/GNU Arm Embedded Toolchain/10 2021.10/bin/arm-none-eabi-gcc.exe" $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S D:/W7500P/ioLibrary/Ethernet/wizchip_conf.c -o CMakeFiles/LOOPBACK_FILES.dir/__/__/Ethernet/wizchip_conf.c.s

# Object files for target LOOPBACK_FILES
LOOPBACK_FILES_OBJECTS = \
"CMakeFiles/LOOPBACK_FILES.dir/loopback.c.obj" \
"CMakeFiles/LOOPBACK_FILES.dir/__/__/Ethernet/socket.c.obj" \
"CMakeFiles/LOOPBACK_FILES.dir/__/__/__/Libraries/CMSIS/Device/WIZnet/W7500/Source/system_W7500x.c.obj" \
"CMakeFiles/LOOPBACK_FILES.dir/__/__/__/Libraries/W7500x_stdPeriph_Driver/src/W7500x_wztoe.c.obj" \
"CMakeFiles/LOOPBACK_FILES.dir/__/__/Ethernet/wizchip_conf.c.obj"

# External object files for target LOOPBACK_FILES
LOOPBACK_FILES_EXTERNAL_OBJECTS =

ioLibrary/Application/loopback/libLOOPBACK_FILES.a: ioLibrary/Application/loopback/CMakeFiles/LOOPBACK_FILES.dir/loopback.c.obj
ioLibrary/Application/loopback/libLOOPBACK_FILES.a: ioLibrary/Application/loopback/CMakeFiles/LOOPBACK_FILES.dir/__/__/Ethernet/socket.c.obj
ioLibrary/Application/loopback/libLOOPBACK_FILES.a: ioLibrary/Application/loopback/CMakeFiles/LOOPBACK_FILES.dir/__/__/__/Libraries/CMSIS/Device/WIZnet/W7500/Source/system_W7500x.c.obj
ioLibrary/Application/loopback/libLOOPBACK_FILES.a: ioLibrary/Application/loopback/CMakeFiles/LOOPBACK_FILES.dir/__/__/__/Libraries/W7500x_stdPeriph_Driver/src/W7500x_wztoe.c.obj
ioLibrary/Application/loopback/libLOOPBACK_FILES.a: ioLibrary/Application/loopback/CMakeFiles/LOOPBACK_FILES.dir/__/__/Ethernet/wizchip_conf.c.obj
ioLibrary/Application/loopback/libLOOPBACK_FILES.a: ioLibrary/Application/loopback/CMakeFiles/LOOPBACK_FILES.dir/build.make
ioLibrary/Application/loopback/libLOOPBACK_FILES.a: ioLibrary/Application/loopback/CMakeFiles/LOOPBACK_FILES.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=D:/W7500P/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Linking C static library libLOOPBACK_FILES.a"
	cd D:/W7500P/build/ioLibrary/Application/loopback && $(CMAKE_COMMAND) -P CMakeFiles/LOOPBACK_FILES.dir/cmake_clean_target.cmake
	cd D:/W7500P/build/ioLibrary/Application/loopback && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/LOOPBACK_FILES.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
ioLibrary/Application/loopback/CMakeFiles/LOOPBACK_FILES.dir/build: ioLibrary/Application/loopback/libLOOPBACK_FILES.a
.PHONY : ioLibrary/Application/loopback/CMakeFiles/LOOPBACK_FILES.dir/build

ioLibrary/Application/loopback/CMakeFiles/LOOPBACK_FILES.dir/clean:
	cd D:/W7500P/build/ioLibrary/Application/loopback && $(CMAKE_COMMAND) -P CMakeFiles/LOOPBACK_FILES.dir/cmake_clean.cmake
.PHONY : ioLibrary/Application/loopback/CMakeFiles/LOOPBACK_FILES.dir/clean

ioLibrary/Application/loopback/CMakeFiles/LOOPBACK_FILES.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" D:/W7500P D:/W7500P/ioLibrary/Application/loopback D:/W7500P/build D:/W7500P/build/ioLibrary/Application/loopback D:/W7500P/build/ioLibrary/Application/loopback/CMakeFiles/LOOPBACK_FILES.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : ioLibrary/Application/loopback/CMakeFiles/LOOPBACK_FILES.dir/depend
