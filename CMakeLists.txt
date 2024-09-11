cmake_minimum_required(VERSION 3.15)
project(velocity)

set(CMAKE_CXX_STANDARD 20)
if (MSVC)
else ()
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
endif ()

add_executable(velocity main.cpp loader/verifier.cpp objects/type.cpp callable/method.cpp callable/table.cpp objects/inbuilt_types.cpp callable/frame.cpp ee/vm.cpp ee/state.cpp loader/loader.cpp debug/debug.cpp debug/table.cpp utils/utils.cpp objects/obj.cpp utils/sign.cpp utils/sign.cpp
        objects/module.cpp
        objects/typeparam.cpp
        loader/foreign_loader.hpp
        loader/foreign_loader.cpp
        callable/callable.hpp
        callable/foreign.hpp
        callable/foreign.cpp
        callable/frame_template.cpp
        callable/frame_template.hpp
        ee/run.cpp
        memory/basic/manager.cpp
        memory/basic/manager.hpp
        ee/thread.cpp
        memory/memory.cpp
        callable/callable.cpp
        memory/basic/collector.cpp
        memory/basic/collector.hpp
        callable/inbuilt.cpp
        callable/inbuilt.hpp
)

include_directories("../elpops")
target_include_directories(velocity PRIVATE "../elpops")
if (WIN32)
    target_link_libraries(velocity "D:\\Programming (Ankit)\\Projects\\spade\\1.0\\elpops\\debug-build\\libelpops.a")
else ()
    target_link_libraries(velocity "/mnt/d/Programming (Ankit)/Projects/spade/1.0/elpops/debug-build-wsl/libelpops.a")
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ldl")
endif ()
