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
    public:
        labyrinth(int in_x,int in_y):size_x(in_x),size_y(in_y){
            tile_container = new Tile[size_x * size_y];
        }
};


#endif //DUNGEONCRAWLERCMAKE_LABYRINTH_H
