//
// Created by pmich on 4/19/2024.
//

#ifndef DUNGEONCRAWLERCMAKE_ENGINE_H
#define DUNGEONCRAWLERCMAKE_ENGINE_H

#include "labyrinth.h"
#include <queue>

class engine {
    private:
        std::queue<labyrinth> queue_stack;
    public:
        bool next();
        bool loop();
        virtual void show_state();
};


#endif //DUNGEONCRAWLERCMAKE_ENGINE_H
