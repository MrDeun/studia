#include "buffer.h"
#include <qmutex.h>

SharedBuffer::SharedBuffer(QObject *parent, int max_size)
    : QObject{parent},
    MAX_SIZE(max_size)
{

}

void SharedBuffer::popChar(){
    m_mutex.lock();
    if(buffer.size() != 0) {
        buffer.chop(1);
        emit bufferUpdated(buffer);
    }
    m_mutex.unlock();
}

void SharedBuffer::receiveString(const QString& c){
    m_mutex.lock();
    if(MAX_SIZE < buffer.size()){
    buffer.append(c);
        emit bufferUpdated(buffer);}
    m_mutex.unlock();
}

void SharedBuffer::clearBuffer(){
    m_mutex.lock();
    if(buffer.size()!=0) {
        buffer.clear();
        emit bufferUpdated(buffer);
    }
    m_mutex.unlock();
}
