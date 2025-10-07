# CMakeLists.txt ─ 루트
cmake_minimum_required(VERSION 3.17)
project(cpp_modoocode_study LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)

enable_testing()                       # ← CTest 온!

file(GLOB_RECURSE SRC_LIST CONFIGURE_DEPENDS src/*.cpp)

foreach(src_file IN LISTS SRC_LIST)
    # src/01_basic/hello_world.cpp → exe 이름: 01_basic_hello_world
    file(RELATIVE_PATH rel ${CMAKE_SOURCE_DIR}/src ${src_file})
    string(REPLACE "/" "_" exe_name "${rel}")
    string(REPLACE ".cpp" "" exe_name "${exe_name}")

    add_executable(${exe_name} ${src_file})

    # 실행만 되면 “통과”로 간주. 0 이외 리턴 시 CI 빨간불
    add_test(NAME run_${exe_name} COMMAND ${exe_name} TIMEOUT 10)

endforeach()
