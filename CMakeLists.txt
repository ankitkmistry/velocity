cmake_minimum_required(VERSION 3.15)
project(velocity)

set(CMAKE_CXX_STANDARD 20)
if (MSVC)
else ()
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
endif ()

add_executable(velocity src/main.cpp
        src/callable/method.cpp
        src/callable/callable.cpp
        src/callable/table.cpp
        src/callable/frame.cpp
        src/callable/foreign.cpp
        src/callable/frame_template.cpp
        src/callable/inbuilt.cpp
        src/debug/debug.cpp
        src/debug/table.cpp
        src/ee/vm.cpp
        src/ee/state.cpp
        src/ee/run.cpp
        src/ee/thread.cpp
        src/loader/verifier.cpp
        src/loader/loader.cpp
        src/loader/foreign_loader.cpp
        src/memory/basic/basic_manager.cpp
        src/memory/basic/basic_collector.cpp
        src/memory/manager.cpp
        src/objects/type.cpp
        src/objects/inbuilt_types.cpp
        src/objects/obj.cpp
        src/objects/module.cpp
        src/objects/typeparam.cpp
        src/utils/utils.cpp
        src/objects/int.cpp
        src/objects/float.cpp
        src/callable/foreign_call.cpp
)

include_directories(../sputils/src)
target_include_directories(velocity PUBLIC ../sputils/src)
if (WIN32)
    target_link_libraries(velocity "D:\\Programming (Ankit)\\Projects\\spade\\1.0\\sputils\\build-debug\\libsputils.a")
else ()
    target_link_libraries(velocity "/mnt/d/Programming (Ankit)/Projects/spade/1.0/sputils/build-wsl/libsputils.a")
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ldl")
endif ()
