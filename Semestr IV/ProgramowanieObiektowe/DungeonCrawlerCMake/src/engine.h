//
// Created by pmich on 4/19/2024.
//

#ifndef DUNGEONCRAWLERCMAKE_ENGINE_H
#define DUNGEONCRAWLERCMAKE_ENGINE_H

#include "labyrinth.h"
#include <queue>
#include <conio.h>
#include <fstream>
#include <memory>
class engine {
    private:
        std::queue<labyrinth> labyrinth_queue;
    public:
        bool construct_labyrinths(const char* filename);
        bool next();
        void loop();
        virtual void show_state();
};


#endif //DUNGEONCRAWLERCMAKE_ENGINE_H
