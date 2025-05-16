#include "worker.h"
#include <cassert>

Worker::Worker(int id, QChar c, int ms, SharedBuffer *buf)
    : QThread{nullptr}, m_character(c), m_id(id), m_timer(parent),
      m_interval(ms), m_active(false) {
        assert(buf);
        m_timer.setInterval(m_interval);
        connect(&m_timer,&QTimer::timeout,this,&Worker::generateCharacter);
      }



void Worker::setInterval(int ms) {}

void Worker::generateCharacter() {
  while (m_active) {
    m_buffer->addChar(m_character, m_id);
  }
}
