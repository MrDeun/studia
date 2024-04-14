//
// Created by pmich on 4/13/2024.
//

#ifndef GAMEOFLIFE_GAME_H
#define GAMEOFLIFE_GAME_H
#include "engine.h"

class game: public engine {
    public:
        game(): engine(16,16){}
        virtual ~game(){}
    private:

};


#endif //GAMEOFLIFE_GAME_H
