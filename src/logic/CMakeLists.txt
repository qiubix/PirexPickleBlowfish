file(GLOB SRC_LIST *.cpp)
file(GLOB HPP_LIST *.hpp)
add_library(logic ${SRC_LIST} ${HPP_LIST})
install(TARGETS logic DESTINATION ${CMAKE_INSTALL_PREFIX})
