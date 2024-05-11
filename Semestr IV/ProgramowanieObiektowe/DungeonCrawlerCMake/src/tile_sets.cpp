//
// Created by Patryk on 19-Apr-24.
//

#include "tile_sets.h"

void hole_tile::event() {
    throw "Hole_Tile event not implemented!";
}

void wall_tile::event() {
    throw "Wall_Tile event not implemented!";
}

void treasure_tile::event(){
    throw "Treasure_Tile event not implemented!";
}

void player_tile::event(direction key_code) {
    throw "Player_Title event not implemented!";
}

void floor_tile::event() {
    throw "Floor_Tile event not implemented!";
}

void exit_tile::event() {
    throw "Exit_Tile event not implemented!";
}