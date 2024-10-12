cmake_minimum_required(VERSION 3.26)
project(lab0b)

set(CMAKE_CXX_STANDARD 17)

add_executable(lab0b main.cpp
        csv_creation.cpp
        txt_reading.cpp)
