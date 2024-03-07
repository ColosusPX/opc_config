# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

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
CMAKE_SOURCE_DIR = /home/user/Документы/open62541-pack-master/examples

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/user/Документы/open62541-pack-master/examples/build

# Utility rule file for open62541-generator-ids_example.

# Include any custom commands dependencies for this target.
include nodeset/CMakeFiles/open62541-generator-ids_example.dir/compiler_depend.make

# Include the progress variables for this target.
include nodeset/CMakeFiles/open62541-generator-ids_example.dir/progress.make

nodeset/CMakeFiles/open62541-generator-ids_example: src_generated/open62541/example_nodeids.h

src_generated/open62541/example_nodeids.h: /usr/local/share/open62541/tools/generate_nodeid_header.py
src_generated/open62541/example_nodeids.h: ../nodeset/server_nodeset.csv
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/user/Документы/open62541-pack-master/examples/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Generating ../src_generated/open62541/example_nodeids.h"
	cd /home/user/Документы/open62541-pack-master/examples/build/nodeset && /usr/bin/python3 /usr/local/share/open62541/tools/generate_nodeid_header.py /home/user/Документы/open62541-pack-master/examples/nodeset/server_nodeset.csv /home/user/Документы/open62541-pack-master/examples/build/src_generated/open62541/example_nodeids EXAMPLE_NS

open62541-generator-ids_example: nodeset/CMakeFiles/open62541-generator-ids_example
open62541-generator-ids_example: src_generated/open62541/example_nodeids.h
open62541-generator-ids_example: nodeset/CMakeFiles/open62541-generator-ids_example.dir/build.make
.PHONY : open62541-generator-ids_example

# Rule to build all files generated by this target.
nodeset/CMakeFiles/open62541-generator-ids_example.dir/build: open62541-generator-ids_example
.PHONY : nodeset/CMakeFiles/open62541-generator-ids_example.dir/build

nodeset/CMakeFiles/open62541-generator-ids_example.dir/clean:
	cd /home/user/Документы/open62541-pack-master/examples/build/nodeset && $(CMAKE_COMMAND) -P CMakeFiles/open62541-generator-ids_example.dir/cmake_clean.cmake
.PHONY : nodeset/CMakeFiles/open62541-generator-ids_example.dir/clean

nodeset/CMakeFiles/open62541-generator-ids_example.dir/depend:
	cd /home/user/Документы/open62541-pack-master/examples/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/user/Документы/open62541-pack-master/examples /home/user/Документы/open62541-pack-master/examples/nodeset /home/user/Документы/open62541-pack-master/examples/build /home/user/Документы/open62541-pack-master/examples/build/nodeset /home/user/Документы/open62541-pack-master/examples/build/nodeset/CMakeFiles/open62541-generator-ids_example.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : nodeset/CMakeFiles/open62541-generator-ids_example.dir/depend
