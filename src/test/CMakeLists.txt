set(GMOCK_DIR $ENV{GMOCK_ROOT})
message("GMock directory: ${GMOCK_DIR}")

add_subdirectory(${GMOCK_DIR} ${CMAKE_BINARY_DIR}/gmock)
set(CMAKE_AUTOMOC ON)

include_directories(SYSTEM ${GMOCK_DIR}/gtest/include ${GMOCK_DIR}/include)

set(DOLLAR_TEST_SRC DollarTest.cpp)
set(GUI_TEST_SRC MainWindowSampleTest.cpp)
set(GUI_TEST_LIBRARIES MainWindowSample ${QT_QTTEST_LIBRARY} ${QT_LIBRARIES})

add_executable(DollarTest ${DOLLAR_TEST_SRC})
add_executable(GuiTest ${GUI_TEST_SRC})

target_link_libraries(DollarTest logic gmock_main)
target_link_libraries(GuiTest ${GUI_TEST_LIBRARIES})
qt5_use_modules(GuiTest Test)

add_test(DollarTest DollarTest)
add_test(GuiTest GuiTest)
