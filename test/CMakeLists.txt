include_directories(${CMAKE_CURRENT_SOURCE_DIR})

find_package(Qt5Widgets REQUIRED)

macro(create_test name src libs)
  add_executable(${name} ${src})
  target_link_libraries(${name} ${GMOCK_LIBRARIES} ${GMOCK_MAIN_LIBRARIES} ${libs})
  add_dependencies(${name} gmock)
  if(CMAKE_COMPILER_IS_GNUC OR CMAKE_COMPILER_IS_GNUCXX)
    target_link_libraries(${name} pthread)
  endif(CMAKE_COMPILER_IS_GNUC OR CMAKE_COMPILER_IS_GNUCXX)
  install(TARGETS ${name} DESTINATION ${CMAKE_INSTALL_PREFIX})
  add_test(${name} ${name})
endmacro(create_test)

#tests connected with token loading
set(JSON_PARSER_TEST_SRC JsonParserTest.cpp JsonConstants.hpp)
set(JSON_PARSER_TEST_LIBS JsonParser)
create_test(JsonParserTest "${JSON_PARSER_TEST_SRC}" "${JSON_PARSER_TEST_LIBS}")
set(JSON_TEST_SRC JsonTest.cpp JsonConstants.hpp)
set(JSON_TEST_LIBS Json)
create_test(JsonTest "${JSON_TEST_SRC}" "${JSON_TEST_LIBS}")

set(STRING_TO_ENUM_TRANSLATOR_TEST_SRC StringToEnumTranslatorTest.cpp)
set(STRING_TO_ENUM_TRANSLATOR_TEST_LIBS StringToEnumTranslator)
create_test(StringToEnumTranslatorTest "${STRING_TO_ENUM_TRANSLATOR_TEST_SRC}" "${STRING_TO_ENUM_TRANSLATOR_TEST_LIBS}")
set(GAME_BOX_TEST_SRC GameBoxTest.cpp)
set(GAME_BOX_TEST_LIBS GameBox logic)
create_test(GameBoxTest "${GAME_BOX_TEST_SRC}" "${GAME_BOX_TEST_LIBS}")
set(TOKEN_LOADER_TEST_SRC TokenLoaderTest.cpp MockJson.hpp)
set(TOKEN_LOADER_TEST_LIBS TokenLoader logic)
create_test(TokenLoaderTest "${TOKEN_LOADER_TEST_SRC}" "${TOKEN_LOADER_TEST_LIBS}")

set(LOADING_TOKENS_TEST_SRC ${STRING_TO_ENUM_TRANSLATOR_TEST_SRC} ${JSON_TEST_SRC} ${JSON_PARSER_TEST_SRC} ${GAME_BOX_TEST_SRC} ${TOKEN_LOADER_TEST_SRC})
set(LOADING_TOKENS_TEST_LIBS StringToEnumTranslator Json JsonParser GameBox TokenLoader)
create_test(LoadingTokensTest "${LOADING_TOKENS_TEST_SRC}" "${LOADING_TOKENS_TEST_LIBS}")

# tests connected with game logic
set(LOGIC_TEST_LIBS logic TokenLoader)

set(MODEL_TEST_SRC FieldTest.cpp BoardTest.cpp PlayerTest.cpp ModelTest.cpp)
create_test(ModelTest "${MODEL_TEST_SRC}" "${LOGIC_TEST_LIBS}")
set(CONTROLLER_TEST_SRC ControllerTest.cpp)
create_test(ControllerTest "${CONTROLLER_TEST_SRC}" "${LOGIC_TEST_LIBS}")
set(TOKEN_TEST_SRC TokenTest.cpp BoardTokenTest.cpp UnitTokenTest.cpp ModuleTokenTest.cpp InstantTokenTest.cpp MockController.hpp HeadquartersTest.cpp)
create_test(TokenTest "${TOKEN_TEST_SRC}" "${LOGIC_TEST_LIBS}")

set(LOGIC_TEST_SRC ${CONTROLLER_TEST_SRC} ${MODEL_TEST_SRC} ${TOKEN_TEST_SRC})
create_test(LogicTest "${LOGIC_TEST_SRC}" "${LOGIC_TEST_LIBS}")

# test connected with gui
set(GUI_TEST_SRC MainWindowSampleTest.cpp)
set(GUI_TEST_LIBS MainWindowSample ${QT_QTTEST_LIBRARY} ${QT_LIBRARIES})
create_test(GuiTest "${GUI_TEST_SRC}" "${GUI_TEST_LIBS}")
qt5_use_modules(GuiTest Test)

# suite containing all tests
set(ALL_TESTS_SRC ${LOADING_TOKENS_TEST_SRC} ${LOGIC_TEST_SRC})
set(ALL_TESTS_LIBS ${LOADING_TOKENS_TEST_LIBS} ${LOGIC_TEST_LIBS})
create_test(AllTests "${ALL_TESTS_SRC}" "${ALL_TESTS_LIBS}")

macro(install_file file)
  file(COPY ${file} DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
  install(FILES ${file} DESTINATION ${CMAKE_INSTALL_PREFIX})
endmacro(install_file)

#test files to TokenLoaderTest
install_file(test.json)
install_file(twoChangeAttributeUpgradesParameters.json)
install_file(oneChangeAttributeOfEnemyUpgradeParameters.json)
install_file(changeArmyUpgradeParameters.json)
install_file(twoAddAttributeUpgradesParameters.json)
install_file(oneAddAttributeAndOneChangeAttributeUpgradesParameters.json)

#army files to ControllerTest
install_file(moloch.json)
