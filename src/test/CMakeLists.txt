set(JSON_PARSER_TEST_SRC JsonParserTest.cpp MockBoostJson.hpp MockQtJson.hpp)
set(TOKEN_TEST_SRC TokenTest.cpp)
set(GUI_TEST_SRC MainWindowSampleTest.cpp)
set(GUI_TEST_LIBRARIES MainWindowSample ${QT_QTTEST_LIBRARY} ${QT_LIBRARIES})

add_executable(JsonParserTest ${JSON_PARSER_TEST_SRC})
add_executable(TokenTest ${TOKEN_TEST_SRC})
add_executable(GuiTest ${GUI_TEST_SRC})

target_link_libraries(JsonParserTest BoostJson BoostJsonParser QtJson QtJsonParser gmock_main)
target_link_libraries(TokenTest logic gmock_main)
target_link_libraries(GuiTest ${GUI_TEST_LIBRARIES})
qt5_use_modules(GuiTest Test)

install(TARGETS TokenTest DESTINATION ${CMAKE_INSTALL_PREFIX})
install(TARGETS GuiTest DESTINATION ${CMAKE_INSTALL_PREFIX})
install(TARGETS JsonParserTest DESTINATION ${CMAKE_INSTALL_PREFIX})

add_test(JsonParserTest JsonParserTest)
add_test(TokenTest TokenTest)
add_test(GuiTest GuiTest)
