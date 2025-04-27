#ifndef BOOKREPOSITORY_H
#define BOOKREPOSITORY_H

#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QtSql>
#include <qlist.h>
#include <qsqldatabase.h>

#include "book.h"

namespace BookRepository {
  static int id_book = 0;
  void addBook(const QString& author, const QString& title);
  void removeBook(int id);
  Book getBookByID(int id);
  QList<Book> getAllBooks();
  
};

#endif // BOOKREPOSITORY_H
