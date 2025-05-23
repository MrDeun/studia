#include "bookrepository.h"
#include <QMessageBox>
#include <QString>
#include <qsqlquery.h>
#include <vector>

std::vector<Book> BookRepository::getAvailableBooks(QSqlQuery &q) {
  QString query =
      "SELECT b.* FROM books b WHERE b.id NOT IN (SELECT br.id_book FROM "
      "borrowings br WHERE br.return_date IS NULL);";
  if (!q.exec(query)) {
    QMessageBox::warning(nullptr, "Sql Error", q.lastError().text());
    return std::vector<Book>();
  }
  std::vector<Book> books = {};
  while (q.next()) {
    int id = q.value(0).toInt();
    QString title = q.value(1).toString();
    QString author = q.value(2).toString();

    Book b(id, author, title);
    books.push_back(b);
  }
  return books;
}

void BookRepository::addBook(QSqlQuery &q, const QString &author,
                             const QString &title) {
  const auto query =
      QString("INSERT INTO books(id,title,author) VALUES (%1,'%2','%3');")
          .arg(QString::number(++id_book), title, author);
  if (!q.exec(query)) {
    QMessageBox::warning(nullptr, "Sql Error", q.lastError().text());
  }
}

void BookRepository::removeBook(QSqlQuery &q, int id) {
  const auto query =
      QString("DELETE FROM books WHERE id = %1;").arg(QString::number(id));
  if (!q.exec(query)) {
    QMessageBox::warning(nullptr, "Sql Error", q.lastError().text());
  }
}
Book BookRepository::getBookByID(QSqlQuery &q, int id) {
  const auto query =
      QString("SELECT * FROM books WHERE id = %1;").arg(QString::number(id));
  if (!q.exec(query)) {
    QMessageBox::warning(nullptr, "Sql Error", q.lastError().text());
  } else {
    while (q.next()) {
      int id = q.value(0).toInt();
      QString title = q.value(1).toString();
      QString author = q.value(2).toString();

      return Book(id, author, title);
    }
  }
  return Book(404, "Not found", "");
}
std::vector<Book> BookRepository::getAllBooks(QSqlQuery &q) {
  const auto query = QString("SELECT * FROM books;");
  if (!q.exec(query)) {
    QMessageBox::warning(nullptr, "Sql Error", q.lastError().text());
  } else {
    std::vector<Book> bookList;
    while (q.next()) {
      int id = q.value(0).toInt();
      QString title = q.value(1).toString();
      QString author = q.value(2).toString();
      Book new_book(id, author, title);
      bookList.push_back(new_book);
    }
    return bookList;
  }
  return std::vector<Book>();
}
