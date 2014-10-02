project(PirexPickleBlowfish)

cmake_minimum_required(VERSION 2.8)

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)
SET(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)

include(C++11Compiling)
include(GoogleMock)
include(DefaultBuildType)

setDefaultBuildType(Debug)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

set(CMAKE_AUTOMOC ON)

IF(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
  SET(CMAKE_INSTALL_PREFIX ${CMAKE_SOURCE_DIR}/bin CACHE PATH "${CMAKE_PROJECT_NAME} install prefix" FORCE)
ENDIF(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)

add_subdirectory(src)
add_subdirectory(test)
