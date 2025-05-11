#ifndef CHARACTERWORKER_H
#define CHARACTERWORKER_H

#include <QObject>
#include <QTimer>
#include "shared_buffer.h"

class CharacterWorker : public QObject {
    Q_OBJECT

private:
    int m_id;
    QChar m_character;
    int m_interval;
    SharedBuffer *m_buffer;
    QTimer *m_timer;
    bool m_active;

public:
    CharacterWorker(int id, QChar character, SharedBuffer *buffer, int interval = 1000);
    ~CharacterWorker();

public slots:
    void start();
    void stop();
    void setInterval(int ms);

private slots:
    void generateCharacter();
};

#endif // CHARACTERWORKER_H
