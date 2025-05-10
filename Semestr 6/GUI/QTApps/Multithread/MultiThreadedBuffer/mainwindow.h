#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QMutex>

#include "buffer.h"
#include "worker.h"

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
    void updateBuffer(const QString& buf);
    void addNewWorker();
    void deleteWorker();

private:
    Ui::MainWindow *ui;
    std::vector<Worker*> workers;
    SharedBuffer m_sharedbuffer;
};
#endif // MAINWINDOW_H
