//
// Created by Patryk on 19-May-24.
//

#ifndef DUNGEONCRAWLERCMAKE_LABYRINTH_H
#define DUNGEONCRAWLERCMAKE_LABYRINTH_H
#include "tile.h"
#include "read_file.h"
#include <vector>

class labyrinth {
private:
    size_t width{},height{};
    tile* layout = nullptr;
public:
    labyrinth() = default;
    ~labyrinth(){delete layout;}
    void construct();
    static tile insert_tile(char buf);
};


#endif //DUNGEONCRAWLERCMAKE_LABYRINTH_H
