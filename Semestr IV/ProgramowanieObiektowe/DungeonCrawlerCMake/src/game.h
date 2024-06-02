#ifndef CLASS_GAME
#define CLASS_GAME

#include "labyrinth.h"
#include <queue>
class Game {
private:
  std::queue<Labyrinth> levels;
  void State();
public:
  Game() = default;
  ~Game() = default;
  void BuildLabyrints(size_t count);
  void Start();
};

#endif