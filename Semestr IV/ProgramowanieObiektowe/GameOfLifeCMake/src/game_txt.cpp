//
// Created by pmich on 4/13/2024.
//

#include "game_txt.h"

void clear_screen(){
   //std::cout << "\033[2J\033[1;1H";
    system("cls");
   return;
}

void delay(){
    time_t begin = clock();
    while(begin + 10 >= clock()){
        continue;
    }
}
void game_txt::show_table() {
    clear_screen();
    for (int id_y = 0; id_y < get_size_y(); ++id_y) {
        for (int id_x = 0; id_x < get_size_x(); ++id_x) {
            char symbol = get_cell(id_x, id_y) ? '#' : '_';
            std::cout << symbol;
        }
        std::cout << '\n';
    }
}

void game_txt::loop() {
    while(true) {
        show_table();
        next_stage();
        delay();
    }
}

void game_txt::start() {
    for (int id_y = 0; id_y < get_size_y(); ++id_y) {
        for (int id_x = 0; id_x < get_size_x(); ++id_x) {
            set_state(id_x,id_y);
        }
    }
    loop();
}