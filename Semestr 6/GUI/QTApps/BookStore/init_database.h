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



inline QSqlError initDB() {
  QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
  db.setDatabaseName(":memory:");
  if (!db.open()) {
    return db.lastError();
  }

  return db.lastError();
}

#endif // INIT_DATABASE_H
