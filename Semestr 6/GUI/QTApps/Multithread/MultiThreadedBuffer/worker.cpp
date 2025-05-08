#include "worker.h"
#include <cassert>

Worker::Worker(QString _id, int _time, QObject *parent, int bufferSize,
               QVector<QString> *bufPtr)
    : QThread{parent}, id_(_id), time_(_time),bufferSize(bufferSize) {
  assert(bufPtr);

}

void Worker::run() {
  while (!isInterruptionRequested()) {
  }
}
