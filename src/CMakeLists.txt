# PATH: PirexPickleBlowfish/src/CMakeLists.txt

set(CMAKE_INCLUDE_CURRENT_DIR ON)

#FILE(GLOB files *.cpp)
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

#aux_source_directory(. SRC_LIST)
set(SRC_LIST main.cpp)

add_executable(${PROJECT_NAME} ${SRC_LIST})

add_library(Dollar Dollar.cpp)
target_link_libraries(${PROJECT_NAME} Dollar)

add_subdirectory(test)

add_subdirectory(GUI)

