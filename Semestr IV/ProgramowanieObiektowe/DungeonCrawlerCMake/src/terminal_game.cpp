#include "terminal_game.h"
#include "labyrinth.h"
#include "conio.h"
#include <cstdio>
void TerminalGame::Show(){
  for (int y = 0 ;y<current_level.getHeight();y++ ) {
    
  }
}

direction TerminalGame::AwaitInput(){
  char symbol{};
  direction way;
  bool correct = false;
  while (!correct) {
    symbol = getchar();
    switch(symbol){
      case 'w':
        way = north;
        correct = true;
        break;
      case 's':
        way = south;
        correct = true;
        break;
      case 'a':
        way = west;
        correct = true;
        break;
      case 'd':
        way = east;
        correct = true;
        break;
      default:
        break;
    }
  }
  return way;
}