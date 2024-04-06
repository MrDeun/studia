#pragma once

#include "cell.hpp"
#include "board.hpp"

Board::Board(size_t _size_x, size_t _size_y): size_x(_size_x),size_y(_size_y){
    board = new Cell*[size_y];
    for (size_t i = 0; i < size_y; ++i) {
        *board = new Cell[size_x]()
    }
}