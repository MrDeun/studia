#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "deletion_worker.h"
#include <QMainWindow>
#include <QMutex>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void updateBuffer();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
