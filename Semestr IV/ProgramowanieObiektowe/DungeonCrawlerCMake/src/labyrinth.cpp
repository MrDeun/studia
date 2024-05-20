//
// Created by Patryk on 19-May-24.
//

#include "labyrinth.h"

tile labyrinth::insert_tile(char buf) {
    switch(buf){
        case '#':
            tile new_wall("wall");
            return new_wall;
        case '_':
            tile new_floor("floor");
            return new_floor;
        case ' ':
            tile new_hole("hole");
            return new_hole;
        case 'P':
            tile new_player("player");
            return new_player;
        case 'T':
            tile new_treasure("treasure");
            return new_treasure;
        case 'E':
            tile new_exit("exit");
            return new_exit;
        default:
            throw "FAILURE: Incorrent tile symbol during reading";
    }
}

void labyrinth::construct() {
    std::ifstream file("labyrinth.dat",std::ios::binary);
    width = reader::read_size(file);
    height = reader::read_size(file);
    if (layout != nullptr)
        delete layout;
    layout = new tile[width*height];
    for (size_t y = 0; y < height; ++y) {
        for (size_t x = 0; x < width; ++x) {
            char buf;
            file.read(&buf,1);
            layout[x + y * height] = insert_tile(buf);
        }
    }
}