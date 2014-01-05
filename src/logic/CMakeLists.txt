file(GLOB SRC_LIST *.cpp)
add_library(logic ${SRC_LIST})
install(TARGETS logic DESTINATION ${CMAKE_INSTALL_PREFIX})
