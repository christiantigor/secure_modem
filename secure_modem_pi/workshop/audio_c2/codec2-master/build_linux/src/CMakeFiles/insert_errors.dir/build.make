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
include src/CMakeFiles/insert_errors.dir/depend.make

# Include the progress variables for this target.
include src/CMakeFiles/insert_errors.dir/progress.make

# Include the compile flags for this target's objects.
include src/CMakeFiles/insert_errors.dir/flags.make

src/CMakeFiles/insert_errors.dir/insert_errors.c.o: src/CMakeFiles/insert_errors.dir/flags.make
src/CMakeFiles/insert_errors.dir/insert_errors.c.o: ../src/insert_errors.c
	$(CMAKE_COMMAND) -E cmake_progress_report /home/pi/dev/secure_modem/workshop/audio_c2/codec2-master/build_linux/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object src/CMakeFiles/insert_errors.dir/insert_errors.c.o"
	cd /home/pi/dev/secure_modem/workshop/audio_c2/codec2-master/build_linux/src && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/insert_errors.dir/insert_errors.c.o   -c /home/pi/dev/secure_modem/workshop/audio_c2/codec2-master/src/insert_errors.c

src/CMakeFiles/insert_errors.dir/insert_errors.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/insert_errors.dir/insert_errors.c.i"
	cd /home/pi/dev/secure_modem/workshop/audio_c2/codec2-master/build_linux/src && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -E /home/pi/dev/secure_modem/workshop/audio_c2/codec2-master/src/insert_errors.c > CMakeFiles/insert_errors.dir/insert_errors.c.i

src/CMakeFiles/insert_errors.dir/insert_errors.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/insert_errors.dir/insert_errors.c.s"
	cd /home/pi/dev/secure_modem/workshop/audio_c2/codec2-master/build_linux/src && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -S /home/pi/dev/secure_modem/workshop/audio_c2/codec2-master/src/insert_errors.c -o CMakeFiles/insert_errors.dir/insert_errors.c.s

src/CMakeFiles/insert_errors.dir/insert_errors.c.o.requires:
.PHONY : src/CMakeFiles/insert_errors.dir/insert_errors.c.o.requires

src/CMakeFiles/insert_errors.dir/insert_errors.c.o.provides: src/CMakeFiles/insert_errors.dir/insert_errors.c.o.requires
	$(MAKE) -f src/CMakeFiles/insert_errors.dir/build.make src/CMakeFiles/insert_errors.dir/insert_errors.c.o.provides.build
.PHONY : src/CMakeFiles/insert_errors.dir/insert_errors.c.o.provides

src/CMakeFiles/insert_errors.dir/insert_errors.c.o.provides.build: src/CMakeFiles/insert_errors.dir/insert_errors.c.o

# Object files for target insert_errors
insert_errors_OBJECTS = \
"CMakeFiles/insert_errors.dir/insert_errors.c.o"

# External object files for target insert_errors
insert_errors_EXTERNAL_OBJECTS =

src/insert_errors: src/CMakeFiles/insert_errors.dir/insert_errors.c.o
src/insert_errors: src/CMakeFiles/insert_errors.dir/build.make
src/insert_errors: /usr/lib/arm-linux-gnueabihf/libspeexdsp.so
src/insert_errors: src/CMakeFiles/insert_errors.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking C executable insert_errors"
	cd /home/pi/dev/secure_modem/workshop/audio_c2/codec2-master/build_linux/src && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/insert_errors.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/CMakeFiles/insert_errors.dir/build: src/insert_errors
.PHONY : src/CMakeFiles/insert_errors.dir/build

src/CMakeFiles/insert_errors.dir/requires: src/CMakeFiles/insert_errors.dir/insert_errors.c.o.requires
.PHONY : src/CMakeFiles/insert_errors.dir/requires

src/CMakeFiles/insert_errors.dir/clean:
	cd /home/pi/dev/secure_modem/workshop/audio_c2/codec2-master/build_linux/src && $(CMAKE_COMMAND) -P CMakeFiles/insert_errors.dir/cmake_clean.cmake
.PHONY : src/CMakeFiles/insert_errors.dir/clean

src/CMakeFiles/insert_errors.dir/depend:
	cd /home/pi/dev/secure_modem/workshop/audio_c2/codec2-master/build_linux && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/pi/dev/secure_modem/workshop/audio_c2/codec2-master /home/pi/dev/secure_modem/workshop/audio_c2/codec2-master/src /home/pi/dev/secure_modem/workshop/audio_c2/codec2-master/build_linux /home/pi/dev/secure_modem/workshop/audio_c2/codec2-master/build_linux/src /home/pi/dev/secure_modem/workshop/audio_c2/codec2-master/build_linux/src/CMakeFiles/insert_errors.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/CMakeFiles/insert_errors.dir/depend

