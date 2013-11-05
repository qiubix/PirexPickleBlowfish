set(GMOCK_DIR "../../../../gmock-1.7.0"
    CACHE PATH "The path to the GoogleMock test framework.")


add_subdirectory(${GMOCK_DIR} ${CMAKE_BINARY_DIR}/gmock)


include_directories(SYSTEM ${GMOCK_DIR}/gtest/include
                ${GMOCK_DIR}/include)

add_executable(DollarTest DollarTest.cpp)

target_link_libraries(DollarTest Dollar gmock_main)

add_test(DollarTest DollarTest)

#add_library(Test )

#SET(CMAKE_INCLUDE_CURRENT_DIR ON)

#FILE(GLOB files *.cpp)

#FIND_PACKAGE( Qt5Core REQUIRED )

#INCLUDE(${QT_USE_FILE})
#add_definitions(${QT_DEFINITIONS})


#SET(QT_USE_QTTEST TRUE)

#qt_wrap_cpp(LIB_HEADER_MOC ${LIB_HEADER})

#add_executable(MoneyTest MoneyTest.cpp ../src/Money.cpp ../src/main.cpp)

#target_link_libraries(MoneyTest Common ${QT_LIBRARIES})

#add_test(MoneyTest MoneyTest)
