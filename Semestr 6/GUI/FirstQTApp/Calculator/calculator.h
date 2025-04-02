#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QWidget>

class Calculator : public QWidget
{
    Q_OBJECT
public:
    explicit Calculator(QWidget *parent = nullptr);

    void executeCalculation();
    void addToMemory();
    
signals:
};

#endif // CALCULATOR_H
