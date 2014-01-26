#tests connected with token loading
set(STRING_TO_ENUM_TRANSLATOR_TEST_SRC StringToEnumTranslatorTest.cpp)
set(JSON_TEST_SRC JsonTest.cpp)
set(JSON_PARSER_TEST_SRC JsonParserTest.cpp)
set(GAME_BOX_TEST_SRC GameBoxTest.cpp)
set(TOKEN_LOADER_TEST_SRC TokenLoaderTest.cpp MockJson.hpp)

set(CONTROLLER_TEST_SRC ControllerTest.cpp)
set(MODEL_TEST_SRC ModelTest.cpp)
set(TOKEN_TEST_SRC TokenTest.cpp MockController.hpp)
set(FIELD_TEST_SRC FieldTest.cpp)
set(PLAYER_TEST_SRC PlayerTest.cpp)
set(GUI_TEST_SRC MainWindowSampleTest.cpp)
set(GUI_TEST_LIBRARIES MainWindowSample ${QT_QTTEST_LIBRARY} ${QT_LIBRARIES})

#tests connected with token loading
add_executable(StringToEnumTranslatorTest ${STRING_TO_ENUM_TRANSLATOR_TEST_SRC})
add_executable(JsonTest ${JSON_TEST_SRC})
add_executable(JsonParserTest ${JSON_PARSER_TEST_SRC})
add_executable(GameBoxTest ${GAME_BOX_TEST_SRC})
add_executable(TokenLoaderTest ${TOKEN_LOADER_TEST_SRC})
#test all classes responsible of loading tokens together
add_executable(LoadingTokensTest ${STRING_TO_ENUM_TRANSLATOR_TEST_SRC} ${JSON_TEST_SRC} ${JSON_PARSER_TEST_SRC} ${GAME_BOX_TEST_SRC} ${TOKEN_LOADER_TEST_SRC})

add_executable(ControllerTest ${CONTROLLER_TEST_SRC})
add_executable(ModelTest ${MODEL_TEST_SRC})
add_executable(TokenTest ${TOKEN_TEST_SRC})
add_executable(FieldTest ${FIELD_TEST_SRC})
add_executable(PlayerTest ${PLAYER_TEST_SRC})
add_executable(LogicTest ${FIELD_TEST_SRC} ${PLAYER_TEST_SRC} ${MODEL_TEST_SRC} ${CONTROLLER_TEST_SRC} ${TOKEN_TEST_SRC})
add_executable(GuiTest ${GUI_TEST_SRC})

#tests connected with token loading
target_link_libraries(StringToEnumTranslatorTest StringToEnumTranslator gmock_main)
target_link_libraries(JsonTest Json gmock_main)
target_link_libraries(JsonParserTest JsonParser gmock_main)
target_link_libraries(GameBoxTest GameBox logic gmock_main)
target_link_libraries(TokenLoaderTest TokenLoader gmock_main)
#test all classes responsible of loading tokens together
target_link_libraries(LoadingTokensTest StringToEnumTranslator Json JsonParser GameBox TokenLoader gmock_main)


target_link_libraries(ControllerTest logic gmock_main)
target_link_libraries(ModelTest logic gmock_main)
target_link_libraries(TokenTest logic gmock_main)
target_link_libraries(FieldTest logic gmock_main)
target_link_libraries(PlayerTest logic gmock_main)
target_link_libraries(LogicTest logic gmock_main)
target_link_libraries(GuiTest ${GUI_TEST_LIBRARIES})
qt5_use_modules(GuiTest Test)

#tests connected with token loading
install(TARGETS StringToEnumTranslatorTest DESTINATION ${CMAKE_INSTALL_PREFIX})
install(TARGETS JsonTest DESTINATION ${CMAKE_INSTALL_PREFIX})
install(TARGETS JsonParserTest DESTINATION ${CMAKE_INSTALL_PREFIX})
install(TARGETS GameBoxTest DESTINATION ${CMAKE_INSTALL_PREFIX})
install(TARGETS TokenLoaderTest DESTINATION ${CMAKE_INSTALL_PREFIX})
#test all classes responsible of loading tokens together
install(TARGETS LoadingTokensTest DESTINATION ${CMAKE_INSTALL_PREFIX})

install(TARGETS TokenTest DESTINATION ${CMAKE_INSTALL_PREFIX})
install(TARGETS ControllerTest DESTINATION ${CMAKE_INSTALL_PREFIX})
install(TARGETS ModelTest DESTINATION ${CMAKE_INSTALL_PREFIX})
install(TARGETS FieldTest DESTINATION ${CMAKE_INSTALL_PREFIX})
install(TARGETS PlayerTest DESTINATION ${CMAKE_INSTALL_PREFIX})
install(TARGETS LogicTest DESTINATION ${CMAKE_INSTALL_PREFIX})
install(TARGETS GuiTest DESTINATION ${CMAKE_INSTALL_PREFIX})

#tests connected with token loading
add_test(StringToEnumTranslatorTest StringToEnumTranslatorTest)
add_test(JsonTest JsonTest)
add_test(JsonParserTest JsonParserTest)
add_test(GameBoxTest GameBoxTest)
add_test(TokenLoaderTest TokenLoaderTest)
add_test(LoadingTokensTest LoadingTokensTest)

add_test(TokenTest TokenTest)
add_test(ControllerTest ControllerTest)
add_test(ModelTest ModelTest)
add_test(FieldTest FieldTest)
add_test(PlayerTest PlayerTest)
add_test(LogicTest LogicTest)
add_test(GuiTest GuiTest)

#test files to TokenLoaderTest
file(COPY test.json DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
install(FILES test.json DESTINATION ${CMAKE_INSTALL_PREFIX})
file(COPY twoChangeAttributeUpgradesParameters.json DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
install(FILES twoChangeAttributeUpgradesParameters.json DESTINATION ${CMAKE_INSTALL_PREFIX})
file(COPY oneChangeAttributeOfEnemyUpgradeParameters.json DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
install(FILES oneChangeAttributeOfEnemyUpgradeParameters.json DESTINATION ${CMAKE_INSTALL_PREFIX})
file(COPY changeArmyUpgradeParameters.json DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
install(FILES changeArmyUpgradeParameters.json DESTINATION ${CMAKE_INSTALL_PREFIX})
file(COPY twoAddAttributeUpgradesParameters.json DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
install(FILES twoAddAttributeUpgradesParameters.json DESTINATION ${CMAKE_INSTALL_PREFIX})
file(COPY oneAddAttributeAndOneChangeAttributeUpgradesParameters.json DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
install(FILES oneAddAttributeAndOneChangeAttributeUpgradesParameters.json DESTINATION ${CMAKE_INSTALL_PREFIX})
