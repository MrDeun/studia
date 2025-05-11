#include "pop_thread.h"
#include <iostream>
void PopWorker::run(){
    while(!isInterruptionRequested()){
        buf->popChar();
        std::cout << QString("Popped character out of buffer\n").toStdString();
        msleep(interval_ms);
    }
}
