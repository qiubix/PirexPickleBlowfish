#REVIEW: do we really need this PATH comment?
# PATH: PirexPickleBlowfish/src/gui/CMakeLists.txt

#REVIEW: do we really need this USING NEW CMAKE comment?
# =========================================================
# USING NEW CMAKE
# =========================================================
cmake_minimum_required(VERSION 2.8.8)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${CMAKE_CURRENT_BINARY_DIR})

find_package(Qt5Widgets REQUIRED)

set(MAIN_WINDOW_SAMPLE_SRC_LIST MainWindowSample.cpp)
set(UI_LIST MainWindowSample.ui)

qt5_wrap_ui(UI_H_LIST ${UI_LIST})

add_library(MainWindowSample ${MAIN_WINDOW_SAMPLE_SRC_LIST} ${UI_H_LIST})

qt5_use_modules(MainWindowSample Widgets)
