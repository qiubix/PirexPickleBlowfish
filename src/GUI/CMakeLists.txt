# PATH: PirexPickleBlowfish/src/GUI/CMakeLists.txt
if(Win32)
	set(CMAKE_MODULE_PATH "C:\Qt\Qt5.1.1")
endif()
#set(GMOCK_DIR "../../../../Qt5.1.1
#    CACHE PATH "The path to the GoogleMock test framework.")

#set(QT5_DIRECTORY "C:\
find_package(Qt5 REQUIRED)
include_directories(${Qt5Widgets_INCLUDE_DIRS})

set(LIBS ${LIBS} ${QT_QTMAIN_LIBRARY} ${QT_LIBRARIES})

#INCLUDE(${QT_USE_FILE})
#add_subdirectory(${GMOCK_DIR} ${CMAKE_BINARY_DIR}/gmock)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

add_executable(BoardSample BoardSample.cpp)

#qt5_use_modules(BoardSample Widgets)
TARGET_LINK_LIBRARIES(BoardSample ${QT_QTMAIN_LIBRARY} ${QT_LIBRARIES})

IF(WIN32) # Check if we are on Windows
  if(MSVC) # Check if we are using the Visual Studio compiler
    set_target_properties(BoardSample PROPERTIES LINK_FLAGS_RELEASE "/SUBSYSTEM:WINDOWS")
  elseif(CMAKE_COMPILER_IS_GNUCXX)
    # SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -mwindows") # Not tested
  else()
    message(SEND_ERROR "You are using an unsupported Windows compiler! (Not MSVC or GCC)")
  endif()
elseif(UNIX)
  # Nothing special required
else()
  message(SEND_ERROR "You are on an unsupported platform! (Not Win32 or Unix)")
ENDIF()

