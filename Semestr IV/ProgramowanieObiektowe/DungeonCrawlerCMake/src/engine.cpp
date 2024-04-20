//
// Created by pmich on 4/19/2024.
//

#include "engine.h"


bool engine::next(){
    if (!queue_stack.empty()){
        queue_stack.pop();
        return true;
    }
    return false;
}

bool engine::loop() {

}