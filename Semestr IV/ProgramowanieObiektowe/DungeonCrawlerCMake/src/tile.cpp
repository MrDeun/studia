//
// Created by Patryk on 19-May-24.
//

#include "tile.h"

std::map<std::string,unsigned char> tile::type_to_symbol = {
        {"wall",'#'},
        {"player",'P'},
        {"hole",' '},
        {"treasure",'T'},
        {"exit",'E'},
        {"floor",'_'}
};

tile::tile(std::string type_in): type(type_in) {
    symbol = type_to_symbol[type];
}

void tile::assign(std::string type_in) {
    type = type_in;
    symbol = type_to_symbol[type];
}