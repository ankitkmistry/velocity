cmake_minimum_required(VERSION 3.15)
project(velocity)

set(CMAKE_CXX_STANDARD 20)
if (MSVC)
else ()
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
endif ()


add_executable(velocity main.cpp loader/verifier.cpp objects/object.cpp objects/type.cpp objects/method.cpp frame/table.cpp objects/inbuilt_types.cpp frame/frame.cpp ee/opcode.cpp ee/vm.cpp ee/state.cpp loader/loader.cpp debug/debug.cpp debug/table.cpp debug/table.hpp utils/utils.cpp memory/memory.hpp objects/obj.cpp memory/collector.cpp memory/collector.hpp memory/space.cpp memory/space.hpp ee/settings.hpp utils/sign.cpp utils/sign.cpp
        objects/typeparam.hpp
        objects/module.cpp
        objects/module.hpp
        objects/typeparam.cpp)

include_directories("D:/Programming (Ankit)/Projects/spade/1.0/elpops")
target_include_directories(velocity PRIVATE "D:/Programming (Ankit)/Projects/spade/1.0/elpops")

target_link_libraries(velocity "D:/Programming (Ankit)/Projects/spade/1.0/elpops/debug-build/libelpops.a")
