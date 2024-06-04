#include "game.h"
#include "labyrinth.h"
#include <string>

void Game::BuildLabyrints(size_t count){
  for (size_t i = 0; i<count; i++) {
    std::string map_file = "map" + std::to_string(i+1) + ".txt";
    Labyrinth newLabyrinth{};
    newLabyrinth.construct(map_file); 
    levels.push(newLabyrinth);
  }
  return;
}

void Game::Start(){
  
}