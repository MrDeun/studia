//
// Created by pmich on 4/19/2024.
//

#ifndef DUNGEONCRAWLERCMAKE_LABYRINTH_H
#define DUNGEONCRAWLERCMAKE_LABYRINTH_H

#include "tile_sets.h"
class labyrinth {
    private:
        int size_x, size_y;
        Tile* tile_container;
        bool finished = false;
        size_t player_tile_x = 0, player_tile_y = 0;
    public:
        labyrinth(int in_x,int in_y):size_x(in_x),size_y(in_y){
            tile_container = new Tile[size_x * size_y];
        }
        bool is_finished(){
            return finished;
        }

        Tile put_tile(char symbol);
        void construct(std::ifstream* ptr_filestream);
        void event(player_tile::direction key_code);
};


#endif //DUNGEONCRAWLERCMAKE_LABYRINTH_H
