# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

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

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/lqf/EmbeddedSoftWare_practice/lab3

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/lqf/EmbeddedSoftWare_practice/build

# Include any dependencies generated for this target.
include src/CMakeFiles/client12.o.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include src/CMakeFiles/client12.o.dir/compiler_depend.make

# Include the progress variables for this target.
include src/CMakeFiles/client12.o.dir/progress.make

# Include the compile flags for this target's objects.
include src/CMakeFiles/client12.o.dir/flags.make

src/CMakeFiles/client12.o.dir/client12.c.o: src/CMakeFiles/client12.o.dir/flags.make
src/CMakeFiles/client12.o.dir/client12.c.o: /home/lqf/EmbeddedSoftWare_practice/lab3/src/client12.c
src/CMakeFiles/client12.o.dir/client12.c.o: src/CMakeFiles/client12.o.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/lqf/EmbeddedSoftWare_practice/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object src/CMakeFiles/client12.o.dir/client12.c.o"
	cd /home/lqf/EmbeddedSoftWare_practice/build/src && /usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT src/CMakeFiles/client12.o.dir/client12.c.o -MF CMakeFiles/client12.o.dir/client12.c.o.d -o CMakeFiles/client12.o.dir/client12.c.o -c /home/lqf/EmbeddedSoftWare_practice/lab3/src/client12.c

src/CMakeFiles/client12.o.dir/client12.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/client12.o.dir/client12.c.i"
	cd /home/lqf/EmbeddedSoftWare_practice/build/src && /usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/lqf/EmbeddedSoftWare_practice/lab3/src/client12.c > CMakeFiles/client12.o.dir/client12.c.i

src/CMakeFiles/client12.o.dir/client12.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/client12.o.dir/client12.c.s"
	cd /home/lqf/EmbeddedSoftWare_practice/build/src && /usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/lqf/EmbeddedSoftWare_practice/lab3/src/client12.c -o CMakeFiles/client12.o.dir/client12.c.s

# Object files for target client12.o
client12_o_OBJECTS = \
"CMakeFiles/client12.o.dir/client12.c.o"

# External object files for target client12.o
client12_o_EXTERNAL_OBJECTS =

src/client12.o: src/CMakeFiles/client12.o.dir/client12.c.o
src/client12.o: src/CMakeFiles/client12.o.dir/build.make
src/client12.o: src/CMakeFiles/client12.o.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/lqf/EmbeddedSoftWare_practice/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable client12.o"
	cd /home/lqf/EmbeddedSoftWare_practice/build/src && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/client12.o.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/CMakeFiles/client12.o.dir/build: src/client12.o
.PHONY : src/CMakeFiles/client12.o.dir/build

src/CMakeFiles/client12.o.dir/clean:
	cd /home/lqf/EmbeddedSoftWare_practice/build/src && $(CMAKE_COMMAND) -P CMakeFiles/client12.o.dir/cmake_clean.cmake
.PHONY : src/CMakeFiles/client12.o.dir/clean

src/CMakeFiles/client12.o.dir/depend:
	cd /home/lqf/EmbeddedSoftWare_practice/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/lqf/EmbeddedSoftWare_practice/lab3 /home/lqf/EmbeddedSoftWare_practice/lab3/src /home/lqf/EmbeddedSoftWare_practice/build /home/lqf/EmbeddedSoftWare_practice/build/src /home/lqf/EmbeddedSoftWare_practice/build/src/CMakeFiles/client12.o.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/CMakeFiles/client12.o.dir/depend
