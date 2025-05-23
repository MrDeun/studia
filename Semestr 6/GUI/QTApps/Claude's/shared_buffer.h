#ifndef SHAREDBUFFER_H
#define SHAREDBUFFER_H

#include <QObject>
#include <QMutex>
#include <QTimer>
#include <QString>

class SharedBuffer : public QObject {
    Q_OBJECT

private:
    QString m_buffer;
    QMutex m_mutex;
    int m_maxSize;
    int m_popInterval;  // Interval for auto-popping
    QTimer *m_popTimer;

public:
    explicit SharedBuffer(QObject *parent = nullptr, int maxSize = 1000, int popMs = 1000);
    ~SharedBuffer();

    void addChar(QChar c, int threadId);
    void setPopInterval(int ms);

public slots:
    void popChar();
    void clear();

signals:
    void bufferUpdated(const QString &buffer);
    void characterAdded(int threadId, QChar c);
    void characterPopped(QChar c);
};

#endif // SHAREDBUFFER_H
