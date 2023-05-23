cmake_minimum_required(VERSION 3.15)
project(velocity)

set(CMAKE_CXX_STANDARD 20)
if (MSVC)
else ()
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
endif ()

add_executable(velocity main.cpp loader/parser.cpp loader/verifier.cpp oop/oop.cpp oop/type.cpp oop/method.cpp frame/table.cpp oop/objects.cpp frame/frame.cpp ee/opcode.cpp ee/vm.cpp ee/thread.cpp ee/state.cpp loader/loader.cpp debug/debug.cpp debug/table.cpp debug/table.hpp utils/utils.cpp memory/memory.hpp oop/obj.cpp memory/collector.cpp memory/collector.hpp memory/space.cpp memory/space.hpp ee/settings.hpp)
