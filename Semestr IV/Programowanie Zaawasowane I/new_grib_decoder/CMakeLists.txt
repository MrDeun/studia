cmake_minimum_required(VERSION 3.27)
project(new_grib_decoder)

set(CMAKE_CXX_STANDARD 17)

add_executable(new_grib_decoder src/main.cpp
        src/convert.h
        src/convert.cpp
        src/grib_decoder.h
        src/grib_decoder.cpp
        src/grib_decoder.cpp)
