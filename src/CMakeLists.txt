#set(CMAKE_INCLUDE_CURRENT_DIR ON)

#FILE(GLOB files *.cpp)
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

aux_source_directory(. SRC_LIST)

#add_executable(${PROJECT_NAME} ${SRC_LIST})
add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(${PROJECT_NAME} Dollar)
#add_library(Core ${SRC_LIST})
add_library(Dollar Dollar.cpp)

add_subdirectory(test)

#target_link_libraries(${PROJECT_NAME} Test)

add_test(firstTest ${PROJECT_NAME})
