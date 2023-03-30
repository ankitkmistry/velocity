cmake_minimum_required(VERSION 3.24)
project(velocity)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

set(CMAKE_CXX_STANDARD 17)

add_executable(velocity main.cpp loader/parser.cpp loader/verifier.cpp oop/oop.cpp oop/type.cpp oop/method.cpp frame/table.cpp oop/objects.cpp frame/frame.cpp ee/opcode.cpp ee/vm.cpp ee/thread.cpp ee/state.cpp frame/writer.cpp loader/loader.cpp loader/writer.cpp loader/writer.hpp)
add_executable(spasm assembler/assembler_main.cpp assembler/SpadeAssemblyVisitor.h assembler/SpadeAssemblyVisitor.cpp assembler/SpadeAssemblyParser.h assembler/SpadeAssemblyParser.cpp assembler/SpadeAssemblyLexer.h assembler/SpadeAssemblyLexer.h assembler/SpadeAssemblyLexer.cpp assembler/SpadeAssemblyBaseVisitor.h assembler/SpadeAssemblyBaseVisitor.cpp assembler/SpadeAssemblyListener.cpp assembler/SpadeAssemblyBaseListener.h assembler/SpadeAssemblyListener.cpp assembler/SpadeAssemblyBaseListener.cpp)

# required if linking to static library
#add_definitions(-DANTLR4CPP_STATIC)

# using /MD flag for antlr4_runtime (for Visual C++ compilers only)
set(ANTLR4_WITH_STATIC_CRT OFF)

# Specify the version of the antlr4 library needed for this project.
# By default the latest version of antlr4 will be used.  You can specify a
# specific, stable version by setting a repository tag value or a link
# to a zip file containing the libary source.
set(ANTLR4_TAG 4.12.0)
set(ANTLR4_ZIP_REPOSITORY https://github.com/antlr/antlr4/archive/refs/tags/4.12.0.zip)

# add external build for antlr-cpp
include(ExternalAntlr4Cpp)
# add antlr4cpp artifacts to project environment
include_directories(${ANTLR4_INCLUDE_DIR})

# set variable pointing to the antlr tool that supports C++
# this is not required if the jar file can be found under PATH environment
set(ANTLR_EXECUTABLE "H:\\Programming (Ankit)\\Toolkits\\ANTLR4\\antlr-4.12.0-complete.jar")
# add macros to generate ANTLR Cpp code from grammar
find_package(ANTLR REQUIRED)
add_dependencies(spasm antlr4_shared)
target_link_libraries(spasm PRIVATE antlr4_shared)
