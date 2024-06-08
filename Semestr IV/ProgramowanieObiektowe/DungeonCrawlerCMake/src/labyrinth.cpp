#include "labyrinth.h"
#include "tile.h"
#include <fstream>
#include <ios>
#include <utility>
#include <iostream>

void Labyrinth::update_location(direction direct) {
    switch (direct) {
        case north:
            player_y--;
            break;
        case south:
            player_y++;
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
    switch (neighbour.getSymbol()) {
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

void Labyrinth::construct(const std::string &filename) {
    std::ifstream file(filename);
    file >> width >> height;
    if (!map.empty()) {
        map.clear();
    }

    for (int i = 0; i < height; ++i) {
        std::vector<Tile> new_vec(width);
        map.push_back(new_vec);
    }

    std::string map_data{};
    while (file.good()) {
        std::string temp{};
        file >> temp;
        std::cout << temp << '\n';
        map_data += temp;
    }
    std::cout << map_data << '\n';

    for (int y{}; y < height; y++) {
        for (int x{}; x < width; x++) {
            Tile new_tile{map_data[x + width * y]};
            if(new_tile.getSymbol() == 'P'){
                player_x = x;
                player_y = y;
            }

            map[y][x] = new_tile;
        }
        }
    }


    void Labyrinth::vec_build(size_t x_in, size_t y_in, const std::vector<char> &map_data) {
        width = x_in;
        height = y_in;
        if (!map.empty()) {
            map.clear();
            for (int y = 0; y < height; ++y) {
                std::vector<Tile> new_vec(x_in);
                map.push_back(new_vec);
            }
        }

        for (int y = 0; y < height; ++y) {
            for (int x = 0; x < width; ++x) {
                char new_symbol = map_data[x + y * height];
                if (new_symbol == 'P') {
                    player_y = y;
                    player_x = x;
                }
                Tile new_tile{new_symbol};
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