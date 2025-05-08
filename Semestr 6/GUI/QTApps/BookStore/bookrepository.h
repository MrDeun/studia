#ifndef BOOKREPOSITORY_H
#define BOOKREPOSITORY_H

#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QtSql>
#include <qsqldatabase.h>
#include <qsqlquery.h>
#include <vector>

#include "book.h"

namespace BookRepository {
static int id_book = 0;
void addBook(QSqlQuery &q, const QString &author, const QString &title);
void removeBook(QSqlQuery &q, int id);
Book getBookByID(QSqlQuery &q, int id);
std::vector<Book> getAllBooks(QSqlQuery &q);
std::vector<Book> getAvailableBooks(QSqlQuery &q);

}; // namespace BookRepository

#endif // BOOKREPOSITORY_H
