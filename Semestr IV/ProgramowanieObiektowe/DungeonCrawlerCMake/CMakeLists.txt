cmake_minimum_required(VERSION 3.27)
project(DungeonCrawlerCMake)

set(CMAKE_CXX_STANDARD 17)

add_executable(Dungeon
        src/main.cpp
        src/terminal_game.cpp
        src/terminal_game.h
        src/engine.cpp
        src/engine.h
        src/tile.cpp
        src/tile.h
        src/labyrinth.cpp
        src/labyrinth.h
        src/read_file.cpp
        src/read_file.h)
