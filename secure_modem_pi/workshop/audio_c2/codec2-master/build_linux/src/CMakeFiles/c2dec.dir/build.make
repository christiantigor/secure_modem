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
include src/CMakeFiles/c2dec.dir/depend.make

# Include the progress variables for this target.
include src/CMakeFiles/c2dec.dir/progress.make

# Include the compile flags for this target's objects.
include src/CMakeFiles/c2dec.dir/flags.make

src/CMakeFiles/c2dec.dir/c2dec.c.o: src/CMakeFiles/c2dec.dir/flags.make
src/CMakeFiles/c2dec.dir/c2dec.c.o: ../src/c2dec.c
	$(CMAKE_COMMAND) -E cmake_progress_report /home/pi/dev/secure_modem/workshop/audio_c2/codec2-master/build_linux/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object src/CMakeFiles/c2dec.dir/c2dec.c.o"
	cd /home/pi/dev/secure_modem/workshop/audio_c2/codec2-master/build_linux/src && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/c2dec.dir/c2dec.c.o   -c /home/pi/dev/secure_modem/workshop/audio_c2/codec2-master/src/c2dec.c

src/CMakeFiles/c2dec.dir/c2dec.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/c2dec.dir/c2dec.c.i"
	cd /home/pi/dev/secure_modem/workshop/audio_c2/codec2-master/build_linux/src && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -E /home/pi/dev/secure_modem/workshop/audio_c2/codec2-master/src/c2dec.c > CMakeFiles/c2dec.dir/c2dec.c.i

src/CMakeFiles/c2dec.dir/c2dec.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/c2dec.dir/c2dec.c.s"
	cd /home/pi/dev/secure_modem/workshop/audio_c2/codec2-master/build_linux/src && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -S /home/pi/dev/secure_modem/workshop/audio_c2/codec2-master/src/c2dec.c -o CMakeFiles/c2dec.dir/c2dec.c.s

src/CMakeFiles/c2dec.dir/c2dec.c.o.requires:
.PHONY : src/CMakeFiles/c2dec.dir/c2dec.c.o.requires

src/CMakeFiles/c2dec.dir/c2dec.c.o.provides: src/CMakeFiles/c2dec.dir/c2dec.c.o.requires
	$(MAKE) -f src/CMakeFiles/c2dec.dir/build.make src/CMakeFiles/c2dec.dir/c2dec.c.o.provides.build
.PHONY : src/CMakeFiles/c2dec.dir/c2dec.c.o.provides

src/CMakeFiles/c2dec.dir/c2dec.c.o.provides.build: src/CMakeFiles/c2dec.dir/c2dec.c.o

# Object files for target c2dec
c2dec_OBJECTS = \
"CMakeFiles/c2dec.dir/c2dec.c.o"

# External object files for target c2dec
c2dec_EXTERNAL_OBJECTS =

src/c2dec: src/CMakeFiles/c2dec.dir/c2dec.c.o
src/c2dec: src/CMakeFiles/c2dec.dir/build.make
src/c2dec: /usr/lib/arm-linux-gnueabihf/libspeexdsp.so
src/c2dec: src/libcodec2.so.0.3
src/c2dec: /usr/lib/arm-linux-gnueabihf/libspeexdsp.so
src/c2dec: src/CMakeFiles/c2dec.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking C executable c2dec"
	cd /home/pi/dev/secure_modem/workshop/audio_c2/codec2-master/build_linux/src && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/c2dec.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/CMakeFiles/c2dec.dir/build: src/c2dec
.PHONY : src/CMakeFiles/c2dec.dir/build

src/CMakeFiles/c2dec.dir/requires: src/CMakeFiles/c2dec.dir/c2dec.c.o.requires
.PHONY : src/CMakeFiles/c2dec.dir/requires

src/CMakeFiles/c2dec.dir/clean:
	cd /home/pi/dev/secure_modem/workshop/audio_c2/codec2-master/build_linux/src && $(CMAKE_COMMAND) -P CMakeFiles/c2dec.dir/cmake_clean.cmake
.PHONY : src/CMakeFiles/c2dec.dir/clean

src/CMakeFiles/c2dec.dir/depend:
	cd /home/pi/dev/secure_modem/workshop/audio_c2/codec2-master/build_linux && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/pi/dev/secure_modem/workshop/audio_c2/codec2-master /home/pi/dev/secure_modem/workshop/audio_c2/codec2-master/src /home/pi/dev/secure_modem/workshop/audio_c2/codec2-master/build_linux /home/pi/dev/secure_modem/workshop/audio_c2/codec2-master/build_linux/src /home/pi/dev/secure_modem/workshop/audio_c2/codec2-master/build_linux/src/CMakeFiles/c2dec.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/CMakeFiles/c2dec.dir/depend

