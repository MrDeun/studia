#ifndef CLASS_GAME
#define CLASS_GAME

#include "labyrinth.h"
#include <queue>
class Game {
private:
  std::queue<Labyrinth> levels;
void BuildLabyrints(size_t count);
  virtual void Show(){}
  virtual direction AwaitInput(){return north;}
  virtual void Loop(){}
  virtual void endLevel(){}
public:
  Game(){}
  virtual ~Game(){}
  void operator=(const Game& other){}
  Game(const Game& other){}
  void nextLevel(){levels.pop();}
  Labyrinth current_level;
  bool remainingLevels(){return !levels.empty();}
  Labyrinth getLevel(){return levels.front();}
  void Start(size_t count);
};

#endif