#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTextEdit>
#include <QLineEdit>
#include <QProgressBar>
#include <QDoubleSpinBox>

namespace Ui {
class MainWindow;
}

#include "sharedbuffer.h"
#include "worker.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private slots:
    void AddThread();
    void RemoveThread();
    void updateGenerateInterval(int ms);
    void updatePopInterval(double);
    void updateBufferDisplay(const QString &buffer);
    void logCharacterAdded(int threadId, QChar c);
    void logCharacterPopped(QChar c);
    void logMessage(const QString& msg);


private:
    Ui::MainWindow *ui;

    SharedBuffer m_buffer;
    QList<QThread*> m_threads;
    QList<Worker*> m_workers;

    QLineEdit* m_bufferDisplay; 
    QLineEdit* m_speedEdit ;
    QLineEdit* m_messageEdit;


    QProgressBar* m_progressBar;
    QDoubleSpinBox* m_popIntervalSpinBox;


};

#endif // MAINWINDOW_H
