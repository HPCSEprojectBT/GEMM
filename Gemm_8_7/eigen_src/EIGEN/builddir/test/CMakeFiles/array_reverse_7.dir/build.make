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
include test/CMakeFiles/array_reverse_7.dir/depend.make

# Include the progress variables for this target.
include test/CMakeFiles/array_reverse_7.dir/progress.make

# Include the compile flags for this target's objects.
include test/CMakeFiles/array_reverse_7.dir/flags.make

test/CMakeFiles/array_reverse_7.dir/array_reverse.cpp.o: test/CMakeFiles/array_reverse_7.dir/flags.make
test/CMakeFiles/array_reverse_7.dir/array_reverse.cpp.o: ../test/array_reverse.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/benjamin/my_libs/EIGEN/builddir/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object test/CMakeFiles/array_reverse_7.dir/array_reverse.cpp.o"
	cd /home/benjamin/my_libs/EIGEN/builddir/test && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/array_reverse_7.dir/array_reverse.cpp.o -c /home/benjamin/my_libs/EIGEN/test/array_reverse.cpp

test/CMakeFiles/array_reverse_7.dir/array_reverse.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/array_reverse_7.dir/array_reverse.cpp.i"
	cd /home/benjamin/my_libs/EIGEN/builddir/test && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/benjamin/my_libs/EIGEN/test/array_reverse.cpp > CMakeFiles/array_reverse_7.dir/array_reverse.cpp.i

test/CMakeFiles/array_reverse_7.dir/array_reverse.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/array_reverse_7.dir/array_reverse.cpp.s"
	cd /home/benjamin/my_libs/EIGEN/builddir/test && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/benjamin/my_libs/EIGEN/test/array_reverse.cpp -o CMakeFiles/array_reverse_7.dir/array_reverse.cpp.s

test/CMakeFiles/array_reverse_7.dir/array_reverse.cpp.o.requires:
.PHONY : test/CMakeFiles/array_reverse_7.dir/array_reverse.cpp.o.requires

test/CMakeFiles/array_reverse_7.dir/array_reverse.cpp.o.provides: test/CMakeFiles/array_reverse_7.dir/array_reverse.cpp.o.requires
	$(MAKE) -f test/CMakeFiles/array_reverse_7.dir/build.make test/CMakeFiles/array_reverse_7.dir/array_reverse.cpp.o.provides.build
.PHONY : test/CMakeFiles/array_reverse_7.dir/array_reverse.cpp.o.provides

test/CMakeFiles/array_reverse_7.dir/array_reverse.cpp.o.provides.build: test/CMakeFiles/array_reverse_7.dir/array_reverse.cpp.o

# Object files for target array_reverse_7
array_reverse_7_OBJECTS = \
"CMakeFiles/array_reverse_7.dir/array_reverse.cpp.o"

# External object files for target array_reverse_7
array_reverse_7_EXTERNAL_OBJECTS =

test/array_reverse_7: test/CMakeFiles/array_reverse_7.dir/array_reverse.cpp.o
test/array_reverse_7: test/CMakeFiles/array_reverse_7.dir/build.make
test/array_reverse_7: test/CMakeFiles/array_reverse_7.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable array_reverse_7"
	cd /home/benjamin/my_libs/EIGEN/builddir/test && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/array_reverse_7.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
test/CMakeFiles/array_reverse_7.dir/build: test/array_reverse_7
.PHONY : test/CMakeFiles/array_reverse_7.dir/build

test/CMakeFiles/array_reverse_7.dir/requires: test/CMakeFiles/array_reverse_7.dir/array_reverse.cpp.o.requires
.PHONY : test/CMakeFiles/array_reverse_7.dir/requires

test/CMakeFiles/array_reverse_7.dir/clean:
	cd /home/benjamin/my_libs/EIGEN/builddir/test && $(CMAKE_COMMAND) -P CMakeFiles/array_reverse_7.dir/cmake_clean.cmake
.PHONY : test/CMakeFiles/array_reverse_7.dir/clean

test/CMakeFiles/array_reverse_7.dir/depend:
	cd /home/benjamin/my_libs/EIGEN/builddir && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/benjamin/my_libs/EIGEN /home/benjamin/my_libs/EIGEN/test /home/benjamin/my_libs/EIGEN/builddir /home/benjamin/my_libs/EIGEN/builddir/test /home/benjamin/my_libs/EIGEN/builddir/test/CMakeFiles/array_reverse_7.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : test/CMakeFiles/array_reverse_7.dir/depend

