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
  void event(Tile &player, Tile &neighbour,direction direct);
  void update_location(direction direct);

public:
  ~Labyrinth();
  Labyrinth(size_t width, size_t height);
  Labyrinth() = default;
  void event(direction direct);
  void construct(std::string filename);
  bool is_finished() { return finished; }
  void finish() { finished = true; }
};

#endif