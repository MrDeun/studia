cmake_minimum_required(VERSION 3.29)
project(clion_project)

set(CMAKE_CXX_STANDARD 17)

add_executable(clion_project main.cpp
        SimulationModel.cpp
        SimulationModel.h)
