# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.9

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
CMAKE_COMMAND = /Applications/CLion.app/Contents/bin/cmake/bin/cmake

# The command to remove a file.
RM = /Applications/CLion.app/Contents/bin/cmake/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/michal/CLionProjects/BShip

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/michal/CLionProjects/BShip/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/BShip.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/BShip.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/BShip.dir/flags.make

CMakeFiles/BShip.dir/main.cpp.o: CMakeFiles/BShip.dir/flags.make
CMakeFiles/BShip.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/michal/CLionProjects/BShip/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/BShip.dir/main.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/BShip.dir/main.cpp.o -c /Users/michal/CLionProjects/BShip/main.cpp

CMakeFiles/BShip.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/BShip.dir/main.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/michal/CLionProjects/BShip/main.cpp > CMakeFiles/BShip.dir/main.cpp.i

CMakeFiles/BShip.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/BShip.dir/main.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/michal/CLionProjects/BShip/main.cpp -o CMakeFiles/BShip.dir/main.cpp.s

CMakeFiles/BShip.dir/main.cpp.o.requires:

.PHONY : CMakeFiles/BShip.dir/main.cpp.o.requires

CMakeFiles/BShip.dir/main.cpp.o.provides: CMakeFiles/BShip.dir/main.cpp.o.requires
	$(MAKE) -f CMakeFiles/BShip.dir/build.make CMakeFiles/BShip.dir/main.cpp.o.provides.build
.PHONY : CMakeFiles/BShip.dir/main.cpp.o.provides

CMakeFiles/BShip.dir/main.cpp.o.provides.build: CMakeFiles/BShip.dir/main.cpp.o


CMakeFiles/BShip.dir/BShip/BShipGrid.cpp.o: CMakeFiles/BShip.dir/flags.make
CMakeFiles/BShip.dir/BShip/BShipGrid.cpp.o: ../BShip/BShipGrid.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/michal/CLionProjects/BShip/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/BShip.dir/BShip/BShipGrid.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/BShip.dir/BShip/BShipGrid.cpp.o -c /Users/michal/CLionProjects/BShip/BShip/BShipGrid.cpp

CMakeFiles/BShip.dir/BShip/BShipGrid.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/BShip.dir/BShip/BShipGrid.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/michal/CLionProjects/BShip/BShip/BShipGrid.cpp > CMakeFiles/BShip.dir/BShip/BShipGrid.cpp.i

CMakeFiles/BShip.dir/BShip/BShipGrid.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/BShip.dir/BShip/BShipGrid.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/michal/CLionProjects/BShip/BShip/BShipGrid.cpp -o CMakeFiles/BShip.dir/BShip/BShipGrid.cpp.s

CMakeFiles/BShip.dir/BShip/BShipGrid.cpp.o.requires:

.PHONY : CMakeFiles/BShip.dir/BShip/BShipGrid.cpp.o.requires

CMakeFiles/BShip.dir/BShip/BShipGrid.cpp.o.provides: CMakeFiles/BShip.dir/BShip/BShipGrid.cpp.o.requires
	$(MAKE) -f CMakeFiles/BShip.dir/build.make CMakeFiles/BShip.dir/BShip/BShipGrid.cpp.o.provides.build
.PHONY : CMakeFiles/BShip.dir/BShip/BShipGrid.cpp.o.provides

CMakeFiles/BShip.dir/BShip/BShipGrid.cpp.o.provides.build: CMakeFiles/BShip.dir/BShip/BShipGrid.cpp.o


CMakeFiles/BShip.dir/BShip/BShip.cpp.o: CMakeFiles/BShip.dir/flags.make
CMakeFiles/BShip.dir/BShip/BShip.cpp.o: ../BShip/BShip.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/michal/CLionProjects/BShip/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/BShip.dir/BShip/BShip.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/BShip.dir/BShip/BShip.cpp.o -c /Users/michal/CLionProjects/BShip/BShip/BShip.cpp

CMakeFiles/BShip.dir/BShip/BShip.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/BShip.dir/BShip/BShip.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/michal/CLionProjects/BShip/BShip/BShip.cpp > CMakeFiles/BShip.dir/BShip/BShip.cpp.i

CMakeFiles/BShip.dir/BShip/BShip.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/BShip.dir/BShip/BShip.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/michal/CLionProjects/BShip/BShip/BShip.cpp -o CMakeFiles/BShip.dir/BShip/BShip.cpp.s

CMakeFiles/BShip.dir/BShip/BShip.cpp.o.requires:

.PHONY : CMakeFiles/BShip.dir/BShip/BShip.cpp.o.requires

CMakeFiles/BShip.dir/BShip/BShip.cpp.o.provides: CMakeFiles/BShip.dir/BShip/BShip.cpp.o.requires
	$(MAKE) -f CMakeFiles/BShip.dir/build.make CMakeFiles/BShip.dir/BShip/BShip.cpp.o.provides.build
.PHONY : CMakeFiles/BShip.dir/BShip/BShip.cpp.o.provides

CMakeFiles/BShip.dir/BShip/BShip.cpp.o.provides.build: CMakeFiles/BShip.dir/BShip/BShip.cpp.o


# Object files for target BShip
BShip_OBJECTS = \
"CMakeFiles/BShip.dir/main.cpp.o" \
"CMakeFiles/BShip.dir/BShip/BShipGrid.cpp.o" \
"CMakeFiles/BShip.dir/BShip/BShip.cpp.o"

# External object files for target BShip
BShip_EXTERNAL_OBJECTS =

BShip: CMakeFiles/BShip.dir/main.cpp.o
BShip: CMakeFiles/BShip.dir/BShip/BShipGrid.cpp.o
BShip: CMakeFiles/BShip.dir/BShip/BShip.cpp.o
BShip: CMakeFiles/BShip.dir/build.make
BShip: CMakeFiles/BShip.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/michal/CLionProjects/BShip/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX executable BShip"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/BShip.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/BShip.dir/build: BShip

.PHONY : CMakeFiles/BShip.dir/build

CMakeFiles/BShip.dir/requires: CMakeFiles/BShip.dir/main.cpp.o.requires
CMakeFiles/BShip.dir/requires: CMakeFiles/BShip.dir/BShip/BShipGrid.cpp.o.requires
CMakeFiles/BShip.dir/requires: CMakeFiles/BShip.dir/BShip/BShip.cpp.o.requires

.PHONY : CMakeFiles/BShip.dir/requires

CMakeFiles/BShip.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/BShip.dir/cmake_clean.cmake
.PHONY : CMakeFiles/BShip.dir/clean

CMakeFiles/BShip.dir/depend:
	cd /Users/michal/CLionProjects/BShip/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/michal/CLionProjects/BShip /Users/michal/CLionProjects/BShip /Users/michal/CLionProjects/BShip/cmake-build-debug /Users/michal/CLionProjects/BShip/cmake-build-debug /Users/michal/CLionProjects/BShip/cmake-build-debug/CMakeFiles/BShip.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/BShip.dir/depend

