# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.12

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


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
CMAKE_SOURCE_DIR = /home/laurin/Repos/conrast

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/laurin/Repos/conrast/build/build-conrast-Desktop-Debug

# Include any dependencies generated for this target.
include CMakeFiles/conrast.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/conrast.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/conrast.dir/flags.make

CMakeFiles/conrast.dir/main.cpp.o: CMakeFiles/conrast.dir/flags.make
CMakeFiles/conrast.dir/main.cpp.o: ../../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/laurin/Repos/conrast/build/build-conrast-Desktop-Debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/conrast.dir/main.cpp.o"
	/usr/bin/clang++-7  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/conrast.dir/main.cpp.o -c /home/laurin/Repos/conrast/main.cpp

CMakeFiles/conrast.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/conrast.dir/main.cpp.i"
	/usr/bin/clang++-7 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/laurin/Repos/conrast/main.cpp > CMakeFiles/conrast.dir/main.cpp.i

CMakeFiles/conrast.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/conrast.dir/main.cpp.s"
	/usr/bin/clang++-7 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/laurin/Repos/conrast/main.cpp -o CMakeFiles/conrast.dir/main.cpp.s

CMakeFiles/conrast.dir/Color/Color.cpp.o: CMakeFiles/conrast.dir/flags.make
CMakeFiles/conrast.dir/Color/Color.cpp.o: ../../Color/Color.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/laurin/Repos/conrast/build/build-conrast-Desktop-Debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/conrast.dir/Color/Color.cpp.o"
	/usr/bin/clang++-7  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/conrast.dir/Color/Color.cpp.o -c /home/laurin/Repos/conrast/Color/Color.cpp

CMakeFiles/conrast.dir/Color/Color.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/conrast.dir/Color/Color.cpp.i"
	/usr/bin/clang++-7 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/laurin/Repos/conrast/Color/Color.cpp > CMakeFiles/conrast.dir/Color/Color.cpp.i

CMakeFiles/conrast.dir/Color/Color.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/conrast.dir/Color/Color.cpp.s"
	/usr/bin/clang++-7 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/laurin/Repos/conrast/Color/Color.cpp -o CMakeFiles/conrast.dir/Color/Color.cpp.s

CMakeFiles/conrast.dir/Utils/Vec.cpp.o: CMakeFiles/conrast.dir/flags.make
CMakeFiles/conrast.dir/Utils/Vec.cpp.o: ../../Utils/Vec.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/laurin/Repos/conrast/build/build-conrast-Desktop-Debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/conrast.dir/Utils/Vec.cpp.o"
	/usr/bin/clang++-7  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/conrast.dir/Utils/Vec.cpp.o -c /home/laurin/Repos/conrast/Utils/Vec.cpp

CMakeFiles/conrast.dir/Utils/Vec.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/conrast.dir/Utils/Vec.cpp.i"
	/usr/bin/clang++-7 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/laurin/Repos/conrast/Utils/Vec.cpp > CMakeFiles/conrast.dir/Utils/Vec.cpp.i

CMakeFiles/conrast.dir/Utils/Vec.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/conrast.dir/Utils/Vec.cpp.s"
	/usr/bin/clang++-7 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/laurin/Repos/conrast/Utils/Vec.cpp -o CMakeFiles/conrast.dir/Utils/Vec.cpp.s

CMakeFiles/conrast.dir/Surface/Surface.cpp.o: CMakeFiles/conrast.dir/flags.make
CMakeFiles/conrast.dir/Surface/Surface.cpp.o: ../../Surface/Surface.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/laurin/Repos/conrast/build/build-conrast-Desktop-Debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/conrast.dir/Surface/Surface.cpp.o"
	/usr/bin/clang++-7  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/conrast.dir/Surface/Surface.cpp.o -c /home/laurin/Repos/conrast/Surface/Surface.cpp

CMakeFiles/conrast.dir/Surface/Surface.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/conrast.dir/Surface/Surface.cpp.i"
	/usr/bin/clang++-7 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/laurin/Repos/conrast/Surface/Surface.cpp > CMakeFiles/conrast.dir/Surface/Surface.cpp.i

CMakeFiles/conrast.dir/Surface/Surface.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/conrast.dir/Surface/Surface.cpp.s"
	/usr/bin/clang++-7 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/laurin/Repos/conrast/Surface/Surface.cpp -o CMakeFiles/conrast.dir/Surface/Surface.cpp.s

CMakeFiles/conrast.dir/Surface/ConsoleSurface.cpp.o: CMakeFiles/conrast.dir/flags.make
CMakeFiles/conrast.dir/Surface/ConsoleSurface.cpp.o: ../../Surface/ConsoleSurface.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/laurin/Repos/conrast/build/build-conrast-Desktop-Debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/conrast.dir/Surface/ConsoleSurface.cpp.o"
	/usr/bin/clang++-7  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/conrast.dir/Surface/ConsoleSurface.cpp.o -c /home/laurin/Repos/conrast/Surface/ConsoleSurface.cpp

CMakeFiles/conrast.dir/Surface/ConsoleSurface.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/conrast.dir/Surface/ConsoleSurface.cpp.i"
	/usr/bin/clang++-7 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/laurin/Repos/conrast/Surface/ConsoleSurface.cpp > CMakeFiles/conrast.dir/Surface/ConsoleSurface.cpp.i

CMakeFiles/conrast.dir/Surface/ConsoleSurface.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/conrast.dir/Surface/ConsoleSurface.cpp.s"
	/usr/bin/clang++-7 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/laurin/Repos/conrast/Surface/ConsoleSurface.cpp -o CMakeFiles/conrast.dir/Surface/ConsoleSurface.cpp.s

CMakeFiles/conrast.dir/Rasterizer/Rasterizer.cpp.o: CMakeFiles/conrast.dir/flags.make
CMakeFiles/conrast.dir/Rasterizer/Rasterizer.cpp.o: ../../Rasterizer/Rasterizer.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/laurin/Repos/conrast/build/build-conrast-Desktop-Debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/conrast.dir/Rasterizer/Rasterizer.cpp.o"
	/usr/bin/clang++-7  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/conrast.dir/Rasterizer/Rasterizer.cpp.o -c /home/laurin/Repos/conrast/Rasterizer/Rasterizer.cpp

CMakeFiles/conrast.dir/Rasterizer/Rasterizer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/conrast.dir/Rasterizer/Rasterizer.cpp.i"
	/usr/bin/clang++-7 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/laurin/Repos/conrast/Rasterizer/Rasterizer.cpp > CMakeFiles/conrast.dir/Rasterizer/Rasterizer.cpp.i

CMakeFiles/conrast.dir/Rasterizer/Rasterizer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/conrast.dir/Rasterizer/Rasterizer.cpp.s"
	/usr/bin/clang++-7 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/laurin/Repos/conrast/Rasterizer/Rasterizer.cpp -o CMakeFiles/conrast.dir/Rasterizer/Rasterizer.cpp.s

CMakeFiles/conrast.dir/Mesh/Vertex.cpp.o: CMakeFiles/conrast.dir/flags.make
CMakeFiles/conrast.dir/Mesh/Vertex.cpp.o: ../../Mesh/Vertex.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/laurin/Repos/conrast/build/build-conrast-Desktop-Debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/conrast.dir/Mesh/Vertex.cpp.o"
	/usr/bin/clang++-7  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/conrast.dir/Mesh/Vertex.cpp.o -c /home/laurin/Repos/conrast/Mesh/Vertex.cpp

CMakeFiles/conrast.dir/Mesh/Vertex.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/conrast.dir/Mesh/Vertex.cpp.i"
	/usr/bin/clang++-7 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/laurin/Repos/conrast/Mesh/Vertex.cpp > CMakeFiles/conrast.dir/Mesh/Vertex.cpp.i

CMakeFiles/conrast.dir/Mesh/Vertex.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/conrast.dir/Mesh/Vertex.cpp.s"
	/usr/bin/clang++-7 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/laurin/Repos/conrast/Mesh/Vertex.cpp -o CMakeFiles/conrast.dir/Mesh/Vertex.cpp.s

CMakeFiles/conrast.dir/Mesh/Line.cpp.o: CMakeFiles/conrast.dir/flags.make
CMakeFiles/conrast.dir/Mesh/Line.cpp.o: ../../Mesh/Line.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/laurin/Repos/conrast/build/build-conrast-Desktop-Debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object CMakeFiles/conrast.dir/Mesh/Line.cpp.o"
	/usr/bin/clang++-7  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/conrast.dir/Mesh/Line.cpp.o -c /home/laurin/Repos/conrast/Mesh/Line.cpp

CMakeFiles/conrast.dir/Mesh/Line.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/conrast.dir/Mesh/Line.cpp.i"
	/usr/bin/clang++-7 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/laurin/Repos/conrast/Mesh/Line.cpp > CMakeFiles/conrast.dir/Mesh/Line.cpp.i

CMakeFiles/conrast.dir/Mesh/Line.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/conrast.dir/Mesh/Line.cpp.s"
	/usr/bin/clang++-7 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/laurin/Repos/conrast/Mesh/Line.cpp -o CMakeFiles/conrast.dir/Mesh/Line.cpp.s

CMakeFiles/conrast.dir/Mesh/Triangle.cpp.o: CMakeFiles/conrast.dir/flags.make
CMakeFiles/conrast.dir/Mesh/Triangle.cpp.o: ../../Mesh/Triangle.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/laurin/Repos/conrast/build/build-conrast-Desktop-Debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building CXX object CMakeFiles/conrast.dir/Mesh/Triangle.cpp.o"
	/usr/bin/clang++-7  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/conrast.dir/Mesh/Triangle.cpp.o -c /home/laurin/Repos/conrast/Mesh/Triangle.cpp

CMakeFiles/conrast.dir/Mesh/Triangle.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/conrast.dir/Mesh/Triangle.cpp.i"
	/usr/bin/clang++-7 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/laurin/Repos/conrast/Mesh/Triangle.cpp > CMakeFiles/conrast.dir/Mesh/Triangle.cpp.i

CMakeFiles/conrast.dir/Mesh/Triangle.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/conrast.dir/Mesh/Triangle.cpp.s"
	/usr/bin/clang++-7 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/laurin/Repos/conrast/Mesh/Triangle.cpp -o CMakeFiles/conrast.dir/Mesh/Triangle.cpp.s

# Object files for target conrast
conrast_OBJECTS = \
"CMakeFiles/conrast.dir/main.cpp.o" \
"CMakeFiles/conrast.dir/Color/Color.cpp.o" \
"CMakeFiles/conrast.dir/Utils/Vec.cpp.o" \
"CMakeFiles/conrast.dir/Surface/Surface.cpp.o" \
"CMakeFiles/conrast.dir/Surface/ConsoleSurface.cpp.o" \
"CMakeFiles/conrast.dir/Rasterizer/Rasterizer.cpp.o" \
"CMakeFiles/conrast.dir/Mesh/Vertex.cpp.o" \
"CMakeFiles/conrast.dir/Mesh/Line.cpp.o" \
"CMakeFiles/conrast.dir/Mesh/Triangle.cpp.o"

# External object files for target conrast
conrast_EXTERNAL_OBJECTS =

conrast: CMakeFiles/conrast.dir/main.cpp.o
conrast: CMakeFiles/conrast.dir/Color/Color.cpp.o
conrast: CMakeFiles/conrast.dir/Utils/Vec.cpp.o
conrast: CMakeFiles/conrast.dir/Surface/Surface.cpp.o
conrast: CMakeFiles/conrast.dir/Surface/ConsoleSurface.cpp.o
conrast: CMakeFiles/conrast.dir/Rasterizer/Rasterizer.cpp.o
conrast: CMakeFiles/conrast.dir/Mesh/Vertex.cpp.o
conrast: CMakeFiles/conrast.dir/Mesh/Line.cpp.o
conrast: CMakeFiles/conrast.dir/Mesh/Triangle.cpp.o
conrast: CMakeFiles/conrast.dir/build.make
conrast: CMakeFiles/conrast.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/laurin/Repos/conrast/build/build-conrast-Desktop-Debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Linking CXX executable conrast"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/conrast.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/conrast.dir/build: conrast

.PHONY : CMakeFiles/conrast.dir/build

CMakeFiles/conrast.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/conrast.dir/cmake_clean.cmake
.PHONY : CMakeFiles/conrast.dir/clean

CMakeFiles/conrast.dir/depend:
	cd /home/laurin/Repos/conrast/build/build-conrast-Desktop-Debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/laurin/Repos/conrast /home/laurin/Repos/conrast /home/laurin/Repos/conrast/build/build-conrast-Desktop-Debug /home/laurin/Repos/conrast/build/build-conrast-Desktop-Debug /home/laurin/Repos/conrast/build/build-conrast-Desktop-Debug/CMakeFiles/conrast.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/conrast.dir/depend
