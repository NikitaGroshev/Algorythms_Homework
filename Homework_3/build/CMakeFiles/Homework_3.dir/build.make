# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.30

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

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\CMake\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\CMake\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Users\TrapNelkit\Desktop\algorithms\Homework_3

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\TrapNelkit\Desktop\algorithms\Homework_3\build

# Include any dependencies generated for this target.
include CMakeFiles/Homework_3.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/Homework_3.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/Homework_3.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Homework_3.dir/flags.make

CMakeFiles/Homework_3.dir/src/task2.cpp.obj: CMakeFiles/Homework_3.dir/flags.make
CMakeFiles/Homework_3.dir/src/task2.cpp.obj: C:/Users/TrapNelkit/Desktop/algorithms/Homework_3/src/task2.cpp
CMakeFiles/Homework_3.dir/src/task2.cpp.obj: CMakeFiles/Homework_3.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=C:\Users\TrapNelkit\Desktop\algorithms\Homework_3\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Homework_3.dir/src/task2.cpp.obj"
	C:\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/Homework_3.dir/src/task2.cpp.obj -MF CMakeFiles\Homework_3.dir\src\task2.cpp.obj.d -o CMakeFiles\Homework_3.dir\src\task2.cpp.obj -c C:\Users\TrapNelkit\Desktop\algorithms\Homework_3\src\task2.cpp

CMakeFiles/Homework_3.dir/src/task2.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/Homework_3.dir/src/task2.cpp.i"
	C:\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\TrapNelkit\Desktop\algorithms\Homework_3\src\task2.cpp > CMakeFiles\Homework_3.dir\src\task2.cpp.i

CMakeFiles/Homework_3.dir/src/task2.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/Homework_3.dir/src/task2.cpp.s"
	C:\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\TrapNelkit\Desktop\algorithms\Homework_3\src\task2.cpp -o CMakeFiles\Homework_3.dir\src\task2.cpp.s

# Object files for target Homework_3
Homework_3_OBJECTS = \
"CMakeFiles/Homework_3.dir/src/task2.cpp.obj"

# External object files for target Homework_3
Homework_3_EXTERNAL_OBJECTS =

Homework_3.exe: CMakeFiles/Homework_3.dir/src/task2.cpp.obj
Homework_3.exe: CMakeFiles/Homework_3.dir/build.make
Homework_3.exe: CMakeFiles/Homework_3.dir/linkLibs.rsp
Homework_3.exe: CMakeFiles/Homework_3.dir/objects1.rsp
Homework_3.exe: CMakeFiles/Homework_3.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=C:\Users\TrapNelkit\Desktop\algorithms\Homework_3\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable Homework_3.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\Homework_3.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Homework_3.dir/build: Homework_3.exe
.PHONY : CMakeFiles/Homework_3.dir/build

CMakeFiles/Homework_3.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\Homework_3.dir\cmake_clean.cmake
.PHONY : CMakeFiles/Homework_3.dir/clean

CMakeFiles/Homework_3.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\TrapNelkit\Desktop\algorithms\Homework_3 C:\Users\TrapNelkit\Desktop\algorithms\Homework_3 C:\Users\TrapNelkit\Desktop\algorithms\Homework_3\build C:\Users\TrapNelkit\Desktop\algorithms\Homework_3\build C:\Users\TrapNelkit\Desktop\algorithms\Homework_3\build\CMakeFiles\Homework_3.dir\DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/Homework_3.dir/depend

