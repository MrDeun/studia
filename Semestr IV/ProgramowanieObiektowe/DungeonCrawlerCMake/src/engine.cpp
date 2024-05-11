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
    ptr_filestream->getline();
    for (size_t i = 0;i<laby_count;i++){
        size_t size_x, size_y;
        file_stream >> size_x >> size_y;
        labyrinth new_labyrinth(size_x,size_x);
        new_labyrinth.construct(ptr_filestream.get());
        labyrinth_queue.push(new_labyrinth);
    }

}