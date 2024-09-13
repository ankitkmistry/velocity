cmake_minimum_required(VERSION 3.15)
project(velocity)

set(CMAKE_CXX_STANDARD 20)
if (MSVC)
else ()
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
endif ()

add_executable(velocity main.cpp
        callable/method.cpp
        callable/callable.cpp
        callable/table.cpp
        callable/frame.cpp
        callable/foreign.cpp
        callable/frame_template.cpp
        callable/inbuilt.cpp
        debug/debug.cpp
        debug/table.cpp
        ee/vm.cpp
        ee/state.cpp
        ee/run.cpp
        ee/thread.cpp
        loader/verifier.cpp
        loader/loader.cpp
        loader/foreign_loader.cpp
        memory/basic/manager.cpp
        memory/basic/collector.cpp
        memory/memory.cpp
        objects/type.cpp
        objects/inbuilt_types.cpp
        objects/obj.cpp
        objects/module.cpp
        objects/typeparam.cpp
        utils/utils.cpp
)

include_directories("../elpops")
target_include_directories(velocity PRIVATE "../elpops")
if (WIN32)
    target_link_libraries(velocity "D:\\Programming (Ankit)\\Projects\\spade\\1.0\\elpops\\debug-build\\libelpops.a")
else ()
    target_link_libraries(velocity "/mnt/d/Programming (Ankit)/Projects/spade/1.0/elpops/debug-build-wsl/libelpops.a")
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ldl")
endif ()
