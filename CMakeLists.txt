cmake_minimum_required(VERSION 3.22)
project(cpp_exam)

set(CMAKE_CXX_STANDARD 20)

add_compile_options(-O2)

add_executable(cpp_exam main.cpp my_unordered_map_mutex.h my_unordered_map_atomic_flag.h)
