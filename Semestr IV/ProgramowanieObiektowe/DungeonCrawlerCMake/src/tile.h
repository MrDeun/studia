#ifndef CLASS_TILE
#define CLASS_TILE

#include <map>
#include <string>

class Tile {
private:
  std::string type;
  char symbol;
  static std::map<std::string, char> trans_map;

public:
  Tile(std::string in) : type(in) { symbol = trans_map[in]; }
  char get_symbol() { return symbol; }
  ~Tile() = default;
};

#endif