# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list

# Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/pi/dev/secure_modem/workshop/audio_c2/codec2-master

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/pi/dev/secure_modem/workshop/audio_c2/codec2-master/build_linux

# Include any dependencies generated for this target.
include unittest/CMakeFiles/pre.dir/depend.make

# Include the progress variables for this target.
include unittest/CMakeFiles/pre.dir/progress.make

# Include the compile flags for this target's objects.
include unittest/CMakeFiles/pre.dir/flags.make

unittest/CMakeFiles/pre.dir/pre.c.o: unittest/CMakeFiles/pre.dir/flags.make
unittest/CMakeFiles/pre.dir/pre.c.o: ../unittest/pre.c
	$(CMAKE_COMMAND) -E cmake_progress_report /home/pi/dev/secure_modem/workshop/audio_c2/codec2-master/build_linux/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object unittest/CMakeFiles/pre.dir/pre.c.o"
	cd /home/pi/dev/secure_modem/workshop/audio_c2/codec2-master/build_linux/unittest && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/pre.dir/pre.c.o   -c /home/pi/dev/secure_modem/workshop/audio_c2/codec2-master/unittest/pre.c

unittest/CMakeFiles/pre.dir/pre.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/pre.dir/pre.c.i"
	cd /home/pi/dev/secure_modem/workshop/audio_c2/codec2-master/build_linux/unittest && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -E /home/pi/dev/secure_modem/workshop/audio_c2/codec2-master/unittest/pre.c > CMakeFiles/pre.dir/pre.c.i

unittest/CMakeFiles/pre.dir/pre.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/pre.dir/pre.c.s"
	cd /home/pi/dev/secure_modem/workshop/audio_c2/codec2-master/build_linux/unittest && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -S /home/pi/dev/secure_modem/workshop/audio_c2/codec2-master/unittest/pre.c -o CMakeFiles/pre.dir/pre.c.s

unittest/CMakeFiles/pre.dir/pre.c.o.requires:
.PHONY : unittest/CMakeFiles/pre.dir/pre.c.o.requires

unittest/CMakeFiles/pre.dir/pre.c.o.provides: unittest/CMakeFiles/pre.dir/pre.c.o.requires
	$(MAKE) -f unittest/CMakeFiles/pre.dir/build.make unittest/CMakeFiles/pre.dir/pre.c.o.provides.build
.PHONY : unittest/CMakeFiles/pre.dir/pre.c.o.provides

unittest/CMakeFiles/pre.dir/pre.c.o.provides.build: unittest/CMakeFiles/pre.dir/pre.c.o

unittest/CMakeFiles/pre.dir/__/src/lpc.c.o: unittest/CMakeFiles/pre.dir/flags.make
unittest/CMakeFiles/pre.dir/__/src/lpc.c.o: ../src/lpc.c
	$(CMAKE_COMMAND) -E cmake_progress_report /home/pi/dev/secure_modem/workshop/audio_c2/codec2-master/build_linux/CMakeFiles $(CMAKE_PROGRESS_2)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object unittest/CMakeFiles/pre.dir/__/src/lpc.c.o"
	cd /home/pi/dev/secure_modem/workshop/audio_c2/codec2-master/build_linux/unittest && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/pre.dir/__/src/lpc.c.o   -c /home/pi/dev/secure_modem/workshop/audio_c2/codec2-master/src/lpc.c

unittest/CMakeFiles/pre.dir/__/src/lpc.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/pre.dir/__/src/lpc.c.i"
	cd /home/pi/dev/secure_modem/workshop/audio_c2/codec2-master/build_linux/unittest && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -E /home/pi/dev/secure_modem/workshop/audio_c2/codec2-master/src/lpc.c > CMakeFiles/pre.dir/__/src/lpc.c.i

unittest/CMakeFiles/pre.dir/__/src/lpc.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/pre.dir/__/src/lpc.c.s"
	cd /home/pi/dev/secure_modem/workshop/audio_c2/codec2-master/build_linux/unittest && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -S /home/pi/dev/secure_modem/workshop/audio_c2/codec2-master/src/lpc.c -o CMakeFiles/pre.dir/__/src/lpc.c.s

unittest/CMakeFiles/pre.dir/__/src/lpc.c.o.requires:
.PHONY : unittest/CMakeFiles/pre.dir/__/src/lpc.c.o.requires

unittest/CMakeFiles/pre.dir/__/src/lpc.c.o.provides: unittest/CMakeFiles/pre.dir/__/src/lpc.c.o.requires
	$(MAKE) -f unittest/CMakeFiles/pre.dir/build.make unittest/CMakeFiles/pre.dir/__/src/lpc.c.o.provides.build
.PHONY : unittest/CMakeFiles/pre.dir/__/src/lpc.c.o.provides

unittest/CMakeFiles/pre.dir/__/src/lpc.c.o.provides.build: unittest/CMakeFiles/pre.dir/__/src/lpc.c.o

# Object files for target pre
pre_OBJECTS = \
"CMakeFiles/pre.dir/pre.c.o" \
"CMakeFiles/pre.dir/__/src/lpc.c.o"

# External object files for target pre
pre_EXTERNAL_OBJECTS =

unittest/pre: unittest/CMakeFiles/pre.dir/pre.c.o
unittest/pre: unittest/CMakeFiles/pre.dir/__/src/lpc.c.o
unittest/pre: unittest/CMakeFiles/pre.dir/build.make
unittest/pre: src/libcodec2.so.0.3
unittest/pre: /usr/lib/arm-linux-gnueabihf/libspeexdsp.so
unittest/pre: unittest/CMakeFiles/pre.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking C executable pre"
	cd /home/pi/dev/secure_modem/workshop/audio_c2/codec2-master/build_linux/unittest && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/pre.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
unittest/CMakeFiles/pre.dir/build: unittest/pre
.PHONY : unittest/CMakeFiles/pre.dir/build

unittest/CMakeFiles/pre.dir/requires: unittest/CMakeFiles/pre.dir/pre.c.o.requires
unittest/CMakeFiles/pre.dir/requires: unittest/CMakeFiles/pre.dir/__/src/lpc.c.o.requires
.PHONY : unittest/CMakeFiles/pre.dir/requires

unittest/CMakeFiles/pre.dir/clean:
	cd /home/pi/dev/secure_modem/workshop/audio_c2/codec2-master/build_linux/unittest && $(CMAKE_COMMAND) -P CMakeFiles/pre.dir/cmake_clean.cmake
.PHONY : unittest/CMakeFiles/pre.dir/clean

unittest/CMakeFiles/pre.dir/depend:
	cd /home/pi/dev/secure_modem/workshop/audio_c2/codec2-master/build_linux && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/pi/dev/secure_modem/workshop/audio_c2/codec2-master /home/pi/dev/secure_modem/workshop/audio_c2/codec2-master/unittest /home/pi/dev/secure_modem/workshop/audio_c2/codec2-master/build_linux /home/pi/dev/secure_modem/workshop/audio_c2/codec2-master/build_linux/unittest /home/pi/dev/secure_modem/workshop/audio_c2/codec2-master/build_linux/unittest/CMakeFiles/pre.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : unittest/CMakeFiles/pre.dir/depend

