#include "shared_buffer.h"

SharedBuffer::SharedBuffer(QObject *parent, int maxSize, int popMs)
    : QObject(parent), m_maxSize(maxSize), m_popInterval(popMs)
{
    // Timer for popping characters
    m_popTimer = new QTimer(this);
    connect(m_popTimer, &QTimer::timeout, this, &SharedBuffer::popChar);
    m_popTimer->start(m_popInterval);
}

SharedBuffer::~SharedBuffer()
{
    // Timer will be deleted automatically as a child of this QObject
}

void SharedBuffer::addChar(QChar c, int threadId)
{
    QMutexLocker locker(&m_mutex);
    
    // Add the character to the buffer
    m_buffer.append(c);
    
    // Trim if needed
    if (m_buffer.length() > m_maxSize) {
        m_buffer.remove(0, m_buffer.length() - m_maxSize);
    }
    
    // Notify about the update
    emit bufferUpdated(m_buffer);
    emit characterAdded(threadId, c);
}

void SharedBuffer::popChar()
{
    QMutexLocker locker(&m_mutex);
    
    // Pop a character if buffer isn't empty
    if (!m_buffer.isEmpty()) {
        QChar poppedChar = m_buffer.at(0);
        m_buffer.remove(0, 1);
        
        // Notify about the update
        emit bufferUpdated(m_buffer);
        emit characterPopped(poppedChar);
    }
}

void SharedBuffer::clear()
{
    QMutexLocker locker(&m_mutex);
    m_buffer.clear();
    emit bufferUpdated(m_buffer);
}

void SharedBuffer::setPopInterval(int ms)
{
    m_popInterval = ms;
    m_popTimer->setInterval(ms);
}
