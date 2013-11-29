# PATH: PirexPickleBlowfish/src/GUI/CMakeLists.txt

#set(GMOCK_DIR "../../../../Qt5.1.1
#    CACHE PATH "The path to the GoogleMock test framework.")

find_package(Qt5Widgets REQUIRED)

#add_subdirectory(${GMOCK_DIR} ${CMAKE_BINARY_DIR}/gmock)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
#include_directories(SYSTEM ${GMOCK_DIR}/gtest/include
#                ${GMOCK_DIR}/include)

add_executable(BoardSample BoardSample.cpp)

qt5_use_modules(BoardSample Widgets)
#target_link_libraries(DollarTest Dollar gmock_main)

#add_test(DollarTest DollarTest)


