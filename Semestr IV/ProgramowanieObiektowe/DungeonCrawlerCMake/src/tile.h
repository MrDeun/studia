#ifndef CLASS_TILE
#define CLASS_TILE

#include <map>
#include <string>

class Tile {
private:
  std::string type;
  char symbol;
  static std::map<std::string, char> str_map;
  static std::map<char, std::string> char_map;

public:
  Tile(char symbol_in) {
    if (symbol_in == 'v') {
      symbol = ' ';
    } else {
      symbol = symbol_in;
    }
    type = char_map[symbol];
  }
  Tile(const std::string &in) : type(in) { symbol = str_map[in]; }
  Tile() {
    symbol = ' ';
    type = char_map[symbol];
  }
  void operator=(Tile& other){type = other.type;symbol=other.symbol;};
  Tile(const Tile& other){type = other.type;symbol=other.symbol;}
  char getSymbol() { return symbol; }
  ~Tile() = default;
};

#endif