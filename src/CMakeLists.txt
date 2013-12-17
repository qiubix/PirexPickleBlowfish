#REVIEW: do we really need this PATH comment?
# PATH: PirexPickleBlowfish/src/CMakeLists.txt

#REVIEW: do we really need this USING NEW CMAKE comment?
# =========================================================
# USING NEW CMAKE
# =========================================================
cmake_minimum_required(VERSION 2.8.8)

#REVIEW: do we really need these comments?
#QUESTION: what is CMAKE_AUTOMOC for?
# basic settings
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${CMAKE_CURRENT_BINARY_DIR})

# finding Qt5 package
find_package(Qt5Widgets REQUIRED)

# creating main executable program
set(SRC_LIST main.cpp)
add_executable(${PROJECT_NAME} ${SRC_LIST})
target_link_libraries(${PROJECT_NAME} logic MainWindowSample)

#REVIEW: do we really need this ADDING SUBDIRECTORIES comment?
# =========================================================
# ADDING SUBDIRECTORIES
# =========================================================
#REVIEW: for now we don't have ai and we not writing it so it shouldn't even be here
add_subdirectory(ai)
add_subdirectory(gui)
add_subdirectory(logic)
add_subdirectory(test)
