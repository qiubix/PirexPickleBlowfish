project(PirexPickleBlowfish)

cmake_minimum_required(VERSION 2.8)

# CUSTOM CMAKE FIND LOCATION
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake")

# ENABLE add_test() COMMAND
enable_testing()

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_subdirectory(src)

