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
CMAKE_COMMAND = /snap/clion/138/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /snap/clion/138/bin/cmake/linux/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/dennis/CLionProjects/Project-3

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/dennis/CLionProjects/Project-3/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/Project_3.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Project_3.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Project_3.dir/flags.make

CMakeFiles/Project_3.dir/main.cpp.o: CMakeFiles/Project_3.dir/flags.make
CMakeFiles/Project_3.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/dennis/CLionProjects/Project-3/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Project_3.dir/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Project_3.dir/main.cpp.o -c /home/dennis/CLionProjects/Project-3/main.cpp

CMakeFiles/Project_3.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Project_3.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/dennis/CLionProjects/Project-3/main.cpp > CMakeFiles/Project_3.dir/main.cpp.i

CMakeFiles/Project_3.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Project_3.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/dennis/CLionProjects/Project-3/main.cpp -o CMakeFiles/Project_3.dir/main.cpp.s

CMakeFiles/Project_3.dir/Job.cpp.o: CMakeFiles/Project_3.dir/flags.make
CMakeFiles/Project_3.dir/Job.cpp.o: ../Job.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/dennis/CLionProjects/Project-3/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/Project_3.dir/Job.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Project_3.dir/Job.cpp.o -c /home/dennis/CLionProjects/Project-3/Job.cpp

CMakeFiles/Project_3.dir/Job.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Project_3.dir/Job.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/dennis/CLionProjects/Project-3/Job.cpp > CMakeFiles/Project_3.dir/Job.cpp.i

CMakeFiles/Project_3.dir/Job.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Project_3.dir/Job.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/dennis/CLionProjects/Project-3/Job.cpp -o CMakeFiles/Project_3.dir/Job.cpp.s

CMakeFiles/Project_3.dir/Queue.cpp.o: CMakeFiles/Project_3.dir/flags.make
CMakeFiles/Project_3.dir/Queue.cpp.o: ../Queue.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/dennis/CLionProjects/Project-3/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/Project_3.dir/Queue.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Project_3.dir/Queue.cpp.o -c /home/dennis/CLionProjects/Project-3/Queue.cpp

CMakeFiles/Project_3.dir/Queue.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Project_3.dir/Queue.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/dennis/CLionProjects/Project-3/Queue.cpp > CMakeFiles/Project_3.dir/Queue.cpp.i

CMakeFiles/Project_3.dir/Queue.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Project_3.dir/Queue.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/dennis/CLionProjects/Project-3/Queue.cpp -o CMakeFiles/Project_3.dir/Queue.cpp.s

# Object files for target Project_3
Project_3_OBJECTS = \
"CMakeFiles/Project_3.dir/main.cpp.o" \
"CMakeFiles/Project_3.dir/Job.cpp.o" \
"CMakeFiles/Project_3.dir/Queue.cpp.o"

# External object files for target Project_3
Project_3_EXTERNAL_OBJECTS =

Project_3: CMakeFiles/Project_3.dir/main.cpp.o
Project_3: CMakeFiles/Project_3.dir/Job.cpp.o
Project_3: CMakeFiles/Project_3.dir/Queue.cpp.o
Project_3: CMakeFiles/Project_3.dir/build.make
Project_3: CMakeFiles/Project_3.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/dennis/CLionProjects/Project-3/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX executable Project_3"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Project_3.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Project_3.dir/build: Project_3

.PHONY : CMakeFiles/Project_3.dir/build

CMakeFiles/Project_3.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Project_3.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Project_3.dir/clean

CMakeFiles/Project_3.dir/depend:
	cd /home/dennis/CLionProjects/Project-3/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/dennis/CLionProjects/Project-3 /home/dennis/CLionProjects/Project-3 /home/dennis/CLionProjects/Project-3/cmake-build-debug /home/dennis/CLionProjects/Project-3/cmake-build-debug /home/dennis/CLionProjects/Project-3/cmake-build-debug/CMakeFiles/Project_3.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Project_3.dir/depend

