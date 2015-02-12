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
include unittest/CMakeFiles/vqtrainsp.dir/depend.make

# Include the progress variables for this target.
include unittest/CMakeFiles/vqtrainsp.dir/progress.make

# Include the compile flags for this target's objects.
include unittest/CMakeFiles/vqtrainsp.dir/flags.make

unittest/CMakeFiles/vqtrainsp.dir/vqtrainsp.c.o: unittest/CMakeFiles/vqtrainsp.dir/flags.make
unittest/CMakeFiles/vqtrainsp.dir/vqtrainsp.c.o: ../unittest/vqtrainsp.c
	$(CMAKE_COMMAND) -E cmake_progress_report /home/pi/dev/secure_modem/workshop/audio_c2/codec2-master/build_linux/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object unittest/CMakeFiles/vqtrainsp.dir/vqtrainsp.c.o"
	cd /home/pi/dev/secure_modem/workshop/audio_c2/codec2-master/build_linux/unittest && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/vqtrainsp.dir/vqtrainsp.c.o   -c /home/pi/dev/secure_modem/workshop/audio_c2/codec2-master/unittest/vqtrainsp.c

unittest/CMakeFiles/vqtrainsp.dir/vqtrainsp.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/vqtrainsp.dir/vqtrainsp.c.i"
	cd /home/pi/dev/secure_modem/workshop/audio_c2/codec2-master/build_linux/unittest && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -E /home/pi/dev/secure_modem/workshop/audio_c2/codec2-master/unittest/vqtrainsp.c > CMakeFiles/vqtrainsp.dir/vqtrainsp.c.i

unittest/CMakeFiles/vqtrainsp.dir/vqtrainsp.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/vqtrainsp.dir/vqtrainsp.c.s"
	cd /home/pi/dev/secure_modem/workshop/audio_c2/codec2-master/build_linux/unittest && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -S /home/pi/dev/secure_modem/workshop/audio_c2/codec2-master/unittest/vqtrainsp.c -o CMakeFiles/vqtrainsp.dir/vqtrainsp.c.s

unittest/CMakeFiles/vqtrainsp.dir/vqtrainsp.c.o.requires:
.PHONY : unittest/CMakeFiles/vqtrainsp.dir/vqtrainsp.c.o.requires

unittest/CMakeFiles/vqtrainsp.dir/vqtrainsp.c.o.provides: unittest/CMakeFiles/vqtrainsp.dir/vqtrainsp.c.o.requires
	$(MAKE) -f unittest/CMakeFiles/vqtrainsp.dir/build.make unittest/CMakeFiles/vqtrainsp.dir/vqtrainsp.c.o.provides.build
.PHONY : unittest/CMakeFiles/vqtrainsp.dir/vqtrainsp.c.o.provides

unittest/CMakeFiles/vqtrainsp.dir/vqtrainsp.c.o.provides.build: unittest/CMakeFiles/vqtrainsp.dir/vqtrainsp.c.o

# Object files for target vqtrainsp
vqtrainsp_OBJECTS = \
"CMakeFiles/vqtrainsp.dir/vqtrainsp.c.o"

# External object files for target vqtrainsp
vqtrainsp_EXTERNAL_OBJECTS =

unittest/vqtrainsp: unittest/CMakeFiles/vqtrainsp.dir/vqtrainsp.c.o
unittest/vqtrainsp: unittest/CMakeFiles/vqtrainsp.dir/build.make
unittest/vqtrainsp: src/libcodec2.so.0.3
unittest/vqtrainsp: /usr/lib/arm-linux-gnueabihf/libspeexdsp.so
unittest/vqtrainsp: unittest/CMakeFiles/vqtrainsp.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking C executable vqtrainsp"
	cd /home/pi/dev/secure_modem/workshop/audio_c2/codec2-master/build_linux/unittest && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/vqtrainsp.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
unittest/CMakeFiles/vqtrainsp.dir/build: unittest/vqtrainsp
.PHONY : unittest/CMakeFiles/vqtrainsp.dir/build

unittest/CMakeFiles/vqtrainsp.dir/requires: unittest/CMakeFiles/vqtrainsp.dir/vqtrainsp.c.o.requires
.PHONY : unittest/CMakeFiles/vqtrainsp.dir/requires

unittest/CMakeFiles/vqtrainsp.dir/clean:
	cd /home/pi/dev/secure_modem/workshop/audio_c2/codec2-master/build_linux/unittest && $(CMAKE_COMMAND) -P CMakeFiles/vqtrainsp.dir/cmake_clean.cmake
.PHONY : unittest/CMakeFiles/vqtrainsp.dir/clean

unittest/CMakeFiles/vqtrainsp.dir/depend:
	cd /home/pi/dev/secure_modem/workshop/audio_c2/codec2-master/build_linux && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/pi/dev/secure_modem/workshop/audio_c2/codec2-master /home/pi/dev/secure_modem/workshop/audio_c2/codec2-master/unittest /home/pi/dev/secure_modem/workshop/audio_c2/codec2-master/build_linux /home/pi/dev/secure_modem/workshop/audio_c2/codec2-master/build_linux/unittest /home/pi/dev/secure_modem/workshop/audio_c2/codec2-master/build_linux/unittest/CMakeFiles/vqtrainsp.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : unittest/CMakeFiles/vqtrainsp.dir/depend
