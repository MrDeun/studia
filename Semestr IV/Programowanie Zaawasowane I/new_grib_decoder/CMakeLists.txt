cmake_minimum_required(VERSION 3.27)
project(new_grib_decoder)

set(CMAKE_CXX_STANDARD 17)

add_executable(new_grib_decoder src/main.cpp
        src/convert.cpp
        src/convert.h
        src/grip_decoder.cpp
        src/grip_decoder.h)
