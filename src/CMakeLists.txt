set(CMAKE_INCLUDE_CURRENT_DIR ON)

FILE(GLOB files *.cpp)

aux_source_directory(. SRC_LIST)

add_executable(${PROJECT_NAME} ${SRC_LIST})

add_library(Core ${SRC_LIST})

add_subdirectory(test)
