#ifndef BUFFER 
#define BUFFER

#include <QObject>
#include <qtmetamacros.h>

class SharedBuffer : public QObject{
    Q_OBJECT
    private:
        const int size;
        const int buffer_timeout;
    public:


};

#endif