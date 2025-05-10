#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

void MainWindow::updateBuffer(){
    ui->textEdit->setText(buf);
}

void MainWindow::delettionRequested(){
    m_mutex.lock();
    if(buf.size()!=0){
        buf.chop(1);
    }
    m_mutex.unlock();
}

void MainWindow::gotChar(QString c){
    m_mutex.lock();
    if(buf.size() < max_size){
        buf.append(c);
        updateBuffer();
    }
    m_mutex.unlock();
}

MainWindow::~MainWindow()
{
    delete ui;
}
