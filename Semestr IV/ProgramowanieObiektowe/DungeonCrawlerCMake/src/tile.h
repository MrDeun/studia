//
// Created by Patryk on 19-May-24.
//

#ifndef DUNGEONCRAWLERCMAKE_TILE_H
#define DUNGEONCRAWLERCMAKE_TILE_H
#include <string>
#include <map>
#include <cstdint>
class tile {
private:
    static std::map<std::string, unsigned char> type_to_symbol;
    unsigned char symbol;
    std::string type;
public:
    tile(std::string type_in);
    tile() = default;
    void assign(std::string type_in);
    ~tile() = default;
};


#endif //DUNGEONCRAWLERCMAKE_TILE_H
