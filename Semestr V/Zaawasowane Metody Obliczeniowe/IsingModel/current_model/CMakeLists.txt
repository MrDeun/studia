cmake_minimum_required(VERSION 3.29)
project(IsingModel)

set(CMAKE_CXX_STANDARD 17)

include_directories(current_model)

add_executable(IsingModel
    src/main.cpp
    src/IsingModel.h
    src/IsingModel.cpp
    src/Statistics.h
    src/Statistics.cpp
)