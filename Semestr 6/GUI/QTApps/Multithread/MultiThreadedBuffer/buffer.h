#ifndef BUFFER_H
#define BUFFER_H

#include <QMutex>
#include <QObject>
#include <QThread>
class SharedBuffer : public QObject {
private:
  Q_OBJECT

  QString buffer;
  QMutex m_mutex;

  const int MAX_SIZE;

public:
  explicit SharedBuffer(QObject *parent = nullptr, int pop_ms = 3000);
  void receiveString(const QString &);
  void popChar();
  SharedBuffer *getSharedBuffer() { return this; }
signals:
  void bufferUpdated(const QString& buffer);
private slots:
  void clearBuffer();
};

#endif // BUFFER_H
