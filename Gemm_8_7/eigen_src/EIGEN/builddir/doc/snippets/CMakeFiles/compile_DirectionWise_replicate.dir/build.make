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
include doc/snippets/CMakeFiles/compile_DirectionWise_replicate.dir/depend.make

# Include the progress variables for this target.
include doc/snippets/CMakeFiles/compile_DirectionWise_replicate.dir/progress.make

# Include the compile flags for this target's objects.
include doc/snippets/CMakeFiles/compile_DirectionWise_replicate.dir/flags.make

doc/snippets/CMakeFiles/compile_DirectionWise_replicate.dir/compile_DirectionWise_replicate.cpp.o: doc/snippets/CMakeFiles/compile_DirectionWise_replicate.dir/flags.make
doc/snippets/CMakeFiles/compile_DirectionWise_replicate.dir/compile_DirectionWise_replicate.cpp.o: doc/snippets/compile_DirectionWise_replicate.cpp
doc/snippets/CMakeFiles/compile_DirectionWise_replicate.dir/compile_DirectionWise_replicate.cpp.o: ../doc/snippets/DirectionWise_replicate.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/benjamin/my_libs/EIGEN/builddir/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object doc/snippets/CMakeFiles/compile_DirectionWise_replicate.dir/compile_DirectionWise_replicate.cpp.o"
	cd /home/benjamin/my_libs/EIGEN/builddir/doc/snippets && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/compile_DirectionWise_replicate.dir/compile_DirectionWise_replicate.cpp.o -c /home/benjamin/my_libs/EIGEN/builddir/doc/snippets/compile_DirectionWise_replicate.cpp

doc/snippets/CMakeFiles/compile_DirectionWise_replicate.dir/compile_DirectionWise_replicate.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/compile_DirectionWise_replicate.dir/compile_DirectionWise_replicate.cpp.i"
	cd /home/benjamin/my_libs/EIGEN/builddir/doc/snippets && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/benjamin/my_libs/EIGEN/builddir/doc/snippets/compile_DirectionWise_replicate.cpp > CMakeFiles/compile_DirectionWise_replicate.dir/compile_DirectionWise_replicate.cpp.i

doc/snippets/CMakeFiles/compile_DirectionWise_replicate.dir/compile_DirectionWise_replicate.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/compile_DirectionWise_replicate.dir/compile_DirectionWise_replicate.cpp.s"
	cd /home/benjamin/my_libs/EIGEN/builddir/doc/snippets && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/benjamin/my_libs/EIGEN/builddir/doc/snippets/compile_DirectionWise_replicate.cpp -o CMakeFiles/compile_DirectionWise_replicate.dir/compile_DirectionWise_replicate.cpp.s

doc/snippets/CMakeFiles/compile_DirectionWise_replicate.dir/compile_DirectionWise_replicate.cpp.o.requires:
.PHONY : doc/snippets/CMakeFiles/compile_DirectionWise_replicate.dir/compile_DirectionWise_replicate.cpp.o.requires

doc/snippets/CMakeFiles/compile_DirectionWise_replicate.dir/compile_DirectionWise_replicate.cpp.o.provides: doc/snippets/CMakeFiles/compile_DirectionWise_replicate.dir/compile_DirectionWise_replicate.cpp.o.requires
	$(MAKE) -f doc/snippets/CMakeFiles/compile_DirectionWise_replicate.dir/build.make doc/snippets/CMakeFiles/compile_DirectionWise_replicate.dir/compile_DirectionWise_replicate.cpp.o.provides.build
.PHONY : doc/snippets/CMakeFiles/compile_DirectionWise_replicate.dir/compile_DirectionWise_replicate.cpp.o.provides

doc/snippets/CMakeFiles/compile_DirectionWise_replicate.dir/compile_DirectionWise_replicate.cpp.o.provides.build: doc/snippets/CMakeFiles/compile_DirectionWise_replicate.dir/compile_DirectionWise_replicate.cpp.o

# Object files for target compile_DirectionWise_replicate
compile_DirectionWise_replicate_OBJECTS = \
"CMakeFiles/compile_DirectionWise_replicate.dir/compile_DirectionWise_replicate.cpp.o"

# External object files for target compile_DirectionWise_replicate
compile_DirectionWise_replicate_EXTERNAL_OBJECTS =

doc/snippets/compile_DirectionWise_replicate: doc/snippets/CMakeFiles/compile_DirectionWise_replicate.dir/compile_DirectionWise_replicate.cpp.o
doc/snippets/compile_DirectionWise_replicate: doc/snippets/CMakeFiles/compile_DirectionWise_replicate.dir/build.make
doc/snippets/compile_DirectionWise_replicate: doc/snippets/CMakeFiles/compile_DirectionWise_replicate.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable compile_DirectionWise_replicate"
	cd /home/benjamin/my_libs/EIGEN/builddir/doc/snippets && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/compile_DirectionWise_replicate.dir/link.txt --verbose=$(VERBOSE)
	cd /home/benjamin/my_libs/EIGEN/builddir/doc/snippets && ./compile_DirectionWise_replicate >/home/benjamin/my_libs/EIGEN/builddir/doc/snippets/DirectionWise_replicate.out

# Rule to build all files generated by this target.
doc/snippets/CMakeFiles/compile_DirectionWise_replicate.dir/build: doc/snippets/compile_DirectionWise_replicate
.PHONY : doc/snippets/CMakeFiles/compile_DirectionWise_replicate.dir/build

doc/snippets/CMakeFiles/compile_DirectionWise_replicate.dir/requires: doc/snippets/CMakeFiles/compile_DirectionWise_replicate.dir/compile_DirectionWise_replicate.cpp.o.requires
.PHONY : doc/snippets/CMakeFiles/compile_DirectionWise_replicate.dir/requires

doc/snippets/CMakeFiles/compile_DirectionWise_replicate.dir/clean:
	cd /home/benjamin/my_libs/EIGEN/builddir/doc/snippets && $(CMAKE_COMMAND) -P CMakeFiles/compile_DirectionWise_replicate.dir/cmake_clean.cmake
.PHONY : doc/snippets/CMakeFiles/compile_DirectionWise_replicate.dir/clean

doc/snippets/CMakeFiles/compile_DirectionWise_replicate.dir/depend:
	cd /home/benjamin/my_libs/EIGEN/builddir && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/benjamin/my_libs/EIGEN /home/benjamin/my_libs/EIGEN/doc/snippets /home/benjamin/my_libs/EIGEN/builddir /home/benjamin/my_libs/EIGEN/builddir/doc/snippets /home/benjamin/my_libs/EIGEN/builddir/doc/snippets/CMakeFiles/compile_DirectionWise_replicate.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : doc/snippets/CMakeFiles/compile_DirectionWise_replicate.dir/depend
