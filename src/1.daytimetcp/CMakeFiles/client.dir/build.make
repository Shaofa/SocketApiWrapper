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
CMAKE_SOURCE_DIR = /home/lsf/SocketApiWrapper/src/1.daytimetcp

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/lsf/SocketApiWrapper/src/1.daytimetcp

# Include any dependencies generated for this target.
include CMakeFiles/client.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/client.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/client.dir/flags.make

CMakeFiles/client.dir/client.c.o: CMakeFiles/client.dir/flags.make
CMakeFiles/client.dir/client.c.o: client.c
	$(CMAKE_COMMAND) -E cmake_progress_report /home/lsf/SocketApiWrapper/src/1.daytimetcp/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object CMakeFiles/client.dir/client.c.o"
	/usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/client.dir/client.c.o   -c /home/lsf/SocketApiWrapper/src/1.daytimetcp/client.c

CMakeFiles/client.dir/client.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/client.dir/client.c.i"
	/usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -E /home/lsf/SocketApiWrapper/src/1.daytimetcp/client.c > CMakeFiles/client.dir/client.c.i

CMakeFiles/client.dir/client.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/client.dir/client.c.s"
	/usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -S /home/lsf/SocketApiWrapper/src/1.daytimetcp/client.c -o CMakeFiles/client.dir/client.c.s

CMakeFiles/client.dir/client.c.o.requires:
.PHONY : CMakeFiles/client.dir/client.c.o.requires

CMakeFiles/client.dir/client.c.o.provides: CMakeFiles/client.dir/client.c.o.requires
	$(MAKE) -f CMakeFiles/client.dir/build.make CMakeFiles/client.dir/client.c.o.provides.build
.PHONY : CMakeFiles/client.dir/client.c.o.provides

CMakeFiles/client.dir/client.c.o.provides.build: CMakeFiles/client.dir/client.c.o

CMakeFiles/client.dir/home/lsf/SocketApiWrapper/src/common/sockapi.c.o: CMakeFiles/client.dir/flags.make
CMakeFiles/client.dir/home/lsf/SocketApiWrapper/src/common/sockapi.c.o: /home/lsf/SocketApiWrapper/src/common/sockapi.c
	$(CMAKE_COMMAND) -E cmake_progress_report /home/lsf/SocketApiWrapper/src/1.daytimetcp/CMakeFiles $(CMAKE_PROGRESS_2)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object CMakeFiles/client.dir/home/lsf/SocketApiWrapper/src/common/sockapi.c.o"
	/usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/client.dir/home/lsf/SocketApiWrapper/src/common/sockapi.c.o   -c /home/lsf/SocketApiWrapper/src/common/sockapi.c

CMakeFiles/client.dir/home/lsf/SocketApiWrapper/src/common/sockapi.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/client.dir/home/lsf/SocketApiWrapper/src/common/sockapi.c.i"
	/usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -E /home/lsf/SocketApiWrapper/src/common/sockapi.c > CMakeFiles/client.dir/home/lsf/SocketApiWrapper/src/common/sockapi.c.i

CMakeFiles/client.dir/home/lsf/SocketApiWrapper/src/common/sockapi.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/client.dir/home/lsf/SocketApiWrapper/src/common/sockapi.c.s"
	/usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -S /home/lsf/SocketApiWrapper/src/common/sockapi.c -o CMakeFiles/client.dir/home/lsf/SocketApiWrapper/src/common/sockapi.c.s

CMakeFiles/client.dir/home/lsf/SocketApiWrapper/src/common/sockapi.c.o.requires:
.PHONY : CMakeFiles/client.dir/home/lsf/SocketApiWrapper/src/common/sockapi.c.o.requires

CMakeFiles/client.dir/home/lsf/SocketApiWrapper/src/common/sockapi.c.o.provides: CMakeFiles/client.dir/home/lsf/SocketApiWrapper/src/common/sockapi.c.o.requires
	$(MAKE) -f CMakeFiles/client.dir/build.make CMakeFiles/client.dir/home/lsf/SocketApiWrapper/src/common/sockapi.c.o.provides.build
.PHONY : CMakeFiles/client.dir/home/lsf/SocketApiWrapper/src/common/sockapi.c.o.provides

CMakeFiles/client.dir/home/lsf/SocketApiWrapper/src/common/sockapi.c.o.provides.build: CMakeFiles/client.dir/home/lsf/SocketApiWrapper/src/common/sockapi.c.o

# Object files for target client
client_OBJECTS = \
"CMakeFiles/client.dir/client.c.o" \
"CMakeFiles/client.dir/home/lsf/SocketApiWrapper/src/common/sockapi.c.o"

# External object files for target client
client_EXTERNAL_OBJECTS =

bin/client: CMakeFiles/client.dir/client.c.o
bin/client: CMakeFiles/client.dir/home/lsf/SocketApiWrapper/src/common/sockapi.c.o
bin/client: CMakeFiles/client.dir/build.make
bin/client: CMakeFiles/client.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking C executable bin/client"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/client.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/client.dir/build: bin/client
.PHONY : CMakeFiles/client.dir/build

CMakeFiles/client.dir/requires: CMakeFiles/client.dir/client.c.o.requires
CMakeFiles/client.dir/requires: CMakeFiles/client.dir/home/lsf/SocketApiWrapper/src/common/sockapi.c.o.requires
.PHONY : CMakeFiles/client.dir/requires

CMakeFiles/client.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/client.dir/cmake_clean.cmake
.PHONY : CMakeFiles/client.dir/clean

CMakeFiles/client.dir/depend:
	cd /home/lsf/SocketApiWrapper/src/1.daytimetcp && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/lsf/SocketApiWrapper/src/1.daytimetcp /home/lsf/SocketApiWrapper/src/1.daytimetcp /home/lsf/SocketApiWrapper/src/1.daytimetcp /home/lsf/SocketApiWrapper/src/1.daytimetcp /home/lsf/SocketApiWrapper/src/1.daytimetcp/CMakeFiles/client.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/client.dir/depend

