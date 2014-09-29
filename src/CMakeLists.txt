cmake_minimum_required(VERSION 2.8.8)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${CMAKE_CURRENT_BINARY_DIR})

find_package(Qt5Widgets REQUIRED)

set(PROJECT_SRC_LIST main.cpp)
set(PROJECT_LIBS logic MainWindowSample GameBox TokenLoader)
add_executable(${PROJECT_NAME} ${PROJECT_SRC_LIST})
target_link_libraries(${PROJECT_NAME} ${PROJECT_LIBS})
install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX})

file(COPY moloch.json DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
  install(FILES moloch.json DESTINATION ${CMAKE_INSTALL_PREFIX})
file(COPY outpost.json DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
  install(FILES outpost.json DESTINATION ${CMAKE_INSTALL_PREFIX})

add_subdirectory(gui)
add_subdirectory(logic)
add_subdirectory(setup)
