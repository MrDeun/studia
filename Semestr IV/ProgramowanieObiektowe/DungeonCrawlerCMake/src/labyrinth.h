#ifndef CLASS_LABYRINTH
#define CLASS_LABYRINTH

#include "tile.h"

#include <vector>
  enum direction { north, south, west, east };

class Labyrinth {
private:
  int score = 100;
  size_t width{}, height{};
  int player_x = -1, player_y= -1;
  std::vector<std::vector<Tile>> map;
  bool finished = false;
  void event(Tile &player, Tile &neighbour, direction direct);
  void update_location(direction direct);
  static void SwapTiles(Tile& first, Tile& second){Tile temp{first};first = second; second = temp;}

public:
  ~Labyrinth(){};
  Labyrinth(size_t width, size_t height);
  Labyrinth() = default;
  void operator=(const Labyrinth& other){}
  Labyrinth(const Labyrinth& other){}
  void event(direction direct);
  void construct(const std::string& filename);
  void vec_build(size_t x, size_t y, const std::vector<char>& map_data);
  bool is_finished() { return finished; }
  size_t getWidth() { return width; }
  size_t getHeight() { return height; }
  char getSymbol(size_t x ,size_t y){return map[y][x].getSymbol();}
  int getFinalScore(){return score;}
  void finish() { finished = true; }
};

#endif
