set(CMAKE_INCLUDE_CURRENT_DIR ON)

aux_source_directory(. SRC_LIST)

add_executable(${PROJECT_NAME} ${SRC_LIST})
