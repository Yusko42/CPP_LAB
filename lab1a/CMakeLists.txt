cmake_minimum_required(VERSION 3.26)
project(lab1a)

set(CMAKE_CXX_STANDARD 17)

add_executable(lab1a main.cpp
        bitarray.cpp)
add_subdirectory(Google_tests)