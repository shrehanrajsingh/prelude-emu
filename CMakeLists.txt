cmake_minimum_required(VERSION 3.10.0)
project(prelude VERSION 0.1.0 LANGUAGES C CXX)
enable_testing()

add_subdirectory(tests)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(prelude
    inst_set.hpp inst_set.cpp
    module.hpp module.cpp
    stack.hpp stack.cpp
    prelude.hpp prelude.cpp)

