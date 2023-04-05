cmake_minimum_required(VERSION 3.15)
project(velocity)

set(CMAKE_CXX_STANDARD 17)
#add_compile_options(-pthread)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

add_executable(velocity main.cpp loader/parser.cpp loader/verifier.cpp oop/oop.cpp oop/type.cpp oop/method.cpp frame/table.cpp oop/objects.cpp frame/frame.cpp ee/opcode.cpp ee/vm.cpp ee/thread.cpp ee/state.cpp frame/writer.cpp loader/loader.cpp loader/writer.cpp loader/writer.hpp debug/debug.cpp debug/table.cpp debug/table.hpp utils/utils.cpp)
