# PATH: PirexPickleBlowfish/src/test/CMakeLists.txt

set(GMOCK_DIR "../../../../gmock-1.7.0"
    CACHE PATH "The path to the GoogleMock test framework.")


add_subdirectory(${GMOCK_DIR} ${CMAKE_BINARY_DIR}/gmock)


include_directories(SYSTEM ${GMOCK_DIR}/gtest/include
                ${GMOCK_DIR}/include)

add_executable(DollarTest DollarTest.cpp)
add_executable(MainWindowSampleTest MainWindowSampleTest.cpp)

target_link_libraries(DollarTest Dollar gmock_main)
target_link_libraries(MainWindowSampleTest MainWindowSample)

add_test(DollarTest DollarTest)
add_test(MainWindowSampleTest MainWindowSampleTest)


