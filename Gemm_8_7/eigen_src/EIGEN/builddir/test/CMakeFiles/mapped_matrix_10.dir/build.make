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
include test/CMakeFiles/mapped_matrix_10.dir/depend.make

# Include the progress variables for this target.
include test/CMakeFiles/mapped_matrix_10.dir/progress.make

# Include the compile flags for this target's objects.
include test/CMakeFiles/mapped_matrix_10.dir/flags.make

test/CMakeFiles/mapped_matrix_10.dir/mapped_matrix.cpp.o: test/CMakeFiles/mapped_matrix_10.dir/flags.make
test/CMakeFiles/mapped_matrix_10.dir/mapped_matrix.cpp.o: ../test/mapped_matrix.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/benjamin/my_libs/EIGEN/builddir/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object test/CMakeFiles/mapped_matrix_10.dir/mapped_matrix.cpp.o"
	cd /home/benjamin/my_libs/EIGEN/builddir/test && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/mapped_matrix_10.dir/mapped_matrix.cpp.o -c /home/benjamin/my_libs/EIGEN/test/mapped_matrix.cpp

test/CMakeFiles/mapped_matrix_10.dir/mapped_matrix.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/mapped_matrix_10.dir/mapped_matrix.cpp.i"
	cd /home/benjamin/my_libs/EIGEN/builddir/test && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/benjamin/my_libs/EIGEN/test/mapped_matrix.cpp > CMakeFiles/mapped_matrix_10.dir/mapped_matrix.cpp.i

test/CMakeFiles/mapped_matrix_10.dir/mapped_matrix.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/mapped_matrix_10.dir/mapped_matrix.cpp.s"
	cd /home/benjamin/my_libs/EIGEN/builddir/test && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/benjamin/my_libs/EIGEN/test/mapped_matrix.cpp -o CMakeFiles/mapped_matrix_10.dir/mapped_matrix.cpp.s

test/CMakeFiles/mapped_matrix_10.dir/mapped_matrix.cpp.o.requires:
.PHONY : test/CMakeFiles/mapped_matrix_10.dir/mapped_matrix.cpp.o.requires

test/CMakeFiles/mapped_matrix_10.dir/mapped_matrix.cpp.o.provides: test/CMakeFiles/mapped_matrix_10.dir/mapped_matrix.cpp.o.requires
	$(MAKE) -f test/CMakeFiles/mapped_matrix_10.dir/build.make test/CMakeFiles/mapped_matrix_10.dir/mapped_matrix.cpp.o.provides.build
.PHONY : test/CMakeFiles/mapped_matrix_10.dir/mapped_matrix.cpp.o.provides

test/CMakeFiles/mapped_matrix_10.dir/mapped_matrix.cpp.o.provides.build: test/CMakeFiles/mapped_matrix_10.dir/mapped_matrix.cpp.o

# Object files for target mapped_matrix_10
mapped_matrix_10_OBJECTS = \
"CMakeFiles/mapped_matrix_10.dir/mapped_matrix.cpp.o"

# External object files for target mapped_matrix_10
mapped_matrix_10_EXTERNAL_OBJECTS =

test/mapped_matrix_10: test/CMakeFiles/mapped_matrix_10.dir/mapped_matrix.cpp.o
test/mapped_matrix_10: test/CMakeFiles/mapped_matrix_10.dir/build.make
test/mapped_matrix_10: test/CMakeFiles/mapped_matrix_10.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable mapped_matrix_10"
	cd /home/benjamin/my_libs/EIGEN/builddir/test && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/mapped_matrix_10.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
test/CMakeFiles/mapped_matrix_10.dir/build: test/mapped_matrix_10
.PHONY : test/CMakeFiles/mapped_matrix_10.dir/build

test/CMakeFiles/mapped_matrix_10.dir/requires: test/CMakeFiles/mapped_matrix_10.dir/mapped_matrix.cpp.o.requires
.PHONY : test/CMakeFiles/mapped_matrix_10.dir/requires

test/CMakeFiles/mapped_matrix_10.dir/clean:
	cd /home/benjamin/my_libs/EIGEN/builddir/test && $(CMAKE_COMMAND) -P CMakeFiles/mapped_matrix_10.dir/cmake_clean.cmake
.PHONY : test/CMakeFiles/mapped_matrix_10.dir/clean

test/CMakeFiles/mapped_matrix_10.dir/depend:
	cd /home/benjamin/my_libs/EIGEN/builddir && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/benjamin/my_libs/EIGEN /home/benjamin/my_libs/EIGEN/test /home/benjamin/my_libs/EIGEN/builddir /home/benjamin/my_libs/EIGEN/builddir/test /home/benjamin/my_libs/EIGEN/builddir/test/CMakeFiles/mapped_matrix_10.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : test/CMakeFiles/mapped_matrix_10.dir/depend

