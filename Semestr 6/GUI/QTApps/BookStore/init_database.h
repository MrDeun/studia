#ifndef INIT_DATABASE_H
#define INIT_DATABASE_H
#include <QDate>
#include <QSqlError>
#include <QSqlQuery>
#include <qcontainerfwd.h>
#include <qlatin1stringview.h>
#include <qnamespace.h>
#include <qsqldatabase.h>
#include <qsqlerror.h>
#include <qsqlquery.h>


inline constexpr auto BOOKS_SQL = QLatin1String(R"(
  create table if not exists books (
  id integer primary key,
  title text,
  author text,
  is_available boolean default 1))"
);


inline constexpr auto PERSONS_SQL = QLatin1String(R"(
  create table if not exists persons (
  id integer primary key,
  name text,
  surname text,
  phone_number text,
  email text
  ))"
);


inline constexpr auto BORROWINGS_SQL = QLatin1String(R"(
  create table if not exists borrowings (
  id integer primary key,
  id_person integer not null,
  id_book integer not null,
  borrow_date text not null,
  due_date text not null,
  return_date text, 
  ))"
);


inline QSqlError initDB() {
  QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
  db.setDatabaseName(":memory:");
  if (!db.open()) {
    return db.lastError();
  }

  QSqlQuery q;

  if(!q.exec(BOOKS_SQL))
    return db.lastError();
  if(!q.exec(PERSONS_SQL))
    return db.lastError();
  if(!q.exec(BORROWINGS_SQL))
    return db.lastError();

  return db.lastError();
}

#endif // INIT_DATABASE_H
