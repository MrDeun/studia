#include "borrowing_repository.h"


void BorrowingRepository::addNewBorrowing(QSqlQuery &q, int id_book, int id_person) {
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

std::vector<Borrowing> Borrowing::getBorrowsByPersonID(QSqlQuery& q, int _id_person){
  QString query = QString("SELECT * from BORROWING where id_person = %1 and return_date = NULL").arg(QString::number(_id_person));
  if(!q.exec(query)){
    QMessageBox::warning(nullptr,"Sql Error",q.lastError().text());
  }
  std::vector<Borrowing> borrows{};
  while(q.next()){
    int id = q.value(0).toInt();
    int id_person = q.value(1).toInt();
    int id_book = q.value(2).toInt();
    QDate borrow_date = q.value(3).toDate();
    QDate due_date = q.value(4).toDate();

    Borrowing temp_borrow(id,id_book,id_person);
    borrows.push_back(temp_borrow);
  }
  return borrows;
}
Borrowing* BorrowingRepository::getLatestBorrowByBookID(QSqlQuery& q, int _id_book){
  QString query = QString("SELECT * from BORROWING where id_book = %1 and return_date = NULL").arg(QString::number(_id_book));
  if(!q.exec(query)){
    QMessageBox::warning(nullptr,"Sql Error",q.lastError().text());
  }
  while(q.next()){
    int id = q.value(0).toInt();
    int id_person = q.value(1).toInt();
    int id_book = q.value(2).toInt();
    QDate borrow_date = q.value(3).toDate();
    QDate due_date = q.value(4).toDate();

    return new Borrowing(id,id_book,id_person,borrow_date,due_date);
  }
  return nullptr;
}

 // namespace BorrowingRepository


