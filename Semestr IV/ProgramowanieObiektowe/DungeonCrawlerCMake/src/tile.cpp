#include "tile.h"

std::map<std::string,char> Tile::trans_map = {
  {"player",'P'},
  {"wall",'#'},
  {"hole",' '},
  {"floor",'_'},
  {"treasure",'T'},
  {"exit",'E'},
};