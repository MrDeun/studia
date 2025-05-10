#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

}

void MainWindow::updateBuffer(const QString& buf){
    ui->textEdit->setText(buf);
}

MainWindow::~MainWindow()
{
    delete ui;
    for (auto w : workers) {
        delete w;
    }
}
