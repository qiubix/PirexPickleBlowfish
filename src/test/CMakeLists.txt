set(TOKEN_LOADER_TEST_SRC TokenLoaderTest.cpp)
set(TOKEN_TEST_SRC TokenTest.cpp)
set(GUI_TEST_SRC MainWindowSampleTest.cpp)
set(GUI_TEST_LIBRARIES MainWindowSample ${QT_QTTEST_LIBRARY} ${QT_LIBRARIES})

add_executable(TokenLoaderTest ${TOKEN_LOADER_TEST_SRC})
add_executable(TokenTest ${TOKEN_TEST_SRC})
add_executable(GuiTest ${GUI_TEST_SRC})

target_link_libraries(TokenLoaderTest Json JsonParser TokenLoader gmock_main)
target_link_libraries(TokenTest logic gmock_main)
target_link_libraries(GuiTest ${GUI_TEST_LIBRARIES})
qt5_use_modules(GuiTest Test)

install(TARGETS TokenTest DESTINATION ${CMAKE_INSTALL_PREFIX})
install(TARGETS TokenLoaderTest DESTINATION ${CMAKE_INSTALL_PREFIX})
install(TARGETS GuiTest DESTINATION ${CMAKE_INSTALL_PREFIX})

add_test(TokenLoaderTest TokenLoaderTest)
add_test(TokenTest TokenTest)
add_test(GuiTest GuiTest)
