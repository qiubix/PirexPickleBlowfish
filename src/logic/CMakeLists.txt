#REVIEW: do we really need this PATH comment
# PATH: PirexPickleBlowfish/src/logic/CMakeLists.txt

file(GLOB SRC_LIST *.cpp)
add_library(logic ${SRC_LIST})
