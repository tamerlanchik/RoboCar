# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.10

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


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
CMAKE_SOURCE_DIR = /home/andrey/Documents/RoboCar/hardware/test

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/andrey/Documents/RoboCar/hardware/test/build

# Include any dependencies generated for this target.
include CMakeFiles/arduino_mock_sample.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/arduino_mock_sample.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/arduino_mock_sample.dir/flags.make

CMakeFiles/arduino_mock_sample.dir/test_main.cpp.o: CMakeFiles/arduino_mock_sample.dir/flags.make
CMakeFiles/arduino_mock_sample.dir/test_main.cpp.o: ../test_main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/andrey/Documents/RoboCar/hardware/test/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/arduino_mock_sample.dir/test_main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/arduino_mock_sample.dir/test_main.cpp.o -c /home/andrey/Documents/RoboCar/hardware/test/test_main.cpp

CMakeFiles/arduino_mock_sample.dir/test_main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/arduino_mock_sample.dir/test_main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/andrey/Documents/RoboCar/hardware/test/test_main.cpp > CMakeFiles/arduino_mock_sample.dir/test_main.cpp.i

CMakeFiles/arduino_mock_sample.dir/test_main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/arduino_mock_sample.dir/test_main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/andrey/Documents/RoboCar/hardware/test/test_main.cpp -o CMakeFiles/arduino_mock_sample.dir/test_main.cpp.s

CMakeFiles/arduino_mock_sample.dir/test_main.cpp.o.requires:

.PHONY : CMakeFiles/arduino_mock_sample.dir/test_main.cpp.o.requires

CMakeFiles/arduino_mock_sample.dir/test_main.cpp.o.provides: CMakeFiles/arduino_mock_sample.dir/test_main.cpp.o.requires
	$(MAKE) -f CMakeFiles/arduino_mock_sample.dir/build.make CMakeFiles/arduino_mock_sample.dir/test_main.cpp.o.provides.build
.PHONY : CMakeFiles/arduino_mock_sample.dir/test_main.cpp.o.provides

CMakeFiles/arduino_mock_sample.dir/test_main.cpp.o.provides.build: CMakeFiles/arduino_mock_sample.dir/test_main.cpp.o


# Object files for target arduino_mock_sample
arduino_mock_sample_OBJECTS = \
"CMakeFiles/arduino_mock_sample.dir/test_main.cpp.o"

# External object files for target arduino_mock_sample
arduino_mock_sample_EXTERNAL_OBJECTS =

arduino_mock_sample: CMakeFiles/arduino_mock_sample.dir/test_main.cpp.o
arduino_mock_sample: CMakeFiles/arduino_mock_sample.dir/build.make
arduino_mock_sample: /lib/gtest/gtest/src/gtest-build/libgtest.a
arduino_mock_sample: /lib/gmock/gmock/src/gmock-build/libgmock.a
arduino_mock_sample: /dist/lib/libarduino_mock.a
arduino_mock_sample: CMakeFiles/arduino_mock_sample.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/andrey/Documents/RoboCar/hardware/test/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable arduino_mock_sample"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/arduino_mock_sample.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/arduino_mock_sample.dir/build: arduino_mock_sample

.PHONY : CMakeFiles/arduino_mock_sample.dir/build

CMakeFiles/arduino_mock_sample.dir/requires: CMakeFiles/arduino_mock_sample.dir/test_main.cpp.o.requires

.PHONY : CMakeFiles/arduino_mock_sample.dir/requires

CMakeFiles/arduino_mock_sample.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/arduino_mock_sample.dir/cmake_clean.cmake
.PHONY : CMakeFiles/arduino_mock_sample.dir/clean

CMakeFiles/arduino_mock_sample.dir/depend:
	cd /home/andrey/Documents/RoboCar/hardware/test/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/andrey/Documents/RoboCar/hardware/test /home/andrey/Documents/RoboCar/hardware/test /home/andrey/Documents/RoboCar/hardware/test/build /home/andrey/Documents/RoboCar/hardware/test/build /home/andrey/Documents/RoboCar/hardware/test/build/CMakeFiles/arduino_mock_sample.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/arduino_mock_sample.dir/depend
