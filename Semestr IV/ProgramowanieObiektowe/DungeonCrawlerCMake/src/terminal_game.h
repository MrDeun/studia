#ifndef CLASS_TERMINAL
#define CLASS_TERMINAL

#include "game.h"
class TerminalGame : public Game {
private:
  direction AwaitInput();
  void Show();
  void Loop();
  void endLevel();

public:
  TerminalGame(){}
  TerminalGame(size_t size_x, size_t size_y, const std::vector<char>& map_data);
  ~TerminalGame(){}
};

#endif