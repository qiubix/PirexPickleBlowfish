cmake_minimum_required(VERSION 2.8.8)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${CMAKE_CURRENT_BINARY_DIR})

find_package(Qt5Widgets REQUIRED)

set(SRC_LIST main.cpp)

#to link dynamic boost libraries
add_definitions(-DBOOST_LOG_DYN_LINK)

find_package(Boost 1.55 COMPONENTS thread system log log_setup REQUIRED )
include_directories(${Boost_INCLUDE_DIR} )

add_library(BoostJson BoostJson.cpp Json.hpp)
target_link_libraries(BoostJson ${Boost_LIBRARIES})

add_library(BoostJsonParser BoostJsonParser.cpp JsonParser.hpp)
target_link_libraries(BoostJsonParser BoostJson ${Boost_LIBRARIES})

add_library(Logger Logger.cpp)
target_link_libraries(Logger ${Boost_LIBRARIES})

add_executable(${PROJECT_NAME} ${SRC_LIST})

target_link_libraries(${PROJECT_NAME} logic MainWindowSample Logger)

add_subdirectory(gui)
add_subdirectory(logic)
add_subdirectory(test)
