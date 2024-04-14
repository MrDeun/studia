//
// Created by Patryk on 12-Apr-24.
//

#ifndef GAMEOFLIFE_ENGINE_H
#define GAMEOFLIFE_ENGINE_H
#include <cstdlib>
#include <ctime>

class engine {
private:
  bool *board;
  int size_x, size_y;
  static bool chance(int max);

public:
  engine(int new_x, int new_y);
  virtual ~engine();
  void next_stage();
  bool check_rule(int neighbours);
  int count_neighbour(int id_x, int id_y);
  virtual void show_table();
  int get_size_x(){return size_x;}
  int get_size_y(){return size_x;}
  bool get_cell(int id_x, int id_y){return board[id_x + id_y * size_y];}
  void set_state(int id_x, int id_y){
      board[id_x + id_y * size_y] = chance(100);
  };
};

#endif // GAMEOFLIFE_ENGINE_H
