cmake_minimum_required(VERSION 2.8.8)

set(STRING_TO_ENUM_TRANSLATOR_SRC StringToEnumTranslator.cpp ../logic/Token.hpp ../logic/BoardToken.hpp)
add_library(StringToEnumTranslator ${STRING_TO_ENUM_TRANSLATOR_SRC} )

add_library(Json Json.cpp)
target_link_libraries(Json ${QT_LIBRARIES})
qt5_use_modules(Json Core)

add_library(JsonParser JsonParser.cpp)
target_link_libraries(JsonParser Json)

set(GAME_BOX_SRC GameBox.cpp GameBoxExceptions.hpp)
add_library(GameBox ${GAME_BOX_SRC})
target_link_libraries(GameBox ${GTEST_LIBRARIES})
add_dependencies(GameBox gmock)

add_library(TokenLoader TokenLoader.cpp)
target_link_libraries(TokenLoader JsonParser StringToEnumTranslator GameBox logic ${GTEST_LIBRARIES})
add_dependencies(TokenLoader gmock)
