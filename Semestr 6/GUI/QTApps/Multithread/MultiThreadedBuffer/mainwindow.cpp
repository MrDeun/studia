#include "mainwindow.h"
#include "sharedbuffer.h"
#include "ui_mainwindow.h"
#include "worker.h"

#include <QThread>
#include <QObject>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow),
    m_buffer(this)
    
{
    ui->setupUi(this);
    m_bufferDisplay = ui->lineEdit;
    m_speedEdit = ui->lineEdit_2;
    m_messageEdit = ui->lineEdit_3;

    m_progressBar = ui->progressBar;
    m_popIntervalSpinBox = ui->doubleSpinBox;

    connect(&m_buffer,&SharedBuffer::bufferUpdated,this,&MainWindow::updateBufferDisplay);
}

void MainWindow::AddThread(){
    QString msg = m_messageEdit->text();
    int interval = m_speedEdit->text().toInt();

    auto thread = new QThread(this);
    auto worker = new Worker(nullptr,m_workers.size(),msg[0],interval,&m_buffer);

    worker->moveToThread(thread);

    connect(thread,&QThread::started,worker,&Worker::start);
    connect(thread,&QThread::finished,worker,&Worker::deleteLater);

    m_threads.append(thread);
    m_workers.append(worker);

    thread->start();
}
void MainWindow::RemoveThread(){
    if(!m_threads.isEmpty()){
        int id = m_threads.size() - 1;

        m_workers[id]->stop();

        m_threads[id]->quit();
        m_threads[id]->wait();

        delete m_threads.takeLast();
        delete m_workers.takeLast();

    }
}
void MainWindow::updateGenerateInterval(int ms){
    // does nothing
}
void MainWindow::updatePopInterval(double ms){
    m_buffer.setPopInterval(int(ms));
}
void MainWindow::updateBufferDisplay(const QString &buffer){
    m_bufferDisplay->setText(buffer);
    m_progressBar->setValue((double)buffer.size()/double(m_buffer.getMaxSize()));
}
void MainWindow::logCharacterAdded(int threadId, QChar c){}
void MainWindow::logCharacterPopped(QChar c){}
void MainWindow::logMessage(const QString& msg){}

MainWindow::~MainWindow()
{
    delete ui;
    qDeleteAll(m_workers);
    qDeleteAll(m_threads);
}
