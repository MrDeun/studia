#include "terminal_game.h"
#include "labyrinth.h"
#include <conio.h>
#include <iostream>

void TerminalGame::Show() {
    std::cout << "\033[2J\033[1;1H"; // Special string to sends out a clear multiplatform
    for (size_t y = 0; y < current_level.getHeight(); y++) {
        for (size_t x = 0; x < current_level.getWidth(); x++) {
            std::cout << current_level.getSymbol(x, y);
        }
        std::cout << '\n';
    }
}

direction TerminalGame::AwaitInput() {
    char buf[256];
    direction way;
    bool correct = false;
    while (!correct) {
        buf[0] = getch();
        switch (buf[0]) {
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


void TerminalGame::endLevel() {
    bool Win = (current_level.getFinalScore() > 0);
    std::cout << "\033[2J\033[1;1H"; // Special string to sends out a clear multiplatform
    std::cout << "Your score is... " << current_level.getFinalScore() << '\n';
    std::cout << ((Win) ? "YOU SURVIVED!\n" : "YOU DIED!\n");
    if (Win) {
        nextLevel();
    }
}

void TerminalGame::Loop() {
    while (remainingLevels()) {
        current_level = getLevel();
        while (!current_level.is_finished()) {
            Show();
            direction direct = AwaitInput();
            current_level.event(direct);
        }
        endLevel();
    }
    return;
}