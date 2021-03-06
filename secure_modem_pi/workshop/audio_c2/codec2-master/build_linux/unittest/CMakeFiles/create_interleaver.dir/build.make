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
include unittest/CMakeFiles/create_interleaver.dir/depend.make

# Include the progress variables for this target.
include unittest/CMakeFiles/create_interleaver.dir/progress.make

# Include the compile flags for this target's objects.
include unittest/CMakeFiles/create_interleaver.dir/flags.make

unittest/CMakeFiles/create_interleaver.dir/create_interleaver.c.o: unittest/CMakeFiles/create_interleaver.dir/flags.make
unittest/CMakeFiles/create_interleaver.dir/create_interleaver.c.o: ../unittest/create_interleaver.c
	$(CMAKE_COMMAND) -E cmake_progress_report /home/pi/dev/secure_modem/workshop/audio_c2/codec2-master/build_linux/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object unittest/CMakeFiles/create_interleaver.dir/create_interleaver.c.o"
	cd /home/pi/dev/secure_modem/workshop/audio_c2/codec2-master/build_linux/unittest && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/create_interleaver.dir/create_interleaver.c.o   -c /home/pi/dev/secure_modem/workshop/audio_c2/codec2-master/unittest/create_interleaver.c

unittest/CMakeFiles/create_interleaver.dir/create_interleaver.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/create_interleaver.dir/create_interleaver.c.i"
	cd /home/pi/dev/secure_modem/workshop/audio_c2/codec2-master/build_linux/unittest && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -E /home/pi/dev/secure_modem/workshop/audio_c2/codec2-master/unittest/create_interleaver.c > CMakeFiles/create_interleaver.dir/create_interleaver.c.i

unittest/CMakeFiles/create_interleaver.dir/create_interleaver.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/create_interleaver.dir/create_interleaver.c.s"
	cd /home/pi/dev/secure_modem/workshop/audio_c2/codec2-master/build_linux/unittest && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -S /home/pi/dev/secure_modem/workshop/audio_c2/codec2-master/unittest/create_interleaver.c -o CMakeFiles/create_interleaver.dir/create_interleaver.c.s

unittest/CMakeFiles/create_interleaver.dir/create_interleaver.c.o.requires:
.PHONY : unittest/CMakeFiles/create_interleaver.dir/create_interleaver.c.o.requires

unittest/CMakeFiles/create_interleaver.dir/create_interleaver.c.o.provides: unittest/CMakeFiles/create_interleaver.dir/create_interleaver.c.o.requires
	$(MAKE) -f unittest/CMakeFiles/create_interleaver.dir/build.make unittest/CMakeFiles/create_interleaver.dir/create_interleaver.c.o.provides.build
.PHONY : unittest/CMakeFiles/create_interleaver.dir/create_interleaver.c.o.provides

unittest/CMakeFiles/create_interleaver.dir/create_interleaver.c.o.provides.build: unittest/CMakeFiles/create_interleaver.dir/create_interleaver.c.o

# Object files for target create_interleaver
create_interleaver_OBJECTS = \
"CMakeFiles/create_interleaver.dir/create_interleaver.c.o"

# External object files for target create_interleaver
create_interleaver_EXTERNAL_OBJECTS =

unittest/create_interleaver: unittest/CMakeFiles/create_interleaver.dir/create_interleaver.c.o
unittest/create_interleaver: unittest/CMakeFiles/create_interleaver.dir/build.make
unittest/create_interleaver: src/libcodec2.so.0.3
unittest/create_interleaver: /usr/lib/arm-linux-gnueabihf/libspeexdsp.so
unittest/create_interleaver: unittest/CMakeFiles/create_interleaver.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking C executable create_interleaver"
	cd /home/pi/dev/secure_modem/workshop/audio_c2/codec2-master/build_linux/unittest && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/create_interleaver.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
unittest/CMakeFiles/create_interleaver.dir/build: unittest/create_interleaver
.PHONY : unittest/CMakeFiles/create_interleaver.dir/build

unittest/CMakeFiles/create_interleaver.dir/requires: unittest/CMakeFiles/create_interleaver.dir/create_interleaver.c.o.requires
.PHONY : unittest/CMakeFiles/create_interleaver.dir/requires

unittest/CMakeFiles/create_interleaver.dir/clean:
	cd /home/pi/dev/secure_modem/workshop/audio_c2/codec2-master/build_linux/unittest && $(CMAKE_COMMAND) -P CMakeFiles/create_interleaver.dir/cmake_clean.cmake
.PHONY : unittest/CMakeFiles/create_interleaver.dir/clean

unittest/CMakeFiles/create_interleaver.dir/depend:
	cd /home/pi/dev/secure_modem/workshop/audio_c2/codec2-master/build_linux && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/pi/dev/secure_modem/workshop/audio_c2/codec2-master /home/pi/dev/secure_modem/workshop/audio_c2/codec2-master/unittest /home/pi/dev/secure_modem/workshop/audio_c2/codec2-master/build_linux /home/pi/dev/secure_modem/workshop/audio_c2/codec2-master/build_linux/unittest /home/pi/dev/secure_modem/workshop/audio_c2/codec2-master/build_linux/unittest/CMakeFiles/create_interleaver.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : unittest/CMakeFiles/create_interleaver.dir/depend

