#ifndef BORROWING_REPO
#define BORROWING_REPO

#include <QDate>
#include <QMessageBox>
#include <QSqlError>
#include <QSqlQuery>
#include <QString>
#include <qcontainerfwd.h>
#include <qdatetime.h>
#include <qmainwindow.h>
#include <qsqlquery.h>
#include <qvariant.h>

class Borrowing {
private:
  int id;
  int id_book;
  int id_person;
  QDate return_date;

public:
  const QDate borrow_date;
  const QDate due_date;
  Borrowing(int id, int id_book, int id_person, QString _return_date = "")
      : id(id), id_book(id_book), id_person(id_person),
        borrow_date(QDate::currentDate()),
        due_date(QDate::currentDate().addMonths(1)) {
    if (!_return_date.isEmpty()) {
      return_date = QDate::fromString(_return_date, "yyyy-MM-dd HH:mm:ss");
    } else {
        ;
    }
  }

  void bookReturned() { return_date = QDate::currentDate(); }
  int getID() const { return id; }
  int getBookID() const { return id_book; }
  int getPersonID() const { return id_person; }
};

namespace BorrowingRepository {
static int borrowing_id = 0;
void addNewBorrowing(QSqlQuery &q, int id_book, int id_person) {
  Borrowing new_borrow(++borrowing_id, id_book, id_person);
  QString query =
      QString(
          "INSERT INTO "
          "borrowings(id,id_person,id_book,borrow_date,due_date,return_date) "
          "VALUES(%1,%2,%3,'%4','%5',%6)")
          .arg(QString::number(new_borrow.getID()),
               QString::number(new_borrow.getPersonID()),
               QString::number(new_borrow.getBookID()),
               new_borrow.borrow_date.toString("yyyy-MM-dd HH:mm:ss"),
               new_borrow.due_date.toString("yyyy-MM-dd HH:mm:ss"), "NULL");
  if (!q.exec(query)) {
    QMessageBox::warning(nullptr, "Sql Error", q.lastError().text());
  }
}
void returnBorrowing(QSqlQuery& q,int id_borrowing) {
  QString query =
      QString("UPDATE borrowing SET return_date = '%1' where id = %2")
          .arg(QDate::currentDate().toString("yyyy-MM-dd HH:mm:ss"),
               QString::number(id_borrowing));
    if(!q.exec(query)){
        QMessageBox::warning(nullptr,"Sql Error",q.lastError().text());
    }
}

Borrowing getLatestBorrowByPersonID(QSqlQuery& q, int _id_person);
Borrowing getLatestBorrowByBookID(QSqlQuery& q, int _id_person);

}; // namespace BorrowingRepository

#endif
