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
include blas/testing/CMakeFiles/sblat2.dir/depend.make

# Include the progress variables for this target.
include blas/testing/CMakeFiles/sblat2.dir/progress.make

# Include the compile flags for this target's objects.
include blas/testing/CMakeFiles/sblat2.dir/flags.make

blas/testing/CMakeFiles/sblat2.dir/sblat2.f.o: blas/testing/CMakeFiles/sblat2.dir/flags.make
blas/testing/CMakeFiles/sblat2.dir/sblat2.f.o: ../blas/testing/sblat2.f
	$(CMAKE_COMMAND) -E cmake_progress_report /home/benjamin/my_libs/EIGEN/builddir/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building Fortran object blas/testing/CMakeFiles/sblat2.dir/sblat2.f.o"
	cd /home/benjamin/my_libs/EIGEN/builddir/blas/testing && /usr/bin/gfortran  $(Fortran_DEFINES) $(Fortran_FLAGS) -c /home/benjamin/my_libs/EIGEN/blas/testing/sblat2.f -o CMakeFiles/sblat2.dir/sblat2.f.o

blas/testing/CMakeFiles/sblat2.dir/sblat2.f.o.requires:
.PHONY : blas/testing/CMakeFiles/sblat2.dir/sblat2.f.o.requires

blas/testing/CMakeFiles/sblat2.dir/sblat2.f.o.provides: blas/testing/CMakeFiles/sblat2.dir/sblat2.f.o.requires
	$(MAKE) -f blas/testing/CMakeFiles/sblat2.dir/build.make blas/testing/CMakeFiles/sblat2.dir/sblat2.f.o.provides.build
.PHONY : blas/testing/CMakeFiles/sblat2.dir/sblat2.f.o.provides

blas/testing/CMakeFiles/sblat2.dir/sblat2.f.o.provides.build: blas/testing/CMakeFiles/sblat2.dir/sblat2.f.o

# Object files for target sblat2
sblat2_OBJECTS = \
"CMakeFiles/sblat2.dir/sblat2.f.o"

# External object files for target sblat2
sblat2_EXTERNAL_OBJECTS =

blas/testing/sblat2: blas/testing/CMakeFiles/sblat2.dir/sblat2.f.o
blas/testing/sblat2: blas/testing/CMakeFiles/sblat2.dir/build.make
blas/testing/sblat2: blas/libeigen_blas.so
blas/testing/sblat2: blas/testing/CMakeFiles/sblat2.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking Fortran executable sblat2"
	cd /home/benjamin/my_libs/EIGEN/builddir/blas/testing && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/sblat2.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
blas/testing/CMakeFiles/sblat2.dir/build: blas/testing/sblat2
.PHONY : blas/testing/CMakeFiles/sblat2.dir/build

blas/testing/CMakeFiles/sblat2.dir/requires: blas/testing/CMakeFiles/sblat2.dir/sblat2.f.o.requires
.PHONY : blas/testing/CMakeFiles/sblat2.dir/requires

blas/testing/CMakeFiles/sblat2.dir/clean:
	cd /home/benjamin/my_libs/EIGEN/builddir/blas/testing && $(CMAKE_COMMAND) -P CMakeFiles/sblat2.dir/cmake_clean.cmake
.PHONY : blas/testing/CMakeFiles/sblat2.dir/clean

blas/testing/CMakeFiles/sblat2.dir/depend:
	cd /home/benjamin/my_libs/EIGEN/builddir && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/benjamin/my_libs/EIGEN /home/benjamin/my_libs/EIGEN/blas/testing /home/benjamin/my_libs/EIGEN/builddir /home/benjamin/my_libs/EIGEN/builddir/blas/testing /home/benjamin/my_libs/EIGEN/builddir/blas/testing/CMakeFiles/sblat2.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : blas/testing/CMakeFiles/sblat2.dir/depend

