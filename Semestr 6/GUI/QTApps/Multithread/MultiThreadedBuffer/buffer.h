#ifndef BUFFER_H
#define BUFFER_H

#include <QObject>

class SharedBuffer: public QObject
{
private:
    Q_OBJECT
public:
    explicit SharedBuffer(QObject *parent = nullptr);

signals:
};

#endif // BUFFER_H
