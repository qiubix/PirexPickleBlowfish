# PATH: PirexPickleBlowfish/src/GUI/CMakeLists.txt

# =========================================================
# USING NEW CMAKE
# =========================================================
cmake_minimum_required(VERSION 2.8.8)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
include_directories(${CMAKE_CURRENT_BINARY_DIR})

find_package(Qt5Widgets REQUIRED)

set(SRC_LIST BoardSample.cpp)
set(UI_LIST BoardSample.ui)

qt5_wrap_ui(UI_H_LIST ${UI_LIST})

add_executable(BoardSample ${SRC_LIST} ${UI_H_LIST})

qt5_use_modules(BoardSample Widgets)
#target_link_libraries(BoardSample Qt5::Widgets)

# =========================================================
# USING OLDER CMAKE
# =========================================================

#cmake_minimum_required(VERSION 2.8.3)
#
#set(CMAKE_INCLUDE_CURRENT_DIR ON)
#include_directories(${CMAKE_CURRENT_BINARY_DIR})
#
#find_package(Qt5Widgets REQUIRED)
#include_directories(${Qt5Widgets_INCLUDE_DIRS})
#add_definitions(${Qt5Widgets_DEFINITIONS})
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${Qt5Widgets_EXECUTABLE_COMPILE_FLAGS}")
#
#qt5_generate_moc(BoardSample.cpp BoardSample.moc)
#
#add_executable(BoardSample BoardSample.cpp BoardSample.moc)
#
#target_link_libraries(${Qt5Widgets_LIBRARIES})

# =========================================================
# WINDOWS BULLSHIT
# =========================================================

#if(WIN32)
#    set(Qt5_DIR "C:/Qt/5.1.1/msvc2012_64_opengl/lib/cmake")
#endif()
#
#IF(WIN32) # Check if we are on Windows
#  if(MSVC) # Check if we are using the Visual Studio compiler
#    set_target_properties(BoardSample PROPERTIES LINK_FLAGS_RELEASE "/SUBSYSTEM:WINDOWS")
#  elseif(CMAKE_COMPILER_IS_GNUCXX)
#    # SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -mwindows") # Not tested
#  else()
#    message(SEND_ERROR "You are using an unsupported Windows compiler! (Not MSVC or GCC)")
#  endif()
#elseif(UNIX)
#  # Nothing special required
#else()
#  message(SEND_ERROR "You are on an unsupported platform! (Not Win32 or Unix)")
#ENDIF()

