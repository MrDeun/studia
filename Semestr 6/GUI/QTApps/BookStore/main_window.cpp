#include "main_window.h"
#include "./ui_bookstore.h"
#include <QtSql/qsqldatabase.h>
#include <QtSql/qsqlquery.h>
#include <QtSql/QSqlError>
#include <cassert>

BookStore::BookStore(QWidget *parent)
    : QMainWindow(parent),ui(new Ui::BookStore) {

    ui->setupUi(this);

    updateList();
}

void BookStore::deleteBookClicked(){
    qDebug() << "Delete book not implemented yet";
}
void BookStore::addBookClicked(){
    qDebug() << "Delete book not implemented yet";
}
void BookStore::borrowBookClicked(){
    qDebug() << "Delete book not implemented yet";
}
void BookStore::returnBookClicked(){
    qDebug() << "Delete book not implemented yet";
}


void BookStore::updateList(){
    {
    }
}

BookStore::~BookStore() {
    delete ui;
}
