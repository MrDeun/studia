#ifndef POP_WORKER
#define POP_WORKER

#include <QThread>
#include <QTimer>
#include <qobject.h>

#include "buffer.h"

class PopWorker : public QThread {
    Q_OBJECT
public:
    PopWorker(int interval_ms, SharedBuffer* _buf):interval_ms(interval_ms),buf(_buf){}
    ~PopWorker() = default;
public slots:
    void run() override;
private:
    int interval_ms;
    SharedBuffer* buf;
    // add your variables here
};
#endif
