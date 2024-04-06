#pragma once

#include "cell.hpp"
#include <cstdint>

Cell::Cell(size_t _id_x,size_t _id_y) : id_x(_id_x),id_y(_id_y) {
    is_alive = false;
}

Cell::~Cell(){}
