#include "tile.h"

std::map<std::string,char> Tile::str_map = {
  {"player",'P'},
  {"wall",'#'},
  {"hole",' '},
  {"floor",'_'},
  {"treasure",'T'},
  {"exit",'E'},
};

std::map<char,std::string> Tile::char_map = {
        {'P',"player"},
        {'#',"wall"},
        {'v',"hole"},
        {'_',"floor"},
        {'T',"treasure"},
        {'E',"exit"}
};
