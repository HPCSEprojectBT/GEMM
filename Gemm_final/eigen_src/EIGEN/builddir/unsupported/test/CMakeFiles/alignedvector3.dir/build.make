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
include unsupported/test/CMakeFiles/alignedvector3.dir/depend.make

# Include the progress variables for this target.
include unsupported/test/CMakeFiles/alignedvector3.dir/progress.make

# Include the compile flags for this target's objects.
include unsupported/test/CMakeFiles/alignedvector3.dir/flags.make

unsupported/test/CMakeFiles/alignedvector3.dir/alignedvector3.cpp.o: unsupported/test/CMakeFiles/alignedvector3.dir/flags.make
unsupported/test/CMakeFiles/alignedvector3.dir/alignedvector3.cpp.o: ../unsupported/test/alignedvector3.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/benjamin/my_libs/EIGEN/builddir/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object unsupported/test/CMakeFiles/alignedvector3.dir/alignedvector3.cpp.o"
	cd /home/benjamin/my_libs/EIGEN/builddir/unsupported/test && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/alignedvector3.dir/alignedvector3.cpp.o -c /home/benjamin/my_libs/EIGEN/unsupported/test/alignedvector3.cpp

unsupported/test/CMakeFiles/alignedvector3.dir/alignedvector3.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/alignedvector3.dir/alignedvector3.cpp.i"
	cd /home/benjamin/my_libs/EIGEN/builddir/unsupported/test && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/benjamin/my_libs/EIGEN/unsupported/test/alignedvector3.cpp > CMakeFiles/alignedvector3.dir/alignedvector3.cpp.i

unsupported/test/CMakeFiles/alignedvector3.dir/alignedvector3.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/alignedvector3.dir/alignedvector3.cpp.s"
	cd /home/benjamin/my_libs/EIGEN/builddir/unsupported/test && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/benjamin/my_libs/EIGEN/unsupported/test/alignedvector3.cpp -o CMakeFiles/alignedvector3.dir/alignedvector3.cpp.s

unsupported/test/CMakeFiles/alignedvector3.dir/alignedvector3.cpp.o.requires:
.PHONY : unsupported/test/CMakeFiles/alignedvector3.dir/alignedvector3.cpp.o.requires

unsupported/test/CMakeFiles/alignedvector3.dir/alignedvector3.cpp.o.provides: unsupported/test/CMakeFiles/alignedvector3.dir/alignedvector3.cpp.o.requires
	$(MAKE) -f unsupported/test/CMakeFiles/alignedvector3.dir/build.make unsupported/test/CMakeFiles/alignedvector3.dir/alignedvector3.cpp.o.provides.build
.PHONY : unsupported/test/CMakeFiles/alignedvector3.dir/alignedvector3.cpp.o.provides

unsupported/test/CMakeFiles/alignedvector3.dir/alignedvector3.cpp.o.provides.build: unsupported/test/CMakeFiles/alignedvector3.dir/alignedvector3.cpp.o

# Object files for target alignedvector3
alignedvector3_OBJECTS = \
"CMakeFiles/alignedvector3.dir/alignedvector3.cpp.o"

# External object files for target alignedvector3
alignedvector3_EXTERNAL_OBJECTS =

unsupported/test/alignedvector3: unsupported/test/CMakeFiles/alignedvector3.dir/alignedvector3.cpp.o
unsupported/test/alignedvector3: unsupported/test/CMakeFiles/alignedvector3.dir/build.make
unsupported/test/alignedvector3: unsupported/test/CMakeFiles/alignedvector3.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable alignedvector3"
	cd /home/benjamin/my_libs/EIGEN/builddir/unsupported/test && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/alignedvector3.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
unsupported/test/CMakeFiles/alignedvector3.dir/build: unsupported/test/alignedvector3
.PHONY : unsupported/test/CMakeFiles/alignedvector3.dir/build

unsupported/test/CMakeFiles/alignedvector3.dir/requires: unsupported/test/CMakeFiles/alignedvector3.dir/alignedvector3.cpp.o.requires
.PHONY : unsupported/test/CMakeFiles/alignedvector3.dir/requires

unsupported/test/CMakeFiles/alignedvector3.dir/clean:
	cd /home/benjamin/my_libs/EIGEN/builddir/unsupported/test && $(CMAKE_COMMAND) -P CMakeFiles/alignedvector3.dir/cmake_clean.cmake
.PHONY : unsupported/test/CMakeFiles/alignedvector3.dir/clean

unsupported/test/CMakeFiles/alignedvector3.dir/depend:
	cd /home/benjamin/my_libs/EIGEN/builddir && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/benjamin/my_libs/EIGEN /home/benjamin/my_libs/EIGEN/unsupported/test /home/benjamin/my_libs/EIGEN/builddir /home/benjamin/my_libs/EIGEN/builddir/unsupported/test /home/benjamin/my_libs/EIGEN/builddir/unsupported/test/CMakeFiles/alignedvector3.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : unsupported/test/CMakeFiles/alignedvector3.dir/depend

