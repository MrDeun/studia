#include "labyrinth.h"
#include "tile.h"
#include <cstddef>
#include <fstream>
#include <ios>
#include <utility>

void Labyrinth::update_location(direction direct) {
    switch (direct) {
        case north:
            player_y++;
            break;
        case south:
            player_y--;
            break;
        case west:
            player_x--;
            break;
        case east:
            player_x++;
            break;
    }
}

void Labyrinth::event(Tile &player, Tile &neighbour, direction direct) {
    Tile empty("floor");
    switch (neighbour.get_symbol()) {
        case '#':
            break;
        case ' ':
            player = empty;
            score = 0;
            finish();
            break;
        case '_':
            std::swap(player, neighbour);
            update_location(direct);
            break;
        case 'T':
            neighbour = player;
            player = empty;
            score += 100;
            update_location(direct);
            break;
        case 'E':
            finish();
            break;
        case 'P':
        default:
            throw "Unknown Object!";
            break;
    }
}

void Labyrinth::construct(std::string filename) {
    std::ifstream file(filename);
    file >> width >> height;
    file.unsetf(std::ios::skipws);
    if (!map.empty()) {
        map.clear();
    }

    for (int i = 0; i < height; ++i) {
        std::vector<Tile> new_vec(width);
        map.push_back(new_vec);
    }

    for (size_t y{}; y < height; y++) {
        for (size_t x{}; x < width; x++) {
            char temp;
            file.get(&temp, 1);
            if (temp == 'P') {
                player_x = x;
                player_y = y;
            }
            Tile new_tile(temp);
            map[y][x] = new_tile;
        }
    }
}

void Labyrinth::event(direction direct) {
    switch (direct) {
        case north:
            if (player_y - 1 > -1) {
                event(map[player_y][player_x], map[player_y - 1][player_x], direct);
            }
            break;
        case south:
            if (player_y + 1 < height) {
                event(map[player_y][player_x], map[player_y + 1][player_x], direct);
            }
            break;
        case west:
            if (player_x - 1 > -1) {
                event(map[player_y][player_x], map[player_y][player_x - 1], direct);
            }
            break;
        case east:
            if (player_y + 1 < width) {
                event(map[player_y][player_x], map[player_y][player_x + 1], direct);
            }
            break;
    }
    return;
}