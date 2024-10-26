cmake_minimum_required(VERSION 3.29)
project(IsingModel)

set(CMAKE_CXX_STANDARD 17)

include_directories(current_model)

add_executable(IsingModel
    current_model/IsingModel.cpp
    current_model/IsingModel.h
    current_model/IsingStats.h
    current_model/main.cpp
    current_model/Statistics.cpp
    current_model/Statistics.h)
