cmake_minimum_required(VERSION 3.24)
project(velocity)

set(CMAKE_CXX_STANDARD 17)

add_executable(velocity main.cpp loader/parser.cpp loader/verifier.cpp oop/oop.cpp oop/type.cpp oop/type.hpp oop/objects.hpp oop/method.cpp oop/method.hpp frame/table.hpp frame/table.cpp oop/objects.cpp frame/frame.cpp frame/frame.hpp ee/opcode.hpp ee/opcode.cpp ee/vm.cpp ee/vm.hpp ee/thread.cpp ee/thread.hpp ee/state.hpp ee/state.cpp utils/constants.hpp frame/writer.hpp frame/writer.cpp loader/loader.hpp loader/loader.cpp)