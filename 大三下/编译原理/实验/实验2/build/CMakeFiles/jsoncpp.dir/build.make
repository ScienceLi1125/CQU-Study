# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.10

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
CMAKE_SOURCE_DIR = /coursegrader

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /coursegrader/build

# Include any dependencies generated for this target.
include CMakeFiles/jsoncpp.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/jsoncpp.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/jsoncpp.dir/flags.make

CMakeFiles/jsoncpp.dir/src/third_party/jsoncpp/jsoncpp.cpp.o: CMakeFiles/jsoncpp.dir/flags.make
CMakeFiles/jsoncpp.dir/src/third_party/jsoncpp/jsoncpp.cpp.o: ../src/third_party/jsoncpp/jsoncpp.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/coursegrader/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/jsoncpp.dir/src/third_party/jsoncpp/jsoncpp.cpp.o"
	/usr/bin/x86_64-linux-gnu-g++-7  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/jsoncpp.dir/src/third_party/jsoncpp/jsoncpp.cpp.o -c /coursegrader/src/third_party/jsoncpp/jsoncpp.cpp

CMakeFiles/jsoncpp.dir/src/third_party/jsoncpp/jsoncpp.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/jsoncpp.dir/src/third_party/jsoncpp/jsoncpp.cpp.i"
	/usr/bin/x86_64-linux-gnu-g++-7 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /coursegrader/src/third_party/jsoncpp/jsoncpp.cpp > CMakeFiles/jsoncpp.dir/src/third_party/jsoncpp/jsoncpp.cpp.i

CMakeFiles/jsoncpp.dir/src/third_party/jsoncpp/jsoncpp.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/jsoncpp.dir/src/third_party/jsoncpp/jsoncpp.cpp.s"
	/usr/bin/x86_64-linux-gnu-g++-7 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /coursegrader/src/third_party/jsoncpp/jsoncpp.cpp -o CMakeFiles/jsoncpp.dir/src/third_party/jsoncpp/jsoncpp.cpp.s

CMakeFiles/jsoncpp.dir/src/third_party/jsoncpp/jsoncpp.cpp.o.requires:

.PHONY : CMakeFiles/jsoncpp.dir/src/third_party/jsoncpp/jsoncpp.cpp.o.requires

CMakeFiles/jsoncpp.dir/src/third_party/jsoncpp/jsoncpp.cpp.o.provides: CMakeFiles/jsoncpp.dir/src/third_party/jsoncpp/jsoncpp.cpp.o.requires
	$(MAKE) -f CMakeFiles/jsoncpp.dir/build.make CMakeFiles/jsoncpp.dir/src/third_party/jsoncpp/jsoncpp.cpp.o.provides.build
.PHONY : CMakeFiles/jsoncpp.dir/src/third_party/jsoncpp/jsoncpp.cpp.o.provides

CMakeFiles/jsoncpp.dir/src/third_party/jsoncpp/jsoncpp.cpp.o.provides.build: CMakeFiles/jsoncpp.dir/src/third_party/jsoncpp/jsoncpp.cpp.o


# Object files for target jsoncpp
jsoncpp_OBJECTS = \
"CMakeFiles/jsoncpp.dir/src/third_party/jsoncpp/jsoncpp.cpp.o"

# External object files for target jsoncpp
jsoncpp_EXTERNAL_OBJECTS =

../bin/libjsoncpp.a: CMakeFiles/jsoncpp.dir/src/third_party/jsoncpp/jsoncpp.cpp.o
../bin/libjsoncpp.a: CMakeFiles/jsoncpp.dir/build.make
../bin/libjsoncpp.a: CMakeFiles/jsoncpp.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/coursegrader/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library ../bin/libjsoncpp.a"
	$(CMAKE_COMMAND) -P CMakeFiles/jsoncpp.dir/cmake_clean_target.cmake
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/jsoncpp.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/jsoncpp.dir/build: ../bin/libjsoncpp.a

.PHONY : CMakeFiles/jsoncpp.dir/build

CMakeFiles/jsoncpp.dir/requires: CMakeFiles/jsoncpp.dir/src/third_party/jsoncpp/jsoncpp.cpp.o.requires

.PHONY : CMakeFiles/jsoncpp.dir/requires

CMakeFiles/jsoncpp.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/jsoncpp.dir/cmake_clean.cmake
.PHONY : CMakeFiles/jsoncpp.dir/clean

CMakeFiles/jsoncpp.dir/depend:
	cd /coursegrader/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /coursegrader /coursegrader /coursegrader/build /coursegrader/build /coursegrader/build/CMakeFiles/jsoncpp.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/jsoncpp.dir/depend

