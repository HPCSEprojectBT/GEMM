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
include unsupported/doc/examples/CMakeFiles/example_MatrixPower.dir/depend.make

# Include the progress variables for this target.
include unsupported/doc/examples/CMakeFiles/example_MatrixPower.dir/progress.make

# Include the compile flags for this target's objects.
include unsupported/doc/examples/CMakeFiles/example_MatrixPower.dir/flags.make

unsupported/doc/examples/CMakeFiles/example_MatrixPower.dir/MatrixPower.cpp.o: unsupported/doc/examples/CMakeFiles/example_MatrixPower.dir/flags.make
unsupported/doc/examples/CMakeFiles/example_MatrixPower.dir/MatrixPower.cpp.o: ../unsupported/doc/examples/MatrixPower.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/benjamin/my_libs/EIGEN/builddir/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object unsupported/doc/examples/CMakeFiles/example_MatrixPower.dir/MatrixPower.cpp.o"
	cd /home/benjamin/my_libs/EIGEN/builddir/unsupported/doc/examples && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/example_MatrixPower.dir/MatrixPower.cpp.o -c /home/benjamin/my_libs/EIGEN/unsupported/doc/examples/MatrixPower.cpp

unsupported/doc/examples/CMakeFiles/example_MatrixPower.dir/MatrixPower.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/example_MatrixPower.dir/MatrixPower.cpp.i"
	cd /home/benjamin/my_libs/EIGEN/builddir/unsupported/doc/examples && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/benjamin/my_libs/EIGEN/unsupported/doc/examples/MatrixPower.cpp > CMakeFiles/example_MatrixPower.dir/MatrixPower.cpp.i

unsupported/doc/examples/CMakeFiles/example_MatrixPower.dir/MatrixPower.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/example_MatrixPower.dir/MatrixPower.cpp.s"
	cd /home/benjamin/my_libs/EIGEN/builddir/unsupported/doc/examples && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/benjamin/my_libs/EIGEN/unsupported/doc/examples/MatrixPower.cpp -o CMakeFiles/example_MatrixPower.dir/MatrixPower.cpp.s

unsupported/doc/examples/CMakeFiles/example_MatrixPower.dir/MatrixPower.cpp.o.requires:
.PHONY : unsupported/doc/examples/CMakeFiles/example_MatrixPower.dir/MatrixPower.cpp.o.requires

unsupported/doc/examples/CMakeFiles/example_MatrixPower.dir/MatrixPower.cpp.o.provides: unsupported/doc/examples/CMakeFiles/example_MatrixPower.dir/MatrixPower.cpp.o.requires
	$(MAKE) -f unsupported/doc/examples/CMakeFiles/example_MatrixPower.dir/build.make unsupported/doc/examples/CMakeFiles/example_MatrixPower.dir/MatrixPower.cpp.o.provides.build
.PHONY : unsupported/doc/examples/CMakeFiles/example_MatrixPower.dir/MatrixPower.cpp.o.provides

unsupported/doc/examples/CMakeFiles/example_MatrixPower.dir/MatrixPower.cpp.o.provides.build: unsupported/doc/examples/CMakeFiles/example_MatrixPower.dir/MatrixPower.cpp.o

# Object files for target example_MatrixPower
example_MatrixPower_OBJECTS = \
"CMakeFiles/example_MatrixPower.dir/MatrixPower.cpp.o"

# External object files for target example_MatrixPower
example_MatrixPower_EXTERNAL_OBJECTS =

unsupported/doc/examples/example_MatrixPower: unsupported/doc/examples/CMakeFiles/example_MatrixPower.dir/MatrixPower.cpp.o
unsupported/doc/examples/example_MatrixPower: unsupported/doc/examples/CMakeFiles/example_MatrixPower.dir/build.make
unsupported/doc/examples/example_MatrixPower: unsupported/doc/examples/CMakeFiles/example_MatrixPower.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable example_MatrixPower"
	cd /home/benjamin/my_libs/EIGEN/builddir/unsupported/doc/examples && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/example_MatrixPower.dir/link.txt --verbose=$(VERBOSE)
	cd /home/benjamin/my_libs/EIGEN/builddir/unsupported/doc/examples && ./example_MatrixPower >/home/benjamin/my_libs/EIGEN/builddir/unsupported/doc/examples/MatrixPower.out

# Rule to build all files generated by this target.
unsupported/doc/examples/CMakeFiles/example_MatrixPower.dir/build: unsupported/doc/examples/example_MatrixPower
.PHONY : unsupported/doc/examples/CMakeFiles/example_MatrixPower.dir/build

unsupported/doc/examples/CMakeFiles/example_MatrixPower.dir/requires: unsupported/doc/examples/CMakeFiles/example_MatrixPower.dir/MatrixPower.cpp.o.requires
.PHONY : unsupported/doc/examples/CMakeFiles/example_MatrixPower.dir/requires

unsupported/doc/examples/CMakeFiles/example_MatrixPower.dir/clean:
	cd /home/benjamin/my_libs/EIGEN/builddir/unsupported/doc/examples && $(CMAKE_COMMAND) -P CMakeFiles/example_MatrixPower.dir/cmake_clean.cmake
.PHONY : unsupported/doc/examples/CMakeFiles/example_MatrixPower.dir/clean

unsupported/doc/examples/CMakeFiles/example_MatrixPower.dir/depend:
	cd /home/benjamin/my_libs/EIGEN/builddir && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/benjamin/my_libs/EIGEN /home/benjamin/my_libs/EIGEN/unsupported/doc/examples /home/benjamin/my_libs/EIGEN/builddir /home/benjamin/my_libs/EIGEN/builddir/unsupported/doc/examples /home/benjamin/my_libs/EIGEN/builddir/unsupported/doc/examples/CMakeFiles/example_MatrixPower.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : unsupported/doc/examples/CMakeFiles/example_MatrixPower.dir/depend

