# PATH: PirexPickleBlowfish/src/CMakeLists.txt


# =========================================================
# USING NEW CMAKE
# =========================================================
cmake_minimum_required(VERSION 2.8.8)

if(WIN32)
    set(Qt5Widgets_DIR "C:/Qt/5.1.1/msvc2012_64_opengl/lib/cmake/Qt5Widgets")
endif()

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${CMAKE_CURRENT_BINARY_DIR})

find_package(Qt5Widgets REQUIRED)

set(SRC_LIST main.cpp)
set(BOARD_SAMPLE_SRC_LIST BoardSample.cpp)
set(MAIN_WINDOW_SAMPLE_SRC_LIST MainWindowSample.cpp)
set(UI_LIST BoardSample.ui MainWindowSample.ui)

qt5_wrap_ui(UI_H_LIST ${UI_LIST})

add_library(BoardSample ${BOARD_SAMPLE_SRC_LIST} ${UI_H_LIST})
add_library(MainWindowSample ${MAIN_WINDOW_SAMPLE_SRC_LIST} ${UI_H_LIST})
add_library(Dollar Dollar.cpp)

qt5_use_modules(BoardSample Widgets)
qt5_use_modules(MainWindowSample Widgets)

add_executable(${PROJECT_NAME} ${SRC_LIST})
target_link_libraries(${PROJECT_NAME} Dollar BoardSample MainWindowSample)

add_subdirectory(test)

# =========================================================
# OLD structure
# =========================================================
#set(CMAKE_INCLUDE_CURRENT_DIR ON)
#
##FILE(GLOB files *.cpp)
#include_directories(${CMAKE_CURRENT_SOURCE_DIR})
#include_directories(${CMAKE_CURRENT_BINARY_DIR})
#
#find_package(Qt5Widgets REQUIRED)
#
##aux_source_directory(. SRC_LIST)
#set(SRC_LIST main.cpp)
#
#add_executable(${PROJECT_NAME} ${SRC_LIST})
#
##add_library(Dollar Dollar.cpp)
#target_link_libraries(${PROJECT_NAME} Dollar BoardSample)
#
#add_subdirectory(test)
#
#add_subdirectory(GUI)
#
#add_subdirectory(Dollar)
