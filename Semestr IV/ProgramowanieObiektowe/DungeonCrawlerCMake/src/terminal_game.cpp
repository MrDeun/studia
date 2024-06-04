#include "terminal_game.h"
#include "conio.h"
#include "labyrinth.h"
#include <cstddef>
#include <cstdio>
#include <iostream>

void TerminalGame::Show() {
  for (size_t y = 0; y < current_level.getHeight(); y++) {
    for (size_t x = 0; x < current_level.getWidth(); x++) {
      std::cout << current_level.getSymbol(x, y);
    }
    std::cout << '\n';
  }
}
direction TerminalGame::AwaitInput() {
  char symbol{};
  direction way;
  bool correct = false;
  while (!correct) {
    symbol = getch();
    switch (symbol) {
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

void TerminalGame::endLevel(){
  bool Win = (current_level.getFinalScore() > 0) ? true : false;
  std::cout << "\033[2J\033[1;1H"; // Special string to sends out a clear multiplatform
  std::cout << "Your score is... " << current_level.getFinalScore();
  std::cout << ((Win) ? "YOU SURVIVED!" : "YOU DIED!");
  if (Win) {
    nextLevel();
  }
}

void TerminalGame::Loop() {
  while (remainingLevels()) {
    current_level = getLevel();
    while (!current_level.is_finished()) {
      direction direct = AwaitInput();
      current_level.event(direct);
    }
    endLevel();
  }
  return;
}