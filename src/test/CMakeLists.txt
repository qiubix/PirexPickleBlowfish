#REVIEW: do we really need this PATH comment?
# PATH: PirexPickleBlowfish/src/test/CMakeLists.txt

#REVIEW: this comment is for example necessary because it explains not trivial code
# setting gmock directory. By default using gmock v1.7.0
# installed in home directory (~/gmock-1.7.0)
set(GMOCK_DIR "../../../../gmock-1.7.0"
    CACHE PATH "The path to the GoogleMock test framework.")

add_subdirectory(${GMOCK_DIR} ${CMAKE_BINARY_DIR}/gmock)

#REVIEW: maybe oneliner is better?
include_directories(SYSTEM ${GMOCK_DIR}/gtest/include
                ${GMOCK_DIR}/include)

add_executable(DollarTest DollarTest.cpp)

set(GUI_TEST_SRC MainWindowSampleTest.cpp)
#REVIEW: maybe oneliner is better?
set(GUI_TEST_LIBRARIES MainWindowSample
          ${QT_QTTEST_LIBRARY}
          ${QT_LIBRARIES})
add_executable(GuiTest ${GUI_TEST_SRC})
qt5_use_modules(GuiTest Test)

target_link_libraries(DollarTest logic gmock_main)
target_link_libraries(GuiTest ${GUI_TEST_LIBRARIES})

add_test(DollarTest DollarTest)
add_test(GuiTest GuiTest)
