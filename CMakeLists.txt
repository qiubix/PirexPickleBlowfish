#REVIEW: do we really need this PATH comment?
# PATH: PirexPickleBlowfish/CMakeLists.txt

#REVIEW: do we need these comments?
# PROJECT NAME
project(PirexPickleBlowfish)

# CMAKE VERSION REQUIRED
cmake_minimum_required(VERSION 2.8)

# ENABLE add_test() COMMAND
enable_testing()

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

# ADD SUBDIRECTIORIES
add_subdirectory(src)

