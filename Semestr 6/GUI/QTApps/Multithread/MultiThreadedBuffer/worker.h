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
  explicit Worker(QObject *parent = nullptr, int i=-1,QChar c = '?', int ms = 1000,
                  SharedBuffer *buf = nullptr);
public slots:
  void run() override;
  void setInterval(int ms);
private slots:
  void generateCharacter();
};

#endif // WORKER_H
