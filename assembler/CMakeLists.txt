cmake_minimum_required(VERSION 3.10.0)
project(prasm VERSION 0.1.0 LANGUAGES C CXX)
enable_testing()

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(tests)

add_library(prasm
    header.hpp
    token.hpp token.cpp
    asm.hpp asm.cpp)

