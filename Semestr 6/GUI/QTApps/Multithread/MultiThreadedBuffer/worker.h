#ifndef WORKER
#define WORKER

#include <QThread>
#include <QTimer>
#include <qobject.h>

class Worker : public QThread {
    Q_OBJECT
public:
    Worker(QString msg, int interval_ms):msg(msg),interval_ms(interval_ms){}
    ~Worker();
public slots:
    void run(SharedBuffer* buf) override;
signals:
    void finished();
    void error(QString err);
private:
    QString msg;
    int interval_ms;
    // add your variables here
};
#endif
