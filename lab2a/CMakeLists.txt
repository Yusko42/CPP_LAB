cmake_minimum_required(VERSION 3.26)
project(lab2a)

set(CMAKE_CXX_STANDARD 17)

add_executable(lab2a main.cpp
        status.cpp
        user_interaction.cpp
        cell.cpp
        status_calculation.cpp)
add_subdirectory(Google_tests)