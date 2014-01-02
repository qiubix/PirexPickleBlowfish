set(GMOCK_DIR $ENV{GMOCK_ROOT})

add_subdirectory(${GMOCK_DIR} ${CMAKE_BINARY_DIR}/gmock)
set(CMAKE_AUTOMOC ON)

include_directories(SYSTEM ${GMOCK_DIR}/gtest/include ${GMOCK_DIR}/include)

set(JSON_PARSER_TEST_SRC JsonParserTest.cpp)
set(TOKEN_TEST_SRC TokenTest.cpp)
set(GUI_TEST_SRC MainWindowSampleTest.cpp)
set(GUI_TEST_LIBRARIES MainWindowSample ${QT_QTTEST_LIBRARY} ${QT_LIBRARIES})

add_executable(JsonParserTest ${JSON_PARSER_TEST_SRC})
add_executable(TokenTest ${TOKEN_TEST_SRC})
add_executable(GuiTest ${GUI_TEST_SRC})

target_link_libraries(JsonParserTest logic gmock_main)
target_link_libraries(TokenTest logic gmock_main)
target_link_libraries(GuiTest ${GUI_TEST_LIBRARIES})
qt5_use_modules(GuiTest Test)

add_test(JsonParserTest JsonParserTest)
add_test(TokenTest TokenTest)
add_test(GuiTest GuiTest)
