cmake_minimum_required(VERSION 3.11.0)
project(MultiThreadBuffer VERSION 0.1.0 LANGUAGES C CXX)



set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)


add_executable(MultiThreadBuffer main.cpp mainwindow.h mainwindow.cpp shared_buffer.h shared_buffer.cpp worker.h worker.cpp)

target_link_libraries(MultiThreadBuffer PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)