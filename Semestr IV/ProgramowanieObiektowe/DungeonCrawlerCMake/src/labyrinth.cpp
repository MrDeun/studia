//
// Created by pmich on 4/19/2024.
//

#include "labyrinth.h"

void labyrinth::event(player_tile::direction key_code) {

}

Tile put_tile(char symbol){
    switch (symbol) {
        case 'H':
            hole_tile temp_hole;
            return temp_hole;
    }
}

void labyrinth::construct(std::ifstream *ptr_filestream) {
    for (int i = 0; i<size_y;i++) {
        std::vector<char> current_row = ptr_filestream->getline();
        for (int j = 0; j<size_x;j++) {
            tile_container[j + i * size_x] = put_tile(current_row[i]);
        }
    }
}