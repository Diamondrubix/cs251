# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.9

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
CMAKE_COMMAND = /home/aarato/.local/share/JetBrains/Toolbox/apps/CLion/ch-0/173.4548.31/bin/cmake/bin/cmake

# The command to remove a file.
RM = /home/aarato/.local/share/JetBrains/Toolbox/apps/CLion/ch-0/173.4548.31/bin/cmake/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/aarato/CLionProjects/cs251/gridworld

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/aarato/CLionProjects/cs251/gridworld/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/gridworld.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/gridworld.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/gridworld.dir/flags.make

CMakeFiles/gridworld.dir/main.cpp.o: CMakeFiles/gridworld.dir/flags.make
CMakeFiles/gridworld.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/aarato/CLionProjects/cs251/gridworld/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/gridworld.dir/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/gridworld.dir/main.cpp.o -c /home/aarato/CLionProjects/cs251/gridworld/main.cpp

CMakeFiles/gridworld.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/gridworld.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/aarato/CLionProjects/cs251/gridworld/main.cpp > CMakeFiles/gridworld.dir/main.cpp.i

CMakeFiles/gridworld.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/gridworld.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/aarato/CLionProjects/cs251/gridworld/main.cpp -o CMakeFiles/gridworld.dir/main.cpp.s

CMakeFiles/gridworld.dir/main.cpp.o.requires:

.PHONY : CMakeFiles/gridworld.dir/main.cpp.o.requires

CMakeFiles/gridworld.dir/main.cpp.o.provides: CMakeFiles/gridworld.dir/main.cpp.o.requires
	$(MAKE) -f CMakeFiles/gridworld.dir/build.make CMakeFiles/gridworld.dir/main.cpp.o.provides.build
.PHONY : CMakeFiles/gridworld.dir/main.cpp.o.provides

CMakeFiles/gridworld.dir/main.cpp.o.provides.build: CMakeFiles/gridworld.dir/main.cpp.o


# Object files for target gridworld
gridworld_OBJECTS = \
"CMakeFiles/gridworld.dir/main.cpp.o"

# External object files for target gridworld
gridworld_EXTERNAL_OBJECTS =

gridworld: CMakeFiles/gridworld.dir/main.cpp.o
gridworld: CMakeFiles/gridworld.dir/build.make
gridworld: CMakeFiles/gridworld.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/aarato/CLionProjects/cs251/gridworld/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable gridworld"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/gridworld.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/gridworld.dir/build: gridworld

.PHONY : CMakeFiles/gridworld.dir/build

CMakeFiles/gridworld.dir/requires: CMakeFiles/gridworld.dir/main.cpp.o.requires

.PHONY : CMakeFiles/gridworld.dir/requires

CMakeFiles/gridworld.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/gridworld.dir/cmake_clean.cmake
.PHONY : CMakeFiles/gridworld.dir/clean

CMakeFiles/gridworld.dir/depend:
	cd /home/aarato/CLionProjects/cs251/gridworld/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/aarato/CLionProjects/cs251/gridworld /home/aarato/CLionProjects/cs251/gridworld /home/aarato/CLionProjects/cs251/gridworld/cmake-build-debug /home/aarato/CLionProjects/cs251/gridworld/cmake-build-debug /home/aarato/CLionProjects/cs251/gridworld/cmake-build-debug/CMakeFiles/gridworld.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/gridworld.dir/depend

