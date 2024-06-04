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
  void Start();
  TerminalGame() = default;
  ~TerminalGame(){};
};

#endif