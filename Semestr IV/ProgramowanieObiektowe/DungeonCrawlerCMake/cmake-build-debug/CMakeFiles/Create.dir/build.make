# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.27

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
CMAKE_COMMAND = /app/extra/clion/bin/cmake/linux/x64/bin/cmake

# The command to remove a file.
RM = /app/extra/clion/bin/cmake/linux/x64/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "/home/mrdeun/Workspace/Github/studia/Semestr IV/ProgramowanieObiektowe/DungeonCrawlerCMake"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/home/mrdeun/Workspace/Github/studia/Semestr IV/ProgramowanieObiektowe/DungeonCrawlerCMake/cmake-build-debug"

# Include any dependencies generated for this target.
include CMakeFiles/Create.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/Create.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/Create.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Create.dir/flags.make

CMakeFiles/Create.dir/src/create.cpp.o: CMakeFiles/Create.dir/flags.make
CMakeFiles/Create.dir/src/create.cpp.o: /home/mrdeun/Workspace/Github/studia/Semestr\ IV/ProgramowanieObiektowe/DungeonCrawlerCMake/src/create.cpp
CMakeFiles/Create.dir/src/create.cpp.o: CMakeFiles/Create.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir="/home/mrdeun/Workspace/Github/studia/Semestr IV/ProgramowanieObiektowe/DungeonCrawlerCMake/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Create.dir/src/create.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/Create.dir/src/create.cpp.o -MF CMakeFiles/Create.dir/src/create.cpp.o.d -o CMakeFiles/Create.dir/src/create.cpp.o -c "/home/mrdeun/Workspace/Github/studia/Semestr IV/ProgramowanieObiektowe/DungeonCrawlerCMake/src/create.cpp"

CMakeFiles/Create.dir/src/create.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/Create.dir/src/create.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/home/mrdeun/Workspace/Github/studia/Semestr IV/ProgramowanieObiektowe/DungeonCrawlerCMake/src/create.cpp" > CMakeFiles/Create.dir/src/create.cpp.i

CMakeFiles/Create.dir/src/create.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/Create.dir/src/create.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/home/mrdeun/Workspace/Github/studia/Semestr IV/ProgramowanieObiektowe/DungeonCrawlerCMake/src/create.cpp" -o CMakeFiles/Create.dir/src/create.cpp.s

# Object files for target Create
Create_OBJECTS = \
"CMakeFiles/Create.dir/src/create.cpp.o"

# External object files for target Create
Create_EXTERNAL_OBJECTS =

Create: CMakeFiles/Create.dir/src/create.cpp.o
Create: CMakeFiles/Create.dir/build.make
Create: CMakeFiles/Create.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir="/home/mrdeun/Workspace/Github/studia/Semestr IV/ProgramowanieObiektowe/DungeonCrawlerCMake/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable Create"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Create.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Create.dir/build: Create
.PHONY : CMakeFiles/Create.dir/build

CMakeFiles/Create.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Create.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Create.dir/clean

CMakeFiles/Create.dir/depend:
	cd "/home/mrdeun/Workspace/Github/studia/Semestr IV/ProgramowanieObiektowe/DungeonCrawlerCMake/cmake-build-debug" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/home/mrdeun/Workspace/Github/studia/Semestr IV/ProgramowanieObiektowe/DungeonCrawlerCMake" "/home/mrdeun/Workspace/Github/studia/Semestr IV/ProgramowanieObiektowe/DungeonCrawlerCMake" "/home/mrdeun/Workspace/Github/studia/Semestr IV/ProgramowanieObiektowe/DungeonCrawlerCMake/cmake-build-debug" "/home/mrdeun/Workspace/Github/studia/Semestr IV/ProgramowanieObiektowe/DungeonCrawlerCMake/cmake-build-debug" "/home/mrdeun/Workspace/Github/studia/Semestr IV/ProgramowanieObiektowe/DungeonCrawlerCMake/cmake-build-debug/CMakeFiles/Create.dir/DependInfo.cmake" "--color=$(COLOR)"
.PHONY : CMakeFiles/Create.dir/depend

