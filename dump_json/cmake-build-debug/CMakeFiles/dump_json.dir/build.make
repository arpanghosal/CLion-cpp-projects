# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.17

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
CMAKE_COMMAND = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake

# The command to remove a file.
RM = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/arpanghosal/Software_tutorials/gitprojects/CLion-cpp-projects/dump_json

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/arpanghosal/Software_tutorials/gitprojects/CLion-cpp-projects/dump_json/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/dump_json.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/dump_json.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/dump_json.dir/flags.make

CMakeFiles/dump_json.dir/main.cpp.o: CMakeFiles/dump_json.dir/flags.make
CMakeFiles/dump_json.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/arpanghosal/Software_tutorials/gitprojects/CLion-cpp-projects/dump_json/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/dump_json.dir/main.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/dump_json.dir/main.cpp.o -c /Users/arpanghosal/Software_tutorials/gitprojects/CLion-cpp-projects/dump_json/main.cpp

CMakeFiles/dump_json.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/dump_json.dir/main.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/arpanghosal/Software_tutorials/gitprojects/CLion-cpp-projects/dump_json/main.cpp > CMakeFiles/dump_json.dir/main.cpp.i

CMakeFiles/dump_json.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/dump_json.dir/main.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/arpanghosal/Software_tutorials/gitprojects/CLion-cpp-projects/dump_json/main.cpp -o CMakeFiles/dump_json.dir/main.cpp.s

# Object files for target dump_json
dump_json_OBJECTS = \
"CMakeFiles/dump_json.dir/main.cpp.o"

# External object files for target dump_json
dump_json_EXTERNAL_OBJECTS =

dump_json: CMakeFiles/dump_json.dir/main.cpp.o
dump_json: CMakeFiles/dump_json.dir/build.make
dump_json: CMakeFiles/dump_json.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/arpanghosal/Software_tutorials/gitprojects/CLion-cpp-projects/dump_json/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable dump_json"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/dump_json.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/dump_json.dir/build: dump_json

.PHONY : CMakeFiles/dump_json.dir/build

CMakeFiles/dump_json.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/dump_json.dir/cmake_clean.cmake
.PHONY : CMakeFiles/dump_json.dir/clean

CMakeFiles/dump_json.dir/depend:
	cd /Users/arpanghosal/Software_tutorials/gitprojects/CLion-cpp-projects/dump_json/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/arpanghosal/Software_tutorials/gitprojects/CLion-cpp-projects/dump_json /Users/arpanghosal/Software_tutorials/gitprojects/CLion-cpp-projects/dump_json /Users/arpanghosal/Software_tutorials/gitprojects/CLion-cpp-projects/dump_json/cmake-build-debug /Users/arpanghosal/Software_tutorials/gitprojects/CLion-cpp-projects/dump_json/cmake-build-debug /Users/arpanghosal/Software_tutorials/gitprojects/CLion-cpp-projects/dump_json/cmake-build-debug/CMakeFiles/dump_json.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/dump_json.dir/depend
