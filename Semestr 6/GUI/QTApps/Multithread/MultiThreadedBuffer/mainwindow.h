#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QMutex>

#include "buffer.h"
#include "pop_thread.h"
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
    void addNewWorkerPressed();
    void deleteWorkerPressed();
    void setNewPopTimerPressed();

private:
    Worker* addNewWorker(QString c, int _interval_ms);
    void setNewPopTimer(int _interval_ms);
    Ui::MainWindow *ui;
    std::vector<Worker*> workers;
    PopWorker* popThread;
    SharedBuffer m_sharedbuffer;
};
#endif // MAINWINDOW_H
