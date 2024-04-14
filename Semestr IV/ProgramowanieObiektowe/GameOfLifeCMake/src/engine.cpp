//
// Created by Patryk on 12-Apr-24.
//

#include "engine.h"

bool engine::check_rule(int neighbours) {
    if (neighbours > 4 || neighbours < 2){
        return false;
    } else
        return true;
}

engine::engine(int new_x, int new_y) : size_x(new_x), size_y(new_y) {
  board = new bool[size_x * size_y];
  srand(time(NULL));
}

bool engine::chance(int max) {
    int state = rand()%max + 1;
    return (state >= 90) ? true : false;
}

engine::~engine() { delete[] board; }

void engine::show_table(){}

void engine::next_stage() {
  bool* temp_board = new bool[size_x * size_y];
  for (int id_x = 0; id_x < size_x; id_x++) {
    for (int id_y = 0; id_y < size_y; id_y++) {
      int neighbours = count_neighbour(id_x, id_y);
      temp_board[id_x + id_y * size_y] = check_rule(neighbours);
    }
  }
  delete[] board;
  board = temp_board;
  return;
}

int engine::count_neighbour(int id_x, int id_y) {
  int count = 0;
  for (int offset_x = -1; offset_x < 2; offset_x++) {
    for (int offset_y = -1; offset_y < 2; offset_y++) {
      if (offset_x != 0 && offset_x != offset_y) {
        if(id_x + offset_x >= 0 &&
        id_x + offset_x < size_x &&
        id_y + offset_y >= 0 &&
        id_y + offset_y < size_y){
          board[(id_x + offset_x) + (id_y + offset_y) * size_y] ? count++ : count = count;
        }
      }
    }
  }
  return count;
}
