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
  void operator=(const TerminalGame& other){}
  TerminalGame(const TerminalGame& other){}
  ~TerminalGame(){}
};

#endif