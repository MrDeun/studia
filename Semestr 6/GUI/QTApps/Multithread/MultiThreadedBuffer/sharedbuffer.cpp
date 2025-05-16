#include "sharedbuffer.h"
#include <qvariant.h>

SharedBuffer::SharedBuffer(QObject *parent,int maxSize,int interval_ms) : 
QObject{parent}, m_maxSize(maxSize), m_popInterval(interval_ms) 
{
  m_popTimer = new QTimer(this);
  connect(m_popTimer,&QTimer::timeout,this,&SharedBuffer::popChar);
  m_popTimer->setInterval(m_popInterval);
  m_popTimer->start();
}

void SharedBuffer::addChar(QChar c, int threadId) {
  m_mutex.lock();
    if(m_buffer.size() < m_maxSize){
  m_buffer.append(c);
  emit bufferUpdated(m_buffer);
  emit characterAdded(threadId, c);}
  m_mutex.unlock();
}

void SharedBuffer::setPopInterval(int ms) {
  m_popTimer->stop();
  m_popInterval = ms;
  m_popTimer->start(m_popInterval);
}

void SharedBuffer::popChar() {
  m_mutex.lock();
    if(!m_buffer.isEmpty()){
  auto copied_char = m_buffer[0];
  m_buffer.remove(0, 1);
  emit bufferUpdated(m_buffer);
  emit characterPopped(copied_char);
    }
  m_mutex.unlock();
}

void SharedBuffer::clear() {
  m_mutex.lock();
  m_buffer.clear();
  emit bufferUpdated(m_buffer);
  m_mutex.unlock();
}
