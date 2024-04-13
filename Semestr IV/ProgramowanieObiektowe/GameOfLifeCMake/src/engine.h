//
// Created by Patryk on 12-Apr-24.
//

#ifndef GAMEOFLIFE_ENGINE_H
#define GAMEOFLIFE_ENGINE_H

class engine {
private:
  bool *board;
  int size_x, size_y;

public:
  engine(int new_x, int new_y);
  ~engine();
  void next_stage();
  int count_neighbour(int id_x, int id_y);
};

#endif // GAMEOFLIFE_ENGINE_H
