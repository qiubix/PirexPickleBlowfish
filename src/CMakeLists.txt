cmake_minimum_required(VERSION 2.8.8)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${CMAKE_CURRENT_BINARY_DIR})

find_package(Qt5Widgets REQUIRED)

set(GMOCK_DIR $ENV{GMOCK_ROOT})

add_subdirectory(${GMOCK_DIR} ${CMAKE_BINARY_DIR}/gmock)
set(CMAKE_AUTOMOC ON)

include_directories(SYSTEM ${GMOCK_DIR}/gtest/include ${GMOCK_DIR}/include)


#to link dynamic boost libraries
add_definitions(-DBOOST_LOG_DYN_LINK)

find_package(Boost 1.55 COMPONENTS thread system log log_setup REQUIRED )
include_directories(${Boost_INCLUDE_DIR} )

add_library(Logger Logger.cpp)
target_link_libraries(Logger ${Boost_LIBRARIES})
install(TARGETS Logger DESTINATION ${CMAKE_INSTALL_PREFIX})

set(PROJECT_SRC_LIST main.cpp)
set(PROJECT_LIBS logic MainWindowSample Logger GameBox TokenLoader)
add_executable(${PROJECT_NAME} ${PROJECT_SRC_LIST})
target_link_libraries(${PROJECT_NAME} ${PROJECT_LIBS})
install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX})

file(COPY moloch.json DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
  install(FILES moloch.json DESTINATION ${CMAKE_INSTALL_PREFIX})
file(COPY outpost.json DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
  install(FILES outpost.json DESTINATION ${CMAKE_INSTALL_PREFIX})

add_subdirectory(gui)
add_subdirectory(logic)
add_subdirectory(test)
add_subdirectory(setup)
