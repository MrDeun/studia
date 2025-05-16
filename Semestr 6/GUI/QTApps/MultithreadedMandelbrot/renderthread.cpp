#include "renderthread.h"
#include "mandelbrotwidget.h"
#include <qobject.h>

RenderThread::RenderThread(QObject* parent): QThread(parent), _abort(false){

}

RenderThread::~RenderThread(){
    mutex.lock();
    _abort = true;
    condition.wakeOne();
    mutex.unlock();
    wait();
}