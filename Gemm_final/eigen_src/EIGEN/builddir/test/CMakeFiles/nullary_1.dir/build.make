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
CMAKE_SOURCE_DIR = /home/benjamin/my_libs/EIGEN

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/benjamin/my_libs/EIGEN/builddir

# Include any dependencies generated for this target.
include test/CMakeFiles/nullary_1.dir/depend.make

# Include the progress variables for this target.
include test/CMakeFiles/nullary_1.dir/progress.make

# Include the compile flags for this target's objects.
include test/CMakeFiles/nullary_1.dir/flags.make

test/CMakeFiles/nullary_1.dir/nullary.cpp.o: test/CMakeFiles/nullary_1.dir/flags.make
test/CMakeFiles/nullary_1.dir/nullary.cpp.o: ../test/nullary.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/benjamin/my_libs/EIGEN/builddir/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object test/CMakeFiles/nullary_1.dir/nullary.cpp.o"
	cd /home/benjamin/my_libs/EIGEN/builddir/test && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/nullary_1.dir/nullary.cpp.o -c /home/benjamin/my_libs/EIGEN/test/nullary.cpp

test/CMakeFiles/nullary_1.dir/nullary.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/nullary_1.dir/nullary.cpp.i"
	cd /home/benjamin/my_libs/EIGEN/builddir/test && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/benjamin/my_libs/EIGEN/test/nullary.cpp > CMakeFiles/nullary_1.dir/nullary.cpp.i

test/CMakeFiles/nullary_1.dir/nullary.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/nullary_1.dir/nullary.cpp.s"
	cd /home/benjamin/my_libs/EIGEN/builddir/test && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/benjamin/my_libs/EIGEN/test/nullary.cpp -o CMakeFiles/nullary_1.dir/nullary.cpp.s

test/CMakeFiles/nullary_1.dir/nullary.cpp.o.requires:
.PHONY : test/CMakeFiles/nullary_1.dir/nullary.cpp.o.requires

test/CMakeFiles/nullary_1.dir/nullary.cpp.o.provides: test/CMakeFiles/nullary_1.dir/nullary.cpp.o.requires
	$(MAKE) -f test/CMakeFiles/nullary_1.dir/build.make test/CMakeFiles/nullary_1.dir/nullary.cpp.o.provides.build
.PHONY : test/CMakeFiles/nullary_1.dir/nullary.cpp.o.provides

test/CMakeFiles/nullary_1.dir/nullary.cpp.o.provides.build: test/CMakeFiles/nullary_1.dir/nullary.cpp.o

# Object files for target nullary_1
nullary_1_OBJECTS = \
"CMakeFiles/nullary_1.dir/nullary.cpp.o"

# External object files for target nullary_1
nullary_1_EXTERNAL_OBJECTS =

test/nullary_1: test/CMakeFiles/nullary_1.dir/nullary.cpp.o
test/nullary_1: test/CMakeFiles/nullary_1.dir/build.make
test/nullary_1: test/CMakeFiles/nullary_1.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable nullary_1"
	cd /home/benjamin/my_libs/EIGEN/builddir/test && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/nullary_1.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
test/CMakeFiles/nullary_1.dir/build: test/nullary_1
.PHONY : test/CMakeFiles/nullary_1.dir/build

test/CMakeFiles/nullary_1.dir/requires: test/CMakeFiles/nullary_1.dir/nullary.cpp.o.requires
.PHONY : test/CMakeFiles/nullary_1.dir/requires

test/CMakeFiles/nullary_1.dir/clean:
	cd /home/benjamin/my_libs/EIGEN/builddir/test && $(CMAKE_COMMAND) -P CMakeFiles/nullary_1.dir/cmake_clean.cmake
.PHONY : test/CMakeFiles/nullary_1.dir/clean

test/CMakeFiles/nullary_1.dir/depend:
	cd /home/benjamin/my_libs/EIGEN/builddir && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/benjamin/my_libs/EIGEN /home/benjamin/my_libs/EIGEN/test /home/benjamin/my_libs/EIGEN/builddir /home/benjamin/my_libs/EIGEN/builddir/test /home/benjamin/my_libs/EIGEN/builddir/test/CMakeFiles/nullary_1.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : test/CMakeFiles/nullary_1.dir/depend

