# PATH: PirexPickleBlowfish/src/test/CMakeLists.txt

set(GMOCK_DIR "../../../../gmock-1.7.0"
    CACHE PATH "The path to the GoogleMock test framework.")


add_subdirectory(${GMOCK_DIR} ${CMAKE_BINARY_DIR}/gmock)


include_directories(SYSTEM ${GMOCK_DIR}/gtest/include
                ${GMOCK_DIR}/include)

add_executable(DollarTest DollarTest.cpp)

set(GUI_TEST_SRC MainWindowSampleTest.cpp)
set(GUI_TEST_LIBRARIES MainWindowSample
          ${QT_QTTEST_LIBRARY}
          ${QT_LIBRARIES})
add_executable(GUI_TEST ${GUI_TEST_SRC})
qt5_use_modules(GUI_TEST Test)

target_link_libraries(DollarTest Dollar gmock_main)
target_link_libraries(GUI_TEST ${GUI_TEST_LIBRARIES})


add_test(DollarTest DollarTest)
add_test(GUI_TEST GUI_TEST)


