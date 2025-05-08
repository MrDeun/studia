#include "main_window.h"
#include "./ui_bookstore.h"
#include <QDialog>
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <cassert>
#include <qdialog.h>
#include <qsqlquery.h>

#include "addbookdialog.h"
#include "addpersondialog.h"
#include "borrowbookdialog.h"
#include "returnbookdialog.h"

#include "bookrepository.h"
#include "borrowing_repository.h"
#include "personrepository.h"

#define INVALID_VIEW false

BookStore::BookStore(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::BookStore), currentView(BOOKS) {
  ui->setupUi(this);
  initDB();
  switchedTab();
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
    currentView = PERSONS;
    updateList();
  }
}
void BookStore::deletePersonClicked() {
  QSqlQuery q(db);
  if (!currentPerson) {
    QMessageBox::warning(nullptr, "BookStore error", "No person is selected");
    return;
  }
  PersonRepository::deletePerson(q, currentPerson->getID());
  currentView = PERSONS;
  updateList();
}
void BookStore::deleteBookClicked() {
  QSqlQuery q(db);
  if (!currentBook) {
    QMessageBox::warning(nullptr, "BookStore error", "No book selected!");
    return;
  }
  BookRepository::removeBook(q, currentBook->getID());
  currentView = BOOKS;
  updateList();
  return;
}
void BookStore::addBookClicked() {
  AddBookDialog dialog(this);
  if (dialog.exec() == QDialog::Accepted) {
    QString title = dialog.getTitle();
    QString author = dialog.getAuthor();

    QSqlQuery q(db);
    BookRepository::addBook(q, author, title);
    currentView = BOOKS;
    updateList();
  }
}
void BookStore::borrowBookClicked() {
  QSqlQuery q(db);
  auto availableBooks = BookRepository::getAvailableBooks(q);
  auto persons = PersonRepository::getAllPersons(q);
  BorrowBookDialog dialog(this);
  dialog.setContainers(&availableBooks, &persons);
  if (dialog.exec() == QDialog::Accepted) {
    int id_book = dialog.getBookID();
    int id_person = dialog.getPersonID();
    BorrowingRepository::addNewBorrowing(q, id_book, id_person);
  }
}
void BookStore::returnBookClicked() {
  QSqlQuery q(db);
  auto currentBorrows = BorrowingRepository::getAllActiveBorrows(q);
  ReturnBookDialog dialog(this);
  dialog.setBorrows(&currentBorrows, q);
  if (dialog.exec() == QDialog::Accepted) {
    int id_borrow = dialog.getIndex();
    BorrowingRepository::returnBook(q, id_borrow);
  }
}

void BookStore::switchedTab() {
  if (ui->radioButton->isChecked()) {
    currentView = PERSONS;
    ui->pushButton_2->setDisabled(true);
    ui->pushButton_3->setDisabled(true);
    ui->pushButton_6->setDisabled(false);
    ui->pushButton_7->setDisabled(false);
  } else {
    currentView = BOOKS;
    ui->pushButton_2->setDisabled(false);
    ui->pushButton_3->setDisabled(false);
    ui->pushButton_6->setDisabled(true);
    ui->pushButton_7->setDisabled(true);
  }
  updateList();
}

void BookStore::updateInfoField() {
  QString info = "";
  QSqlQuery q(db);
  switch (currentView) {
  case PERSONS: {
      if(currentPerson == nullptr){
          ui->textEdit->clear();
          return;
      }
    auto borrowed_books =
        BorrowingRepository::getBorrowsByPersonID(q, currentPerson->getID());

    info.append(QString("Name: %1\n").arg(currentPerson->getName()));
    info.append(QString("Surname: %1\n").arg(currentPerson->getSurname()));
    info.append(
        QString("Phone Number: %1\n").arg(currentPerson->getPhoneNumber()));
    info.append(QString("Email: %1\n").arg(currentPerson->getEmail()));
    info.append(QString("Current borrowed books: \n"));
    if (borrowed_books.empty()) {
      info.append(" - NONE\n");
    } else {
      for (const auto &borrow : borrowed_books) {
        Book b = BookRepository::getBookByID(q, borrow.getBookID());
        QString missing_books_str = QString(" - \"%1\"  by %2 due to %3\n")
                                        .arg(b.getTitle(), b.getAuthor(),
                                             borrow.getDueDate().toString());
        info.append(missing_books_str);
      }
    }

    break;
  }
  case BOOKS: {
      if(currentBook == nullptr){
          ui->textEdit->clear();
          return;
      }
    info.append(QString("Title: %1\n").arg(currentBook->getTitle()));
    info.append(QString("Author: %2\n").arg(currentBook->getAuthor()));
    auto latestEntry =
        BorrowingRepository::getLatestBorrowByBookID(q, currentBook->getID());
    if (latestEntry) {
      QString borrowed_by_str = "Borrowed by: %1";
      Person p = PersonRepository::getPerson(q, latestEntry->getPersonID());
      borrowed_by_str =
          borrowed_by_str.arg(p.getName() + " " + p.getSurname() + "\n");
      info.append(borrowed_by_str);
      delete latestEntry;
    } else {
      info.append(QString("Avainble for borrowing!\n"));
    }
    break;
  }
  default:
    assert(INVALID_VIEW);
  }
  ui->textEdit->setText(info);
}

void BookStore::clickedElementOfList() {
  int startPos, stopPos, length, index_num;
  currentPerson = nullptr;
  currentBook = nullptr;
  if (ui->listWidget->currentItem()->text() == "-- NONE --") {
    ui->textEdit->clear();
    return;
  }
  if (currentView == PERSONS) {
    auto nameSurname = ui->listWidget->currentItem()->text();
    startPos = nameSurname.lastIndexOf('(') + 1;
    stopPos = nameSurname.lastIndexOf(')');
    length = stopPos - startPos;
    index_num = nameSurname.mid(startPos, length).toInt();
    for (auto &p : persons) {
      if (p.getID() == index_num) {
        currentPerson = &p;
        ui->textEdit->setText(currentPerson->getName());
        break;
      }
    }
  } else {
    auto title = ui->listWidget->currentItem()->text();
    startPos = title.lastIndexOf('(') + 1;
    stopPos = title.lastIndexOf(')');
    length = stopPos - startPos;
    index_num = title.mid(startPos, length).toInt();
    for (auto &b : books) {
      if (b.getID() == index_num) {
        currentBook = &b;
        ui->textEdit->setText(currentBook->getTitle());
        break;
      }
    }
  }
  updateInfoField();
}

void BookStore::updateList() {
  QSqlQuery q(db);
  ui->listWidget->clear();
  ui->listWidget->addItem("-- NONE --");
  if (currentView == PERSONS) {
    persons = PersonRepository::getAllPersons(q);
    for (const auto &p : persons) {
      QString fullName = "";
      fullName.append(p.getName());
      fullName.append(QString(" (%1)").arg(QString::number(p.getID())));
      ui->listWidget->addItem(fullName);
    }
    ui->listWidget->show();
  } else {
    books = BookRepository::getAllBooks(q);
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
