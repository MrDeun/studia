cmake_minimum_required(VERSION 3.27)
project(DungeonCrawlerCMake)

set(CMAKE_CXX_STANDARD 17)

add_executable(DungeonCrawlerCMake src/main.cpp
        src/Tile.cpp
        src/Tile.h
        src/tile_sets.cpp
        src/tile_sets.h
        src/labyrinth.cpp
        src/labyrinth.h
        src/engine.cpp
        src/engine.h)
