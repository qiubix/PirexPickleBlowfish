cmake_minimum_required(VERSION 2.8.8)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${CMAKE_CURRENT_BINARY_DIR})

# Generate GUI classes based on design stored in *.ui files
# That basically allows to create GUI with QtCreator Designer
set(CMAKE_AUTOMOC ON)

find_package(Qt5Widgets REQUIRED)

set(MAIN_WINDOW_SAMPLE_SRC_LIST MainWindowSample.cpp ViewController.cpp Board.cpp Hexagon.cpp SideField.cpp BoardField.cpp)
set(UI_LIST MainWindowSample.ui)

qt5_wrap_ui(UI_H_LIST ${UI_LIST})

add_library(MainWindowSample ${MAIN_WINDOW_SAMPLE_SRC_LIST} ${UI_H_LIST})
target_link_libraries(MainWindowSample logic)
install(TARGETS MainWindowSample DESTINATION ${CMAKE_INSTALL_PREFIX})

file(COPY armies DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
install(DIRECTORY armies DESTINATION ${CMAKE_INSTALL_PREFIX})

qt5_use_modules(MainWindowSample Widgets)
