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
include test/CMakeFiles/unalignedassert.dir/depend.make

# Include the progress variables for this target.
include test/CMakeFiles/unalignedassert.dir/progress.make

# Include the compile flags for this target's objects.
include test/CMakeFiles/unalignedassert.dir/flags.make

test/CMakeFiles/unalignedassert.dir/unalignedassert.cpp.o: test/CMakeFiles/unalignedassert.dir/flags.make
test/CMakeFiles/unalignedassert.dir/unalignedassert.cpp.o: ../test/unalignedassert.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/benjamin/my_libs/EIGEN/builddir/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object test/CMakeFiles/unalignedassert.dir/unalignedassert.cpp.o"
	cd /home/benjamin/my_libs/EIGEN/builddir/test && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/unalignedassert.dir/unalignedassert.cpp.o -c /home/benjamin/my_libs/EIGEN/test/unalignedassert.cpp

test/CMakeFiles/unalignedassert.dir/unalignedassert.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/unalignedassert.dir/unalignedassert.cpp.i"
	cd /home/benjamin/my_libs/EIGEN/builddir/test && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/benjamin/my_libs/EIGEN/test/unalignedassert.cpp > CMakeFiles/unalignedassert.dir/unalignedassert.cpp.i

test/CMakeFiles/unalignedassert.dir/unalignedassert.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/unalignedassert.dir/unalignedassert.cpp.s"
	cd /home/benjamin/my_libs/EIGEN/builddir/test && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/benjamin/my_libs/EIGEN/test/unalignedassert.cpp -o CMakeFiles/unalignedassert.dir/unalignedassert.cpp.s

test/CMakeFiles/unalignedassert.dir/unalignedassert.cpp.o.requires:
.PHONY : test/CMakeFiles/unalignedassert.dir/unalignedassert.cpp.o.requires

test/CMakeFiles/unalignedassert.dir/unalignedassert.cpp.o.provides: test/CMakeFiles/unalignedassert.dir/unalignedassert.cpp.o.requires
	$(MAKE) -f test/CMakeFiles/unalignedassert.dir/build.make test/CMakeFiles/unalignedassert.dir/unalignedassert.cpp.o.provides.build
.PHONY : test/CMakeFiles/unalignedassert.dir/unalignedassert.cpp.o.provides

test/CMakeFiles/unalignedassert.dir/unalignedassert.cpp.o.provides.build: test/CMakeFiles/unalignedassert.dir/unalignedassert.cpp.o

# Object files for target unalignedassert
unalignedassert_OBJECTS = \
"CMakeFiles/unalignedassert.dir/unalignedassert.cpp.o"

# External object files for target unalignedassert
unalignedassert_EXTERNAL_OBJECTS =

test/unalignedassert: test/CMakeFiles/unalignedassert.dir/unalignedassert.cpp.o
test/unalignedassert: test/CMakeFiles/unalignedassert.dir/build.make
test/unalignedassert: test/CMakeFiles/unalignedassert.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable unalignedassert"
	cd /home/benjamin/my_libs/EIGEN/builddir/test && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/unalignedassert.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
test/CMakeFiles/unalignedassert.dir/build: test/unalignedassert
.PHONY : test/CMakeFiles/unalignedassert.dir/build

test/CMakeFiles/unalignedassert.dir/requires: test/CMakeFiles/unalignedassert.dir/unalignedassert.cpp.o.requires
.PHONY : test/CMakeFiles/unalignedassert.dir/requires

test/CMakeFiles/unalignedassert.dir/clean:
	cd /home/benjamin/my_libs/EIGEN/builddir/test && $(CMAKE_COMMAND) -P CMakeFiles/unalignedassert.dir/cmake_clean.cmake
.PHONY : test/CMakeFiles/unalignedassert.dir/clean

test/CMakeFiles/unalignedassert.dir/depend:
	cd /home/benjamin/my_libs/EIGEN/builddir && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/benjamin/my_libs/EIGEN /home/benjamin/my_libs/EIGEN/test /home/benjamin/my_libs/EIGEN/builddir /home/benjamin/my_libs/EIGEN/builddir/test /home/benjamin/my_libs/EIGEN/builddir/test/CMakeFiles/unalignedassert.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : test/CMakeFiles/unalignedassert.dir/depend
