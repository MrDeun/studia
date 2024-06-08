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

Game::Game(size_t x, size_t y, const std::vector<char>& map_data) {
    Labyrinth test_lab{};
    test_lab.vec_build(x,y,map_data);
}

void Game::Start(){
  BuildLabyrints(2);
  Loop();
  return;
}