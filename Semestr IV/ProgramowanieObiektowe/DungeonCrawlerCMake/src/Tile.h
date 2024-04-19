//
// Created by Patryk on 19-Apr-24.
//

#ifndef DUNGEONCRAWLER_TILE_H
#define DUNGEONCRAWLER_TILE_H


class Tile {
    protected:
        unsigned char symbol{};
    public:
        Tile() = default;
        ~Tile() = default;
        Tile(char sym_in):symbol(sym_in){}
        unsigned char get_symbol(){return symbol;}
        virtual void event();
};


#endif DUNGEONCRAWLER_TILE_H
