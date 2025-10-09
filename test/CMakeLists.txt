cmake_minimum_required(VERSION 3.17)
project(basic_test)
set(CMAKE_CXX_STANDARD 17)

add_executable(basic_test basic_test.cpp)
find_package(Threads REQUIRED)
target_link_libraries(basic_test PRIVATE Threads::Threads)

add_test(NAME basic_test COMMAND basic_test)
