#ifndef CLASS_TERMINAL
#define CLASS_TERMINAL

#include "game.h"
class TerminalGame:Game{
  private:
  public:
  TerminalGame() = default;
  ~TerminalGame() = default;
  void Show();
  direction AwaitInput();
};

#endif