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
include src/CMakeFiles/fdmdv_get_test_bits.dir/depend.make

# Include the progress variables for this target.
include src/CMakeFiles/fdmdv_get_test_bits.dir/progress.make

# Include the compile flags for this target's objects.
include src/CMakeFiles/fdmdv_get_test_bits.dir/flags.make

src/CMakeFiles/fdmdv_get_test_bits.dir/fdmdv_get_test_bits.c.o: src/CMakeFiles/fdmdv_get_test_bits.dir/flags.make
src/CMakeFiles/fdmdv_get_test_bits.dir/fdmdv_get_test_bits.c.o: ../src/fdmdv_get_test_bits.c
	$(CMAKE_COMMAND) -E cmake_progress_report /home/pi/dev/secure_modem/workshop/audio_c2/codec2-master/build_linux/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object src/CMakeFiles/fdmdv_get_test_bits.dir/fdmdv_get_test_bits.c.o"
	cd /home/pi/dev/secure_modem/workshop/audio_c2/codec2-master/build_linux/src && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/fdmdv_get_test_bits.dir/fdmdv_get_test_bits.c.o   -c /home/pi/dev/secure_modem/workshop/audio_c2/codec2-master/src/fdmdv_get_test_bits.c

src/CMakeFiles/fdmdv_get_test_bits.dir/fdmdv_get_test_bits.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/fdmdv_get_test_bits.dir/fdmdv_get_test_bits.c.i"
	cd /home/pi/dev/secure_modem/workshop/audio_c2/codec2-master/build_linux/src && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -E /home/pi/dev/secure_modem/workshop/audio_c2/codec2-master/src/fdmdv_get_test_bits.c > CMakeFiles/fdmdv_get_test_bits.dir/fdmdv_get_test_bits.c.i

src/CMakeFiles/fdmdv_get_test_bits.dir/fdmdv_get_test_bits.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/fdmdv_get_test_bits.dir/fdmdv_get_test_bits.c.s"
	cd /home/pi/dev/secure_modem/workshop/audio_c2/codec2-master/build_linux/src && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -S /home/pi/dev/secure_modem/workshop/audio_c2/codec2-master/src/fdmdv_get_test_bits.c -o CMakeFiles/fdmdv_get_test_bits.dir/fdmdv_get_test_bits.c.s

src/CMakeFiles/fdmdv_get_test_bits.dir/fdmdv_get_test_bits.c.o.requires:
.PHONY : src/CMakeFiles/fdmdv_get_test_bits.dir/fdmdv_get_test_bits.c.o.requires

src/CMakeFiles/fdmdv_get_test_bits.dir/fdmdv_get_test_bits.c.o.provides: src/CMakeFiles/fdmdv_get_test_bits.dir/fdmdv_get_test_bits.c.o.requires
	$(MAKE) -f src/CMakeFiles/fdmdv_get_test_bits.dir/build.make src/CMakeFiles/fdmdv_get_test_bits.dir/fdmdv_get_test_bits.c.o.provides.build
.PHONY : src/CMakeFiles/fdmdv_get_test_bits.dir/fdmdv_get_test_bits.c.o.provides

src/CMakeFiles/fdmdv_get_test_bits.dir/fdmdv_get_test_bits.c.o.provides.build: src/CMakeFiles/fdmdv_get_test_bits.dir/fdmdv_get_test_bits.c.o

src/CMakeFiles/fdmdv_get_test_bits.dir/fdmdv.c.o: src/CMakeFiles/fdmdv_get_test_bits.dir/flags.make
src/CMakeFiles/fdmdv_get_test_bits.dir/fdmdv.c.o: ../src/fdmdv.c
	$(CMAKE_COMMAND) -E cmake_progress_report /home/pi/dev/secure_modem/workshop/audio_c2/codec2-master/build_linux/CMakeFiles $(CMAKE_PROGRESS_2)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object src/CMakeFiles/fdmdv_get_test_bits.dir/fdmdv.c.o"
	cd /home/pi/dev/secure_modem/workshop/audio_c2/codec2-master/build_linux/src && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/fdmdv_get_test_bits.dir/fdmdv.c.o   -c /home/pi/dev/secure_modem/workshop/audio_c2/codec2-master/src/fdmdv.c

src/CMakeFiles/fdmdv_get_test_bits.dir/fdmdv.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/fdmdv_get_test_bits.dir/fdmdv.c.i"
	cd /home/pi/dev/secure_modem/workshop/audio_c2/codec2-master/build_linux/src && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -E /home/pi/dev/secure_modem/workshop/audio_c2/codec2-master/src/fdmdv.c > CMakeFiles/fdmdv_get_test_bits.dir/fdmdv.c.i

src/CMakeFiles/fdmdv_get_test_bits.dir/fdmdv.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/fdmdv_get_test_bits.dir/fdmdv.c.s"
	cd /home/pi/dev/secure_modem/workshop/audio_c2/codec2-master/build_linux/src && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -S /home/pi/dev/secure_modem/workshop/audio_c2/codec2-master/src/fdmdv.c -o CMakeFiles/fdmdv_get_test_bits.dir/fdmdv.c.s

src/CMakeFiles/fdmdv_get_test_bits.dir/fdmdv.c.o.requires:
.PHONY : src/CMakeFiles/fdmdv_get_test_bits.dir/fdmdv.c.o.requires

src/CMakeFiles/fdmdv_get_test_bits.dir/fdmdv.c.o.provides: src/CMakeFiles/fdmdv_get_test_bits.dir/fdmdv.c.o.requires
	$(MAKE) -f src/CMakeFiles/fdmdv_get_test_bits.dir/build.make src/CMakeFiles/fdmdv_get_test_bits.dir/fdmdv.c.o.provides.build
.PHONY : src/CMakeFiles/fdmdv_get_test_bits.dir/fdmdv.c.o.provides

src/CMakeFiles/fdmdv_get_test_bits.dir/fdmdv.c.o.provides.build: src/CMakeFiles/fdmdv_get_test_bits.dir/fdmdv.c.o

src/CMakeFiles/fdmdv_get_test_bits.dir/kiss_fft.c.o: src/CMakeFiles/fdmdv_get_test_bits.dir/flags.make
src/CMakeFiles/fdmdv_get_test_bits.dir/kiss_fft.c.o: ../src/kiss_fft.c
	$(CMAKE_COMMAND) -E cmake_progress_report /home/pi/dev/secure_modem/workshop/audio_c2/codec2-master/build_linux/CMakeFiles $(CMAKE_PROGRESS_3)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object src/CMakeFiles/fdmdv_get_test_bits.dir/kiss_fft.c.o"
	cd /home/pi/dev/secure_modem/workshop/audio_c2/codec2-master/build_linux/src && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/fdmdv_get_test_bits.dir/kiss_fft.c.o   -c /home/pi/dev/secure_modem/workshop/audio_c2/codec2-master/src/kiss_fft.c

src/CMakeFiles/fdmdv_get_test_bits.dir/kiss_fft.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/fdmdv_get_test_bits.dir/kiss_fft.c.i"
	cd /home/pi/dev/secure_modem/workshop/audio_c2/codec2-master/build_linux/src && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -E /home/pi/dev/secure_modem/workshop/audio_c2/codec2-master/src/kiss_fft.c > CMakeFiles/fdmdv_get_test_bits.dir/kiss_fft.c.i

src/CMakeFiles/fdmdv_get_test_bits.dir/kiss_fft.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/fdmdv_get_test_bits.dir/kiss_fft.c.s"
	cd /home/pi/dev/secure_modem/workshop/audio_c2/codec2-master/build_linux/src && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -S /home/pi/dev/secure_modem/workshop/audio_c2/codec2-master/src/kiss_fft.c -o CMakeFiles/fdmdv_get_test_bits.dir/kiss_fft.c.s

src/CMakeFiles/fdmdv_get_test_bits.dir/kiss_fft.c.o.requires:
.PHONY : src/CMakeFiles/fdmdv_get_test_bits.dir/kiss_fft.c.o.requires

src/CMakeFiles/fdmdv_get_test_bits.dir/kiss_fft.c.o.provides: src/CMakeFiles/fdmdv_get_test_bits.dir/kiss_fft.c.o.requires
	$(MAKE) -f src/CMakeFiles/fdmdv_get_test_bits.dir/build.make src/CMakeFiles/fdmdv_get_test_bits.dir/kiss_fft.c.o.provides.build
.PHONY : src/CMakeFiles/fdmdv_get_test_bits.dir/kiss_fft.c.o.provides

src/CMakeFiles/fdmdv_get_test_bits.dir/kiss_fft.c.o.provides.build: src/CMakeFiles/fdmdv_get_test_bits.dir/kiss_fft.c.o

# Object files for target fdmdv_get_test_bits
fdmdv_get_test_bits_OBJECTS = \
"CMakeFiles/fdmdv_get_test_bits.dir/fdmdv_get_test_bits.c.o" \
"CMakeFiles/fdmdv_get_test_bits.dir/fdmdv.c.o" \
"CMakeFiles/fdmdv_get_test_bits.dir/kiss_fft.c.o"

# External object files for target fdmdv_get_test_bits
fdmdv_get_test_bits_EXTERNAL_OBJECTS =

src/fdmdv_get_test_bits: src/CMakeFiles/fdmdv_get_test_bits.dir/fdmdv_get_test_bits.c.o
src/fdmdv_get_test_bits: src/CMakeFiles/fdmdv_get_test_bits.dir/fdmdv.c.o
src/fdmdv_get_test_bits: src/CMakeFiles/fdmdv_get_test_bits.dir/kiss_fft.c.o
src/fdmdv_get_test_bits: src/CMakeFiles/fdmdv_get_test_bits.dir/build.make
src/fdmdv_get_test_bits: /usr/lib/arm-linux-gnueabihf/libspeexdsp.so
src/fdmdv_get_test_bits: src/CMakeFiles/fdmdv_get_test_bits.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking C executable fdmdv_get_test_bits"
	cd /home/pi/dev/secure_modem/workshop/audio_c2/codec2-master/build_linux/src && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/fdmdv_get_test_bits.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/CMakeFiles/fdmdv_get_test_bits.dir/build: src/fdmdv_get_test_bits
.PHONY : src/CMakeFiles/fdmdv_get_test_bits.dir/build

src/CMakeFiles/fdmdv_get_test_bits.dir/requires: src/CMakeFiles/fdmdv_get_test_bits.dir/fdmdv_get_test_bits.c.o.requires
src/CMakeFiles/fdmdv_get_test_bits.dir/requires: src/CMakeFiles/fdmdv_get_test_bits.dir/fdmdv.c.o.requires
src/CMakeFiles/fdmdv_get_test_bits.dir/requires: src/CMakeFiles/fdmdv_get_test_bits.dir/kiss_fft.c.o.requires
.PHONY : src/CMakeFiles/fdmdv_get_test_bits.dir/requires

src/CMakeFiles/fdmdv_get_test_bits.dir/clean:
	cd /home/pi/dev/secure_modem/workshop/audio_c2/codec2-master/build_linux/src && $(CMAKE_COMMAND) -P CMakeFiles/fdmdv_get_test_bits.dir/cmake_clean.cmake
.PHONY : src/CMakeFiles/fdmdv_get_test_bits.dir/clean

src/CMakeFiles/fdmdv_get_test_bits.dir/depend:
	cd /home/pi/dev/secure_modem/workshop/audio_c2/codec2-master/build_linux && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/pi/dev/secure_modem/workshop/audio_c2/codec2-master /home/pi/dev/secure_modem/workshop/audio_c2/codec2-master/src /home/pi/dev/secure_modem/workshop/audio_c2/codec2-master/build_linux /home/pi/dev/secure_modem/workshop/audio_c2/codec2-master/build_linux/src /home/pi/dev/secure_modem/workshop/audio_c2/codec2-master/build_linux/src/CMakeFiles/fdmdv_get_test_bits.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/CMakeFiles/fdmdv_get_test_bits.dir/depend

