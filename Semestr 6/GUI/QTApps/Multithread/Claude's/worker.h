#ifndef WORKER 
#define WORKER 
#include <QDateTime>
struct CharacterItem {
    QChar character;
    qint64 timestamp;
    
    CharacterItem(QChar c) : character(c), timestamp(QDateTime::currentMSecsSinceEpoch()) {}
};

class CharacterGenerator : public QObject
{
    Q_OBJECT

public:
    CharacterGenerator(SharedBuffer *buffer, int id)
        : m_buffer(buffer), m_id(id), m_active(false), m_interval(500)
    {
        // Set character range based on worker ID
        switch (m_id % 4) {
            case 0: // Lowercase letters
                m_minChar = 'a';
                m_maxChar = 'z';
                break;
            case 1: // Uppercase letters
                m_minChar = 'A';
                m_maxChar = 'Z';
                break;
            case 2: // Numbers
                m_minChar = '0';
                m_maxChar = '9';
                break;
            case 3: // Special characters
                m_minChar = '!';
                m_maxChar = '/';
                break;
        }

        m_timer = new QTimer(this);
        connect(m_timer, &QTimer::timeout, this, &CharacterGenerator::generateCharacter);
    }

    ~CharacterGenerator() {
        stop();
    }

public slots:
    void start() {
        if (!m_active) {
            m_active = true;
            m_timer->start(m_interval);
        }
    }

    void stop() {
        if (m_active) {
            m_active = false;
            m_timer->stop();
        }
    }

    void setInterval(int ms) {
        m_interval = ms;
        if (m_active) {
            m_timer->setInterval(ms);
        }
    }

private slots:
    void generateCharacter() {
        if (m_active) {
            // Generate a random character in our range
            QChar c = QChar(QRandomGenerator::global()->bounded(m_minChar, m_maxChar + 1));
            
            // Add to shared buffer
            m_buffer->addChar(c);
            
            emit characterGenerated(m_id, c);
        }
    }

signals:
    void characterGenerated(int workerId, QChar c);

private:
    SharedBuffer *m_buffer;
    int m_id;
    bool m_active;
    int m_interval;
    QTimer *m_timer;
    ushort m_minChar;
    ushort m_maxChar;
};

#endif