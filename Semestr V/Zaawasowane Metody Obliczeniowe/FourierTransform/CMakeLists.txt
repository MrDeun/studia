cmake_minimum_required(VERSION 3.20.0)
project(FourierTransform VERSION 0.1.0 LANGUAGES C CXX)

set(CXX_STANDARD 11)

add_executable(FourierTransform src/main.cpp src/dft.cpp src/fft.cpp src/dft.h src/fft.h)
add_executable(NoiseTransform src/noise.cpp src/fft.cpp src/fft.h src/regression.h src/regression.cpp)

