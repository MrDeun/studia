#include "main_window.h"
#include "./ui_bookstore.h"
#include "addbookdialog.h"
#include "addpersondialog.h"
#include "bookrepository.h"
#include "person.h"
#include <QDialog>
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <cassert>
#include <qdialog.h>
#include <qsqlquery.h>

#include "bookrepository.h"
#include "borrowing_repository.h"
#include "personrepository.h"

BookStore::BookStore(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::BookStore), currentView(BOOKS) {
  ui->setupUi(this);
  initDB();
  updateList();
}

void BookStore::addPersonClicked() {
  AddPersonDialog dialog(this);
  if (dialog.exec() == QDialog::Accepted) {
    QString name = dialog.getName();
    QString surname = dialog.getSurname();
    QString phone_number = dialog.getPhoneNumber();
    QString email = dialog.getEmail();

    QSqlQuery q(db);
    PersonRepository::addPerson(q, name, surname, phone_number, email);
  }
}
void BookStore::deletePersonClicked() {
  QSqlQuery q(db);
  if (!currentPerson) {
    QMessageBox::warning(nullptr, "BookStore error", "No person is selected");
    return;
  }
  PersonRepository::deletePerson(q, currentPerson->getID());
  updateList();
}
void BookStore::deleteBookClicked() {
  QSqlQuery q(db);
  if (!currentBook) {
    QMessageBox::warning(nullptr, "BookStore error", "No book selected!");
    return;
  }
  BookRepository::removeBook(q, currentBook->getID());
  updateList();
  return;
}
void BookStore::addBookClicked() {
    AddBookDialog dialog(this);
    if(dialog.exec() == QDialog::Accepted){
        QString title = dialog.getTitle();
        QString author = dialog.getAuthor();

        QSqlQuery q(db);
        BookRepository::addBook(q, author, title);
    }
}
void BookStore::borrowBookClicked() {
  qDebug() << "Delete book not implemented yet";
}
void BookStore::returnBookClicked() {
  qDebug() << "Delete book not implemented yet";
}

void BookStore::switchedTab() {
  if (ui->radioButton->isChecked()) {
    currentView = PERSONS;
  } else {
    currentView = BOOKS;
  }
  updateList();
}

void BookStore::clickedElementOfList() {
  currentPerson = nullptr;
  currentBook = nullptr;
  if (currentView == PERSONS) {
    auto nameSurname = ui->listWidget->currentItem()->text();
    for (auto &p : persons) {
      if (p.getName() + " " + p.getSurname() == nameSurname) {
        currentPerson = &p;
        break;
      }
    }
  } else {
    auto title = ui->listWidget->currentItem()->text();
    for (auto &b : books) {
      if (b.getTitle() == title) {
        currentBook = &b;
      }
    }
  }
}

void BookStore::updateList() {
  QSqlQuery q(db);
  if (currentView == PERSONS) {
    persons = PersonRepository::getAllPersons(q);
    ui->listWidget->clear();
    for (const auto &p : persons) {
      QString fullName = "";
      fullName.append(p.getName());
      fullName.append(QString(" (%1)").arg(QString::number(p.getID())));
      ui->listWidget->addItem(fullName);
    }
    ui->listWidget->show();
  } else {
    books = BookRepository::getAllBooks(q);
    ui->listWidget->clear();
    for (const auto &b : books) {
      QString fullName = "";
      fullName.append(b.getTitle());
      fullName.append(QString(" (%1)").arg(QString::number(b.getID())));
      ui->listWidget->addItem(fullName);
    }
    ui->listWidget->show();
  }
  currentPerson = nullptr;
  currentBook = nullptr;
}

BookStore::~BookStore() { delete ui; }

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

  // TODO: Add query for creating BOOKS table
  if (!q.exec("CREATE TABLE IF NOT EXISTS books (id integer primary key, title "
              "text, author text);")) {
    QMessageBox::warning(nullptr, "Sql Error", q.lastError().text());
    assert(false);
  }
  if (!q.exec("CREATE TABLE IF NOT EXISTS persons (id integer primary key, "
              "name text, surname text, phone_number text, email text);")) {
    QMessageBox::warning(nullptr, "Sql Error", q.lastError().text());
    assert(false);
  }
  // TODO: Add query for creating BORROWING tables
  if (!q.exec(("CREATE TABLE IF NOT EXISTS borrowings (id integer primary key, "
               "id_person integer not null, id_book integer not null, "
               "borrow_date text "
               "NOT null, due_date text not NULL, return_date text);"))) {
    QMessageBox::warning(nullptr, "Sql Error", q.lastError().text());
    assert(false);
  }

  PersonRepository::addPerson(q, "Jan", "Kowalski", "123456789",
                              "no@thank.you");
  PersonRepository::addPerson(q, "Stefan", "Nowak", "123456789",
                              "no@thank.you");
  PersonRepository::addPerson(q, "Jane", "Doe", "272785461", "no@thank.you");
  PersonRepository::addPerson(q, "Maciej", "Stanowski", "489216872",
                              "no@thank.you");

  BookRepository::addBook(q, "Sapkowski", "Witcher");
  BookRepository::addBook(q, "J.K. Rowling", "Harry Potter");

  BorrowingRepository::addNewBorrowing(q, 1, 3);
  BorrowingRepository::addNewBorrowing(q, 2, 3);

  return;
}
