cmake_minimum_required(VERSION 3.24)
project(velocity)

set(CMAKE_CXX_STANDARD 17)

add_executable(velocity main.cpp loader/parser.cpp loader/verifier.cpp oop/oop.cpp oop/type.cpp oop/type.hpp oop/objects.hpp oop/method.cpp oop/method.hpp frame/table.hpp frame/table.cpp oop/objects.cpp)