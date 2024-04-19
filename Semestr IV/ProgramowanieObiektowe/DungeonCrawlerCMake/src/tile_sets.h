//
// Created by Patryk on 19-Apr-24.
//

#ifndef DUNGEONCRAWLERCMAKE_TILE_SETS_H
#define DUNGEONCRAWLERCMAKE_TILE_SETS_H

#include "Tile.h"

class player_tile: public Tile{
public:
    player_tile(): Tile('P'){};
    ~player_tile(){}
    void event();
};

class wall_tile: public Tile{
public:
    wall_tile(): Tile('#'){};
    ~wall_tile(){}
    void event();
};

class floor_tile: public Tile{
public:
    floor_tile():Tile('_'){}
    ~floor_tile(){}
    void event();
};

class hole_tile: public Tile{
public:
    hole_tile():Tile(' '){}
    ~hole_tile() = default;
    void event();
};

class treasure_tile:public Tile{
    public:
    treasure_tile():Tile('G'){}
    ~treasure_tile() = default;
    void event();
};

class exit_tile:public Tile{
    public:
    exit_tile():Tile('E'){}
    ~exit_tile() = default;
    void event();
};


#endif //DUNGEONCRAWLERCMAKE_TILE_SETS_H
