# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.25

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
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
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/xadel/Project/COUR/TP/AS/turtle

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/xadel/Project/COUR/TP/AS/turtle/build

# Include any dependencies generated for this target.
include CMakeFiles/turtle-viewer.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/turtle-viewer.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/turtle-viewer.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/turtle-viewer.dir/flags.make

CMakeFiles/turtle-viewer.dir/turtle-viewer.cc.o: CMakeFiles/turtle-viewer.dir/flags.make
CMakeFiles/turtle-viewer.dir/turtle-viewer.cc.o: /home/xadel/Project/COUR/TP/AS/turtle/turtle-viewer.cc
CMakeFiles/turtle-viewer.dir/turtle-viewer.cc.o: CMakeFiles/turtle-viewer.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/xadel/Project/COUR/TP/AS/turtle/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/turtle-viewer.dir/turtle-viewer.cc.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/turtle-viewer.dir/turtle-viewer.cc.o -MF CMakeFiles/turtle-viewer.dir/turtle-viewer.cc.o.d -o CMakeFiles/turtle-viewer.dir/turtle-viewer.cc.o -c /home/xadel/Project/COUR/TP/AS/turtle/turtle-viewer.cc

CMakeFiles/turtle-viewer.dir/turtle-viewer.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/turtle-viewer.dir/turtle-viewer.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/xadel/Project/COUR/TP/AS/turtle/turtle-viewer.cc > CMakeFiles/turtle-viewer.dir/turtle-viewer.cc.i

CMakeFiles/turtle-viewer.dir/turtle-viewer.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/turtle-viewer.dir/turtle-viewer.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/xadel/Project/COUR/TP/AS/turtle/turtle-viewer.cc -o CMakeFiles/turtle-viewer.dir/turtle-viewer.cc.s

# Object files for target turtle-viewer
turtle__viewer_OBJECTS = \
"CMakeFiles/turtle-viewer.dir/turtle-viewer.cc.o"

# External object files for target turtle-viewer
turtle__viewer_EXTERNAL_OBJECTS =

turtle-viewer: CMakeFiles/turtle-viewer.dir/turtle-viewer.cc.o
turtle-viewer: CMakeFiles/turtle-viewer.dir/build.make
turtle-viewer: /usr/local/lib/libgf0.so.1.1.0
turtle-viewer: /usr/local/lib/libgfnet0.so.1.1.0
turtle-viewer: /usr/local/lib/libgfcore0.so.1.1.0
turtle-viewer: /usr/lib/libz.so
turtle-viewer: CMakeFiles/turtle-viewer.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/xadel/Project/COUR/TP/AS/turtle/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable turtle-viewer"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/turtle-viewer.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/turtle-viewer.dir/build: turtle-viewer
.PHONY : CMakeFiles/turtle-viewer.dir/build

CMakeFiles/turtle-viewer.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/turtle-viewer.dir/cmake_clean.cmake
.PHONY : CMakeFiles/turtle-viewer.dir/clean

CMakeFiles/turtle-viewer.dir/depend:
	cd /home/xadel/Project/COUR/TP/AS/turtle/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/xadel/Project/COUR/TP/AS/turtle /home/xadel/Project/COUR/TP/AS/turtle /home/xadel/Project/COUR/TP/AS/turtle/build /home/xadel/Project/COUR/TP/AS/turtle/build /home/xadel/Project/COUR/TP/AS/turtle/build/CMakeFiles/turtle-viewer.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/turtle-viewer.dir/depend
