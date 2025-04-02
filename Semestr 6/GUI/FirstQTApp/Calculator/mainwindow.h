#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLineEdit>
#include <qobject.h>

#include "button.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow() = default;

private slots:
    void digitClicked();
    // void pointClicked();
    // void unaryOperationClicked();
    // void addOperatorClicked();
    // void multiplyOperatorClicked();
    // void equalClicked();
    // void changeSignClicked();
    // void backspaceClicked();
    // void clear();
    // void clearAll();
    // void clearMemory();
    // void readMemory();
    // void setMemory();
    // void addToMemory();


private:

    template<typename PointerToMemberFunction>
    Button *createButton(const QString &text, const PointerToMemberFunction &member);

    double memory;
    double sumSoFar;
    double factorSoFar;
    QString pendingAdditiveOperation;
    QString pendingMultiplicativeOperation;
    bool waitingForOperand;

    QLineEdit* display;

    enum {NumDigitButtons = 10};
    Button *digitButtons[NumDigitButtons];
};
#endif // MAINWINDOW_H
