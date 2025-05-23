#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTextEdit>
#include <QSpinBox>
#include <QThread>
#include <QList>
#include "shared_buffer.h"
#include "worker.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

private:
    SharedBuffer *m_buffer;
    std::vector<QThread*> m_threads;
    std::vector<CharacterWorker*> m_workers;
    QTextEdit *m_bufferDisplay;
    QTextEdit *m_logDisplay;
    QSpinBox *m_generateIntervalSpinBox;
    QSpinBox *m_popIntervalSpinBox;
    
    const QList<QChar> CHARACTERS = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H'};

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void addThread();
    void removeThread();
    void updatePopInterval(int ms);
    void updateBufferDisplay(const QString &buffer);
    void logCharacterAdded(int threadId, QChar c);
    void logCharacterPopped(QChar c);
    void logMessage(const QString &message);
};

#endif // MAINWINDOW_H
