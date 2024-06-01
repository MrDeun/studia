#include "labyrinth.h"
#include <utility>

void Labyrinth::event(Tile &player, Tile &neighbour,direction direct) {
  Tile empty("floor");
  switch (neighbour.get_symbol()) {
    case '#':
      return;
    case ' ':
      player = empty;
    case '_':
      std::swap(player,neighbour);
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
    case 'T':
    case 'E':
    case 'P':
  }
}

void Labyrinth::event(direction direct) {
  switch (direct) {
  case north:
    if (player_y - 1 > -1) {
      event(map[player_y][player_x], map[player_y - 1][player_x],direct);
    }
    break;
  case south:
    if (player_y + 1 < height) {
      event(map[player_y][player_x], map[player_y + 1][player_x],direct);
    }
    break;
  case west:
    if (player_x - 1 > -1) {
      event(map[player_y][player_x], map[player_y][player_x - 1],direct);
    }
    break;
  case east:
    if (player_y + 1 < width) {
      event(map[player_y][player_x], map[player_y][player_x + 1],direct);
    }
    break;
  }
  return;
}