# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.31

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
CMAKE_SOURCE_DIR = C:\Users\Windows\Desktop\fac\l2\c++\projetl2_sfml

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\Windows\Desktop\fac\l2\c++\projetl2_sfml\build

# Utility rule file for Continuous.

# Include any custom commands dependencies for this target.
include CMakeFiles/Continuous.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/Continuous.dir/progress.make

CMakeFiles/Continuous:
	"C:\Program Files\CMake\bin\ctest.exe" -D Continuous

CMakeFiles/Continuous.dir/codegen:
.PHONY : CMakeFiles/Continuous.dir/codegen

Continuous: CMakeFiles/Continuous
Continuous: CMakeFiles/Continuous.dir/build.make
.PHONY : Continuous

# Rule to build all files generated by this target.
CMakeFiles/Continuous.dir/build: Continuous
.PHONY : CMakeFiles/Continuous.dir/build

CMakeFiles/Continuous.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\Continuous.dir\cmake_clean.cmake
.PHONY : CMakeFiles/Continuous.dir/clean

CMakeFiles/Continuous.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\Windows\Desktop\fac\l2\c++\projetl2_sfml C:\Users\Windows\Desktop\fac\l2\c++\projetl2_sfml C:\Users\Windows\Desktop\fac\l2\c++\projetl2_sfml\build C:\Users\Windows\Desktop\fac\l2\c++\projetl2_sfml\build C:\Users\Windows\Desktop\fac\l2\c++\projetl2_sfml\build\CMakeFiles\Continuous.dir\DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/Continuous.dir/depend

