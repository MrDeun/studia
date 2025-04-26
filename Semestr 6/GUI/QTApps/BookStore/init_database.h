#ifndef INIT_DATABASE_H
#define INIT_DATABASE_H
#include <QDate>
#include <QSqlError>
#include <QSqlQuery>
#include <qsqldatabase.h>
#include <qsqlerror.h>

void addBook(QSqlQuery& q, const QString& title, const QString& author, int year){
    q.addBindValue(title);
    q.addBindValue(author);
    q.addBindValue(year);
    q.exec();

    return ;
}

void addBorrow(QSqlQuery& q, int id_person, int id_book){
    q.addBindValue(id_person);
    q.addBindValue(id_book);
    q.exec();

    return;
}

void addPerson(QSqlQuery& q, const QString& name, const QString& surname){
    q.addBindValue(name);
    q.addBindValue(surname);
    q.exec();

    return;
}

const auto BOOKS_SQL = QLatin1String(R"(
    create table books (id integer primary key, title varchar, author varchar, year interger)
)");

const auto PERSONS_SQL = QLatin1String(R"(
    create table persons (id integer primary key, name varchar, surname varchar)
)");

const auto BORROWED_SQL = QLatin1String(R"(
    create table borrowed (id integer primary key. id_person interger, id_book interger)
)");


QSqlError initDB() {
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(":memory:");
}

#endif // INIT_DATABASE_H
