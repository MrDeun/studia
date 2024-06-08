#include "game.h"
#include "labyrinth.h"
#include <string>

void Game::BuildLabyrints(size_t count){
  for (size_t i = 0; i<count; i++) {
    std::string map_file = "level" + std::to_string(i) + ".txt";
    Labyrinth newLabyrinth{};
    newLabyrinth.construct(map_file); 
    levels.push(newLabyrinth);
  }
  return;
}

void Game::Start(size_t level_count){
  BuildLabyrints(level_count);
  Loop();
  return;
}