#include "terminal_game.h"
int main(){
    size_t levelsCount = 2;
  TerminalGame thisGame{};
  thisGame.Start(levelsCount);
  return 0;
}