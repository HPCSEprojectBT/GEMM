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
include test/CMakeFiles/product_trsolve_8.dir/depend.make

# Include the progress variables for this target.
include test/CMakeFiles/product_trsolve_8.dir/progress.make

# Include the compile flags for this target's objects.
include test/CMakeFiles/product_trsolve_8.dir/flags.make

test/CMakeFiles/product_trsolve_8.dir/product_trsolve.cpp.o: test/CMakeFiles/product_trsolve_8.dir/flags.make
test/CMakeFiles/product_trsolve_8.dir/product_trsolve.cpp.o: ../test/product_trsolve.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/benjamin/my_libs/EIGEN/builddir/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object test/CMakeFiles/product_trsolve_8.dir/product_trsolve.cpp.o"
	cd /home/benjamin/my_libs/EIGEN/builddir/test && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/product_trsolve_8.dir/product_trsolve.cpp.o -c /home/benjamin/my_libs/EIGEN/test/product_trsolve.cpp

test/CMakeFiles/product_trsolve_8.dir/product_trsolve.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/product_trsolve_8.dir/product_trsolve.cpp.i"
	cd /home/benjamin/my_libs/EIGEN/builddir/test && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/benjamin/my_libs/EIGEN/test/product_trsolve.cpp > CMakeFiles/product_trsolve_8.dir/product_trsolve.cpp.i

test/CMakeFiles/product_trsolve_8.dir/product_trsolve.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/product_trsolve_8.dir/product_trsolve.cpp.s"
	cd /home/benjamin/my_libs/EIGEN/builddir/test && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/benjamin/my_libs/EIGEN/test/product_trsolve.cpp -o CMakeFiles/product_trsolve_8.dir/product_trsolve.cpp.s

test/CMakeFiles/product_trsolve_8.dir/product_trsolve.cpp.o.requires:
.PHONY : test/CMakeFiles/product_trsolve_8.dir/product_trsolve.cpp.o.requires

test/CMakeFiles/product_trsolve_8.dir/product_trsolve.cpp.o.provides: test/CMakeFiles/product_trsolve_8.dir/product_trsolve.cpp.o.requires
	$(MAKE) -f test/CMakeFiles/product_trsolve_8.dir/build.make test/CMakeFiles/product_trsolve_8.dir/product_trsolve.cpp.o.provides.build
.PHONY : test/CMakeFiles/product_trsolve_8.dir/product_trsolve.cpp.o.provides

test/CMakeFiles/product_trsolve_8.dir/product_trsolve.cpp.o.provides.build: test/CMakeFiles/product_trsolve_8.dir/product_trsolve.cpp.o

# Object files for target product_trsolve_8
product_trsolve_8_OBJECTS = \
"CMakeFiles/product_trsolve_8.dir/product_trsolve.cpp.o"

# External object files for target product_trsolve_8
product_trsolve_8_EXTERNAL_OBJECTS =

test/product_trsolve_8: test/CMakeFiles/product_trsolve_8.dir/product_trsolve.cpp.o
test/product_trsolve_8: test/CMakeFiles/product_trsolve_8.dir/build.make
test/product_trsolve_8: test/CMakeFiles/product_trsolve_8.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable product_trsolve_8"
	cd /home/benjamin/my_libs/EIGEN/builddir/test && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/product_trsolve_8.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
test/CMakeFiles/product_trsolve_8.dir/build: test/product_trsolve_8
.PHONY : test/CMakeFiles/product_trsolve_8.dir/build

test/CMakeFiles/product_trsolve_8.dir/requires: test/CMakeFiles/product_trsolve_8.dir/product_trsolve.cpp.o.requires
.PHONY : test/CMakeFiles/product_trsolve_8.dir/requires

test/CMakeFiles/product_trsolve_8.dir/clean:
	cd /home/benjamin/my_libs/EIGEN/builddir/test && $(CMAKE_COMMAND) -P CMakeFiles/product_trsolve_8.dir/cmake_clean.cmake
.PHONY : test/CMakeFiles/product_trsolve_8.dir/clean

test/CMakeFiles/product_trsolve_8.dir/depend:
	cd /home/benjamin/my_libs/EIGEN/builddir && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/benjamin/my_libs/EIGEN /home/benjamin/my_libs/EIGEN/test /home/benjamin/my_libs/EIGEN/builddir /home/benjamin/my_libs/EIGEN/builddir/test /home/benjamin/my_libs/EIGEN/builddir/test/CMakeFiles/product_trsolve_8.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : test/CMakeFiles/product_trsolve_8.dir/depend

