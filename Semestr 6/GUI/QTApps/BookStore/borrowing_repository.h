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
#include <qmessagebox.h>
#include <qsqlquery.h>
#include <qvariant.h>
#include <vector>

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
        } else {}
      }
      Borrowing(int id, int id_book,int id_person, QDate borrow_date, QDate due_date):
      id(id),id_book(id_book),id_person(id_person),borrow_date(borrow_date),due_date(due_date){}

      void bookReturned() { return_date = QDate::currentDate(); }
      int getID() const { return id; }
      int getBookID() const { return id_book; }
      int getPersonID() const { return id_person; }
      QDate getDueDate() const {return due_date;}
      QDate getBorrowDate() const {return borrow_date;}
    };

    namespace BorrowingRepository {
        static int borrowing_id = 0;
        void addNewBorrowing(QSqlQuery& q, int id_book, int id_person);
        std::vector<Borrowing> getAllActiveBorrows(QSqlQuery& q);
        std::vector<Borrowing> getBorrowsByPersonID(QSqlQuery& q, int _id_person);
        Borrowing* getLatestBorrowByBookID(QSqlQuery& q, int _id_book);
        void returnBook(QSqlQuery& q, int id_borrowing);
    };

#endif
