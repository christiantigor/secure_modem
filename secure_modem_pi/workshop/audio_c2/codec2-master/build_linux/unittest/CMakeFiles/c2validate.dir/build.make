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
include unittest/CMakeFiles/c2validate.dir/depend.make

# Include the progress variables for this target.
include unittest/CMakeFiles/c2validate.dir/progress.make

# Include the compile flags for this target's objects.
include unittest/CMakeFiles/c2validate.dir/flags.make

unittest/CMakeFiles/c2validate.dir/c2validate.c.o: unittest/CMakeFiles/c2validate.dir/flags.make
unittest/CMakeFiles/c2validate.dir/c2validate.c.o: ../unittest/c2validate.c
	$(CMAKE_COMMAND) -E cmake_progress_report /home/pi/dev/secure_modem/workshop/audio_c2/codec2-master/build_linux/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object unittest/CMakeFiles/c2validate.dir/c2validate.c.o"
	cd /home/pi/dev/secure_modem/workshop/audio_c2/codec2-master/build_linux/unittest && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/c2validate.dir/c2validate.c.o   -c /home/pi/dev/secure_modem/workshop/audio_c2/codec2-master/unittest/c2validate.c

unittest/CMakeFiles/c2validate.dir/c2validate.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/c2validate.dir/c2validate.c.i"
	cd /home/pi/dev/secure_modem/workshop/audio_c2/codec2-master/build_linux/unittest && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -E /home/pi/dev/secure_modem/workshop/audio_c2/codec2-master/unittest/c2validate.c > CMakeFiles/c2validate.dir/c2validate.c.i

unittest/CMakeFiles/c2validate.dir/c2validate.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/c2validate.dir/c2validate.c.s"
	cd /home/pi/dev/secure_modem/workshop/audio_c2/codec2-master/build_linux/unittest && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -S /home/pi/dev/secure_modem/workshop/audio_c2/codec2-master/unittest/c2validate.c -o CMakeFiles/c2validate.dir/c2validate.c.s

unittest/CMakeFiles/c2validate.dir/c2validate.c.o.requires:
.PHONY : unittest/CMakeFiles/c2validate.dir/c2validate.c.o.requires

unittest/CMakeFiles/c2validate.dir/c2validate.c.o.provides: unittest/CMakeFiles/c2validate.dir/c2validate.c.o.requires
	$(MAKE) -f unittest/CMakeFiles/c2validate.dir/build.make unittest/CMakeFiles/c2validate.dir/c2validate.c.o.provides.build
.PHONY : unittest/CMakeFiles/c2validate.dir/c2validate.c.o.provides

unittest/CMakeFiles/c2validate.dir/c2validate.c.o.provides.build: unittest/CMakeFiles/c2validate.dir/c2validate.c.o

# Object files for target c2validate
c2validate_OBJECTS = \
"CMakeFiles/c2validate.dir/c2validate.c.o"

# External object files for target c2validate
c2validate_EXTERNAL_OBJECTS =

unittest/c2validate: unittest/CMakeFiles/c2validate.dir/c2validate.c.o
unittest/c2validate: unittest/CMakeFiles/c2validate.dir/build.make
unittest/c2validate: src/libcodec2.so.0.3
unittest/c2validate: /usr/lib/arm-linux-gnueabihf/libspeexdsp.so
unittest/c2validate: unittest/CMakeFiles/c2validate.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking C executable c2validate"
	cd /home/pi/dev/secure_modem/workshop/audio_c2/codec2-master/build_linux/unittest && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/c2validate.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
unittest/CMakeFiles/c2validate.dir/build: unittest/c2validate
.PHONY : unittest/CMakeFiles/c2validate.dir/build

unittest/CMakeFiles/c2validate.dir/requires: unittest/CMakeFiles/c2validate.dir/c2validate.c.o.requires
.PHONY : unittest/CMakeFiles/c2validate.dir/requires

unittest/CMakeFiles/c2validate.dir/clean:
	cd /home/pi/dev/secure_modem/workshop/audio_c2/codec2-master/build_linux/unittest && $(CMAKE_COMMAND) -P CMakeFiles/c2validate.dir/cmake_clean.cmake
.PHONY : unittest/CMakeFiles/c2validate.dir/clean

unittest/CMakeFiles/c2validate.dir/depend:
	cd /home/pi/dev/secure_modem/workshop/audio_c2/codec2-master/build_linux && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/pi/dev/secure_modem/workshop/audio_c2/codec2-master /home/pi/dev/secure_modem/workshop/audio_c2/codec2-master/unittest /home/pi/dev/secure_modem/workshop/audio_c2/codec2-master/build_linux /home/pi/dev/secure_modem/workshop/audio_c2/codec2-master/build_linux/unittest /home/pi/dev/secure_modem/workshop/audio_c2/codec2-master/build_linux/unittest/CMakeFiles/c2validate.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : unittest/CMakeFiles/c2validate.dir/depend

