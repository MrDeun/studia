#ifndef CLASS_LABYRINTH
#define CLASS_LABYRINTH

#include "tile.h"

class Labyrinth {
private:
  int score = 100;
  size_t width, height;
  size_t player_x, player_y;
  Tile **map = nullptr;
  bool finished = false;
  enum direction { north, south, west, east };
  void event(Tile &player, Tile &neighbour);

public:
  ~Labyrinth() = default;
  Labyrinth(size_t width, size_t height);
  void event(direction direct);
  void construct();
  bool is_finished() { return finished; }
  void finish() { finished = true; }
};

#endif