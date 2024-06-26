# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.29

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
CMAKE_SOURCE_DIR = /home/hoswoo/Desktop/Programming/c++/raylib/raylib-pathfinder

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/hoswoo/Desktop/Programming/c++/raylib/raylib-pathfinder/assets

# Include any dependencies generated for this target.
include lib/raygui-cpp/examples/CMakeFiles/ButtonPlacement.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include lib/raygui-cpp/examples/CMakeFiles/ButtonPlacement.dir/compiler_depend.make

# Include the progress variables for this target.
include lib/raygui-cpp/examples/CMakeFiles/ButtonPlacement.dir/progress.make

# Include the compile flags for this target's objects.
include lib/raygui-cpp/examples/CMakeFiles/ButtonPlacement.dir/flags.make

lib/raygui-cpp/examples/CMakeFiles/ButtonPlacement.dir/ButtonPlacement.cpp.o: lib/raygui-cpp/examples/CMakeFiles/ButtonPlacement.dir/flags.make
lib/raygui-cpp/examples/CMakeFiles/ButtonPlacement.dir/ButtonPlacement.cpp.o: /home/hoswoo/Desktop/Programming/c++/raylib/raylib-pathfinder/lib/raygui-cpp/examples/ButtonPlacement.cpp
lib/raygui-cpp/examples/CMakeFiles/ButtonPlacement.dir/ButtonPlacement.cpp.o: lib/raygui-cpp/examples/CMakeFiles/ButtonPlacement.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/hoswoo/Desktop/Programming/c++/raylib/raylib-pathfinder/assets/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object lib/raygui-cpp/examples/CMakeFiles/ButtonPlacement.dir/ButtonPlacement.cpp.o"
	cd /home/hoswoo/Desktop/Programming/c++/raylib/raylib-pathfinder/assets/lib/raygui-cpp/examples && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT lib/raygui-cpp/examples/CMakeFiles/ButtonPlacement.dir/ButtonPlacement.cpp.o -MF CMakeFiles/ButtonPlacement.dir/ButtonPlacement.cpp.o.d -o CMakeFiles/ButtonPlacement.dir/ButtonPlacement.cpp.o -c /home/hoswoo/Desktop/Programming/c++/raylib/raylib-pathfinder/lib/raygui-cpp/examples/ButtonPlacement.cpp

lib/raygui-cpp/examples/CMakeFiles/ButtonPlacement.dir/ButtonPlacement.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/ButtonPlacement.dir/ButtonPlacement.cpp.i"
	cd /home/hoswoo/Desktop/Programming/c++/raylib/raylib-pathfinder/assets/lib/raygui-cpp/examples && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/hoswoo/Desktop/Programming/c++/raylib/raylib-pathfinder/lib/raygui-cpp/examples/ButtonPlacement.cpp > CMakeFiles/ButtonPlacement.dir/ButtonPlacement.cpp.i

lib/raygui-cpp/examples/CMakeFiles/ButtonPlacement.dir/ButtonPlacement.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/ButtonPlacement.dir/ButtonPlacement.cpp.s"
	cd /home/hoswoo/Desktop/Programming/c++/raylib/raylib-pathfinder/assets/lib/raygui-cpp/examples && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/hoswoo/Desktop/Programming/c++/raylib/raylib-pathfinder/lib/raygui-cpp/examples/ButtonPlacement.cpp -o CMakeFiles/ButtonPlacement.dir/ButtonPlacement.cpp.s

# Object files for target ButtonPlacement
ButtonPlacement_OBJECTS = \
"CMakeFiles/ButtonPlacement.dir/ButtonPlacement.cpp.o"

# External object files for target ButtonPlacement
ButtonPlacement_EXTERNAL_OBJECTS =

lib/raygui-cpp/examples/ButtonPlacement: lib/raygui-cpp/examples/CMakeFiles/ButtonPlacement.dir/ButtonPlacement.cpp.o
lib/raygui-cpp/examples/ButtonPlacement: lib/raygui-cpp/examples/CMakeFiles/ButtonPlacement.dir/build.make
lib/raygui-cpp/examples/ButtonPlacement: lib/raygui-cpp/libraygui_cpp.a
lib/raygui-cpp/examples/ButtonPlacement: _deps/raylib-build/raylib/libraylib.a
lib/raygui-cpp/examples/ButtonPlacement: /usr/lib/libOpenGL.so
lib/raygui-cpp/examples/ButtonPlacement: /usr/lib/libGLX.so
lib/raygui-cpp/examples/ButtonPlacement: /usr/lib/libGLU.so
lib/raygui-cpp/examples/ButtonPlacement: _deps/raylib-build/raylib/external/glfw/src/libglfw3.a
lib/raygui-cpp/examples/ButtonPlacement: /usr/lib/librt.a
lib/raygui-cpp/examples/ButtonPlacement: /usr/lib/libm.so
lib/raygui-cpp/examples/ButtonPlacement: lib/raygui-cpp/examples/CMakeFiles/ButtonPlacement.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/home/hoswoo/Desktop/Programming/c++/raylib/raylib-pathfinder/assets/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable ButtonPlacement"
	cd /home/hoswoo/Desktop/Programming/c++/raylib/raylib-pathfinder/assets/lib/raygui-cpp/examples && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/ButtonPlacement.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
lib/raygui-cpp/examples/CMakeFiles/ButtonPlacement.dir/build: lib/raygui-cpp/examples/ButtonPlacement
.PHONY : lib/raygui-cpp/examples/CMakeFiles/ButtonPlacement.dir/build

lib/raygui-cpp/examples/CMakeFiles/ButtonPlacement.dir/clean:
	cd /home/hoswoo/Desktop/Programming/c++/raylib/raylib-pathfinder/assets/lib/raygui-cpp/examples && $(CMAKE_COMMAND) -P CMakeFiles/ButtonPlacement.dir/cmake_clean.cmake
.PHONY : lib/raygui-cpp/examples/CMakeFiles/ButtonPlacement.dir/clean

lib/raygui-cpp/examples/CMakeFiles/ButtonPlacement.dir/depend:
	cd /home/hoswoo/Desktop/Programming/c++/raylib/raylib-pathfinder/assets && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/hoswoo/Desktop/Programming/c++/raylib/raylib-pathfinder /home/hoswoo/Desktop/Programming/c++/raylib/raylib-pathfinder/lib/raygui-cpp/examples /home/hoswoo/Desktop/Programming/c++/raylib/raylib-pathfinder/assets /home/hoswoo/Desktop/Programming/c++/raylib/raylib-pathfinder/assets/lib/raygui-cpp/examples /home/hoswoo/Desktop/Programming/c++/raylib/raylib-pathfinder/assets/lib/raygui-cpp/examples/CMakeFiles/ButtonPlacement.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : lib/raygui-cpp/examples/CMakeFiles/ButtonPlacement.dir/depend

