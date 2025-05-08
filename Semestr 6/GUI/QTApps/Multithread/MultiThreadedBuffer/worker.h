#ifndef WORKER_H
#define WORKER_H

#include <QThread>
#include <QMutex>
#include <qcontainerfwd.h>

class Worker : public QThread
{
    Q_OBJECT
public:
    explicit Worker(QString _id, int _time, QObject *parent = 0, int bufferSize=0, QVector<QString>* bufRef=nullptr);

protected:
    void run() override;

    QString id_;    //ID of thread
    int time_;      //sleep time for the thread

    const int bufferSize;
    const QVector<QString>& vecRef;

    static QMutex mutex_;   //we will synchronize threads using mutex
signals:

public slots:

};


#endif // WORKER_H
