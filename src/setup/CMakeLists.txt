cmake_minimum_required(VERSION 2.8.8)

add_library(Json Json.cpp)
target_link_libraries(Json ${QT_LIBRARIES})
qt5_use_modules(Json Core)

add_library(JsonParser JsonParser.cpp)
target_link_libraries(JsonParser Json)

add_library(TokenLoader TokenLoader.cpp)
target_link_libraries(TokenLoader JsonParser gmock_main)
