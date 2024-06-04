cmake_minimum_required(VERSION 3.27)
project(DungeonCrawlerCMake)

set(CMAKE_CXX_STANDARD 17)

add_executable(Dungeon
        src/main.cpp
        src/terminal_game.cpp
        src/game.cpp
        src/labyrinth.cpp
        src/tile.cpp
        src/terminal_game.h
        src/game.h
        src/labyrinth.h
        src/tile.h
)
