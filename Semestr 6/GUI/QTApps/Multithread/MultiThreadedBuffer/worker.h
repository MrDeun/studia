#ifndef WORKER_H
#define WORKER_H

#include <QThread>
#include <QTimer>

#include "sharedbuffer.h"

class Worker : public QThread {
  Q_OBJECT
private:
  int m_id;
  QChar m_character;
  int m_interval;
  SharedBuffer *m_buffer;
  QTimer m_timer;
  bool m_active;

public:
  explicit Worker(QObject *parent = nullptr, int id = -1, QChar c = '?',
                  int ms = 1000, SharedBuffer *buf = nullptr);
  void stop() {
    m_active = true;
    m_timer.start(m_interval);
  }
  void start() {
    m_active = false;
    m_timer.stop();
  }
public slots:
  // void run() override;
  void setInterval(int ms);

private:
  void generateCharacter();
};

#endif // WORKER_H
