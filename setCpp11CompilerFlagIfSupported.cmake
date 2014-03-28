#this function assumes GNU GCC as compiler
#function sets -std=c++11 flag on CMAKE_CXX_FLAGS in parent scope
#TODO: make this work with other compilers
#TODO: figure out if it is possible to have + in function name (to have c++11 instead of cpp)
#TODO: figure out how set -std=c++11 flag on CMAKE_CXX_FLAGS "globally"

function(set_cpp11_compiler_flag_if_supported)
	include(CheckCXXCompilerFlag)
	CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)

	if(NOT COMPILER_SUPPORTS_CXX11)
	  message(FATAL_ERROR "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support. Please use a different C++ compiler. Cmake will exit now.")
	else()
	  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11" PARENT_SCOPE)
	endif()
endfunction()