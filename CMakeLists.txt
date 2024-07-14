cmake_minimum_required(VERSION 3.15)
project(velocity)

set(CMAKE_CXX_STANDARD 20)
if (MSVC)
else ()
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
endif ()

add_executable(velocity main.cpp loader/verifier.cpp objects/object.cpp objects/type.cpp objects/method.cpp frame/table.cpp objects/inbuilt_types.cpp frame/frame.cpp ee/vm.cpp ee/state.cpp loader/loader.cpp debug/debug.cpp debug/table.cpp utils/utils.cpp objects/obj.cpp memory/collector.cpp memory/space.cpp utils/sign.cpp utils/sign.cpp
        objects/module.cpp
        objects/typeparam.cpp
        loader/native_loader.hpp
        loader/native_loader.cpp)

include_directories("../elpops")
target_include_directories(velocity PRIVATE "../elpops")
if (WIN32)
    target_link_libraries(velocity "D:\\Programming (Ankit)\\Projects\\spade\\1.0\\elpops\\debug-build\\libelpops.a")
else ()
    target_link_libraries(velocity "/mnt/d/Programming (Ankit)/Projects/spade/1.0/elpops/debug-build-wsl/libelpops.a")
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ldl")
endif ()
