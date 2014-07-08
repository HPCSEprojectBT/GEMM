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
include doc/examples/CMakeFiles/MatrixBase_cwise_const.dir/depend.make

# Include the progress variables for this target.
include doc/examples/CMakeFiles/MatrixBase_cwise_const.dir/progress.make

# Include the compile flags for this target's objects.
include doc/examples/CMakeFiles/MatrixBase_cwise_const.dir/flags.make

doc/examples/CMakeFiles/MatrixBase_cwise_const.dir/MatrixBase_cwise_const.cpp.o: doc/examples/CMakeFiles/MatrixBase_cwise_const.dir/flags.make
doc/examples/CMakeFiles/MatrixBase_cwise_const.dir/MatrixBase_cwise_const.cpp.o: ../doc/examples/MatrixBase_cwise_const.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/benjamin/my_libs/EIGEN/builddir/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object doc/examples/CMakeFiles/MatrixBase_cwise_const.dir/MatrixBase_cwise_const.cpp.o"
	cd /home/benjamin/my_libs/EIGEN/builddir/doc/examples && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/MatrixBase_cwise_const.dir/MatrixBase_cwise_const.cpp.o -c /home/benjamin/my_libs/EIGEN/doc/examples/MatrixBase_cwise_const.cpp

doc/examples/CMakeFiles/MatrixBase_cwise_const.dir/MatrixBase_cwise_const.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/MatrixBase_cwise_const.dir/MatrixBase_cwise_const.cpp.i"
	cd /home/benjamin/my_libs/EIGEN/builddir/doc/examples && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/benjamin/my_libs/EIGEN/doc/examples/MatrixBase_cwise_const.cpp > CMakeFiles/MatrixBase_cwise_const.dir/MatrixBase_cwise_const.cpp.i

doc/examples/CMakeFiles/MatrixBase_cwise_const.dir/MatrixBase_cwise_const.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/MatrixBase_cwise_const.dir/MatrixBase_cwise_const.cpp.s"
	cd /home/benjamin/my_libs/EIGEN/builddir/doc/examples && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/benjamin/my_libs/EIGEN/doc/examples/MatrixBase_cwise_const.cpp -o CMakeFiles/MatrixBase_cwise_const.dir/MatrixBase_cwise_const.cpp.s

doc/examples/CMakeFiles/MatrixBase_cwise_const.dir/MatrixBase_cwise_const.cpp.o.requires:
.PHONY : doc/examples/CMakeFiles/MatrixBase_cwise_const.dir/MatrixBase_cwise_const.cpp.o.requires

doc/examples/CMakeFiles/MatrixBase_cwise_const.dir/MatrixBase_cwise_const.cpp.o.provides: doc/examples/CMakeFiles/MatrixBase_cwise_const.dir/MatrixBase_cwise_const.cpp.o.requires
	$(MAKE) -f doc/examples/CMakeFiles/MatrixBase_cwise_const.dir/build.make doc/examples/CMakeFiles/MatrixBase_cwise_const.dir/MatrixBase_cwise_const.cpp.o.provides.build
.PHONY : doc/examples/CMakeFiles/MatrixBase_cwise_const.dir/MatrixBase_cwise_const.cpp.o.provides

doc/examples/CMakeFiles/MatrixBase_cwise_const.dir/MatrixBase_cwise_const.cpp.o.provides.build: doc/examples/CMakeFiles/MatrixBase_cwise_const.dir/MatrixBase_cwise_const.cpp.o

# Object files for target MatrixBase_cwise_const
MatrixBase_cwise_const_OBJECTS = \
"CMakeFiles/MatrixBase_cwise_const.dir/MatrixBase_cwise_const.cpp.o"

# External object files for target MatrixBase_cwise_const
MatrixBase_cwise_const_EXTERNAL_OBJECTS =

doc/examples/MatrixBase_cwise_const: doc/examples/CMakeFiles/MatrixBase_cwise_const.dir/MatrixBase_cwise_const.cpp.o
doc/examples/MatrixBase_cwise_const: doc/examples/CMakeFiles/MatrixBase_cwise_const.dir/build.make
doc/examples/MatrixBase_cwise_const: doc/examples/CMakeFiles/MatrixBase_cwise_const.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable MatrixBase_cwise_const"
	cd /home/benjamin/my_libs/EIGEN/builddir/doc/examples && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/MatrixBase_cwise_const.dir/link.txt --verbose=$(VERBOSE)
	cd /home/benjamin/my_libs/EIGEN/builddir/doc/examples && ./MatrixBase_cwise_const >/home/benjamin/my_libs/EIGEN/builddir/doc/examples/MatrixBase_cwise_const.out

# Rule to build all files generated by this target.
doc/examples/CMakeFiles/MatrixBase_cwise_const.dir/build: doc/examples/MatrixBase_cwise_const
.PHONY : doc/examples/CMakeFiles/MatrixBase_cwise_const.dir/build

doc/examples/CMakeFiles/MatrixBase_cwise_const.dir/requires: doc/examples/CMakeFiles/MatrixBase_cwise_const.dir/MatrixBase_cwise_const.cpp.o.requires
.PHONY : doc/examples/CMakeFiles/MatrixBase_cwise_const.dir/requires

doc/examples/CMakeFiles/MatrixBase_cwise_const.dir/clean:
	cd /home/benjamin/my_libs/EIGEN/builddir/doc/examples && $(CMAKE_COMMAND) -P CMakeFiles/MatrixBase_cwise_const.dir/cmake_clean.cmake
.PHONY : doc/examples/CMakeFiles/MatrixBase_cwise_const.dir/clean

doc/examples/CMakeFiles/MatrixBase_cwise_const.dir/depend:
	cd /home/benjamin/my_libs/EIGEN/builddir && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/benjamin/my_libs/EIGEN /home/benjamin/my_libs/EIGEN/doc/examples /home/benjamin/my_libs/EIGEN/builddir /home/benjamin/my_libs/EIGEN/builddir/doc/examples /home/benjamin/my_libs/EIGEN/builddir/doc/examples/CMakeFiles/MatrixBase_cwise_const.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : doc/examples/CMakeFiles/MatrixBase_cwise_const.dir/depend

