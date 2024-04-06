#pragma once

#include <cstdint>#include <vector>
#include "cell.hpp"
class Board{
    private:
        size_t size_x, size_y;
        Cell** board;
    public:
        Board(size_t _size_x, size_t _size_y);
        ~Board();
};