//
// Created by pmich on 4/13/2024.
//

#ifndef GAMEOFLIFE_GAME_TXT_H
#define GAMEOFLIFE_GAME_TXT_H
#include "game.h"
#include <iostream>

class game_txt: public game {
    public:
        game_txt():game(){}
        ~game_txt(){}
        void show_table();
        void loop();
        void start();
    private:

};


#endif //GAMEOFLIFE_GAME_TXT_H
