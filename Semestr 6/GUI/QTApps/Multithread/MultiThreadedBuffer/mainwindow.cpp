#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow),popThread(new PopWorker(3000000,&m_sharedbuffer)),m_sharedbuffer(parent)

{
  ui->setupUi(this);
auto worker1 = addNewWorker("x", 1500);
auto worker2 = addNewWorker("y", 2000);
auto worker3 = addNewWorker("z", 4500);

connect(&m_sharedbuffer,&SharedBuffer::bufferUpdated,this,&MainWindow::updateBuffer);


workers.push_back(worker1);
workers.push_back(worker2);
workers.push_back(worker3);

worker1->start();
worker2->start();
worker3->start();

  popThread->start();
}

void MainWindow::updateBuffer(const QString &buf) {
    QMessageBox::warning(this,"",buf);
  ui->textEdit->setText(buf);
}

void MainWindow::addNewWorkerPressed() { 
    QString new_msg = ui->msgEdit->text();
    int _interval_ms = ui->speedEdit->text().toInt();
    Worker* new_worker = new Worker(new_msg,_interval_ms,&m_sharedbuffer);
    workers.push_back(new_worker);
    new_worker->start();
}

Worker* MainWindow::addNewWorker(QString c, int _interval_ms){
    Worker* new_worker = new Worker(c,_interval_ms, &m_sharedbuffer);
    return new_worker;
}

void MainWindow::setNewPopTimerPressed(){}

void MainWindow::deleteWorkerPressed(){
    delete *workers.end();
    workers.pop_back();
}

MainWindow::~MainWindow() {
  delete ui;
  delete popThread;
  for (auto w : workers) {
    delete w;
  }
}
