#include "main_window.h"
#include "./ui_bookstore.h"
#include "addbookdialog.h"
#include "init_database.h"
#include "personrepository.h"
#include <QtSql/qsqldatabase.h>
#include <QtSql/qsqlquery.h>
#include <QtSql/QSqlError>
#include <QMessageBox>
#include <cassert>
#include <qdialog.h>

BookStore::BookStore(QWidget *parent)
    : QMainWindow(parent),ui(new Ui::BookStore) {
    initDB();
    ui->setupUi(this);
    updateList();
}
void BookStore::addPersonClicked(){
    AddBookDialog dialog(this);
    if(dialog.exec() == QDialog::Accepted){
        QString name = dialog.getName();
        QString surname = dialog.getSurname();
        QString phone_number = dialog.getPhoneNumber();
        QString email = dialog.getEmail();

        QSqlQuery q(db);
        PersonRepository::addPerson(q,name, surname, phone_number, email);
    }
}
void BookStore::deletePersonClicked(){
    qDebug() << "Delete book not implemented yet";
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

void BookStore::switchedTab(){
    if(ui->radioButton->isChecked()){
        currentView = PERSONS;
    } else {
        currentView = BOOKS;
    }
    updateList();
}

void BookStore::clickedElementOfList(){
    qDebug() << "Delete book not implemented yet";
}


void BookStore::updateList(){
    // if (currentView == PERSONS) {
        QSqlQuery q(db);
        auto persons = PersonRepository::getAllPersons(q);
        ui->listWidget->clear();
        for (const auto& p : persons) {
            QString fullName = "";
            fullName.append(p.getName());
            fullName.append(p.getSurname());
            ui->listWidget->addItem(fullName);
        }
    // }
}

BookStore::~BookStore() {
    delete ui;
}

void BookStore::initDB() {
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(":memory:");
    if (!db.open()) {
      {
        QMessageBox::warning(nullptr, "Sql Error",
                             "Database failed to initialize");
        assert(false);
      }
    }
  
    QSqlQuery q(db);
  
    //TODO: Add query for creating BOOKS table
    if (!q.exec("")) {
      QMessageBox::warning(nullptr, "Sql Error", q.lastError().text());
      assert(false);
    }
    if (!q.exec("CREATE TABLE IF NOT EXISTS PERSONS (id integer primary key, name text, surname text, phone_number text, email text);")) {
      QMessageBox::warning(nullptr, "Sql Error", q.lastError().text());
      assert(false);
    }
    //TODO: Add query for creating BORROWING tables
    if (!q.exec((""))) {
      QMessageBox::warning(nullptr, "Sql Error", q.lastError().text());
      assert(false);
    }
  
    return ;
  }
