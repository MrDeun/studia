#include "worker.h"
#include "buffer.h"

#include <iostream>

void Worker::run(){
    while(!isInterruptionRequested()){
        buf->receiveString(msg);
        std::cout << QString("Send out: %1\n").arg(msg).toStdString();
        msleep(interval_ms);
    }
}
