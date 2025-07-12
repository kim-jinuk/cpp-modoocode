cmake_minimum_required(VERSION 3.14)
project(cpp_modoocode_study)
set(CMAKE_CXX_STANDARD 17)

add_executable(hello_world src/01_basic_syntax/hello_world.cpp)

enable_testing()
add_subdirectory(test)
