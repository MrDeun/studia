#ifndef BOOKREPOSITORY_H
#define BOOKREPOSITORY_H

#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QtSql>
#include <qlist.h>
#include <qsqldatabase.h>

#include "book.h"

class BookRepository {
private:
  QSqlDatabase m_db;

public:
  BookRepository();
  void add(Book book);
  void remove(int id);
  Book getBookByID(int id);
  QList<Book> getAll();
  QList<Book> getBookByTitle(const QString& title);
  
};

#endif // BOOKREPOSITORY_H
