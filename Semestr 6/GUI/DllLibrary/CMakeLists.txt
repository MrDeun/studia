cmake_minimum_required(VERSION 3.10.0)
project(DllExample VERSION 0.1.0 LANGUAGES C CXX)

add_library(DllExample SHARED DllExample.cpp)

