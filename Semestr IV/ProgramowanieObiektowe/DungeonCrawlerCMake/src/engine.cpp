//
// Created by pmich on 4/19/2024.
//

#include "engine.h"


bool engine::next(){
    if (!labyrinth_queue.empty()){
        labyrinth_queue.pop();
        return true;
    }
    return false;
}

void engine::loop() {
    while(next()){
        labyrinth current_labyrinth = labyrinth_queue.front();
        while(!current_labyrinth.is_finished()){
            int input = getch();
            labyrinth_queue.front().event(input);
        }
        labyrinth_queue.pop();
    }
}

bool engine::construct_labyrinths(const char *filename) {
    std::unique_ptr<std::ofstream> ptr_filestream
        = std::make_unique<std::ofstream>(filename);
    size_t laby_count;
    file_stream >> laby_count;
    for (size_t i = 0;i<laby_count;i++){
        size_t size_x, size_y;
        file_stream >> size_x >> size;
        labyrinth new_labyrinth;
        new_labyrinth.construct();
        labyrinth_queue.push(new_labyrinth);
    }

}