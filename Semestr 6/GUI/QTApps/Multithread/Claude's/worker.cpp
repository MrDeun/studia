#include "worker.h"

CharacterWorker::CharacterWorker(int id, QChar character, SharedBuffer *buffer, int interval)
    : m_id(id), m_character(character), m_interval(interval), 
      m_buffer(buffer), m_active(false)
{
    m_timer = new QTimer(this);
    connect(m_timer, &QTimer::timeout, this, &CharacterWorker::generateCharacter);
}

CharacterWorker::~CharacterWorker()
{
    stop();
    // Timer will be deleted automatically as a child of this QObject
}

void CharacterWorker::start()
{
    m_active = true;
    m_timer->start(m_interval);
}

void CharacterWorker::stop()
{
    m_active = false;
    m_timer->stop();
}

void CharacterWorker::setInterval(int ms)
{
    m_interval = ms;
    if (m_active) {
        m_timer->setInterval(ms);
    }
}

void CharacterWorker::generateCharacter()
{
    if (m_active) {
        m_buffer->addChar(m_character, m_id);
    }
}
