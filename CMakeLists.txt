project(PirexPickleBlowfish)

cmake_minimum_required(VERSION 2.8)

include(setCpp11CompilerFlagIfSupported.cmake)
set_cpp11_compiler_flag_if_supported()

enable_testing()

set(CMAKE_INCLUDE_CURRENT_DIR ON)
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

set(GMOCK_DIR $ENV{GMOCK_ROOT})

add_subdirectory(${GMOCK_DIR} ${CMAKE_BINARY_DIR}/gmock)
set(CMAKE_AUTOMOC ON)

include_directories(SYSTEM ${GMOCK_DIR}/gtest/include ${GMOCK_DIR}/include)


IF(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
  SET(CMAKE_INSTALL_PREFIX ${CMAKE_SOURCE_DIR}/bin CACHE PATH "${CMAKE_PROJECT_NAME} install prefix" FORCE)
ENDIF(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)


add_subdirectory(src)

add_subdirectory(test)
