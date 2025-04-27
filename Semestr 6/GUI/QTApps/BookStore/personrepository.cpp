#include "personrepository.h"
#include "person.h"
#include <qlist.h>
#include <qmessagebox.h>
#include <qsqlerror.h>
#include <qsqlquery.h>

void PersonRepository::addPerson(QSqlQuery& q,const QString &name, const QString &surname,
                                 const QString &phone_number,
                                 const QString &email) {
  if(!q.prepare("insert into persons (id,name,surname,phone_number,email) values(?,?,?,?,?)")){
    QMessageBox::warning(nullptr,"Sql Error",q.lastError().text());
    return;
  }
  q.addBindValue(++id_person);
  q.addBindValue(name.toLatin1());
  q.addBindValue(surname.toLatin1());
  q.addBindValue(phone_number.toLatin1());
  q.addBindValue(email.toLatin1());

  if(!q.exec()){
      QMessageBox::warning(nullptr,"Sql Error",q.lastError().text());
  } else {
    if(!q.exec("select * from persons")){
      QMessageBox::warning(nullptr,"Sql Error",q.lastError().text());
    }
    while (!q.next()) {
      QMessageBox::warning(nullptr,"Sql Result",q.value(1).toString());
    }
  }
}

void PersonRepository::deletePerson(QSqlQuery& q,int id) {
  q.prepare("delete from persons where id = (?)");
  q.addBindValue(id);
  q.exec();
}

Person PersonRepository::getPerson(QSqlQuery& q,int id) {
  q.prepare("select * from persons where id = (?)");
  q.addBindValue(id);
  q.exec();
  int _id = q.value(0).toInt();
  QString name = q.value(1).toString();
  QString surname = q.value(2).toString();
  QString phone_number = q.value(3).toString();
  auto email = q.value(4).toString();
  Person p(_id, name, surname, phone_number, email);
  return p;
}

QList<Person> PersonRepository::getAllPersons(QSqlQuery& q) {
    
    q.prepare("select * from persons");
    QList<Person> list;
    if(!q.exec()){
      QMessageBox::warning(nullptr,"SQL Error",q.lastError().text());
      return list;
    }
    while(q.next()){
        int _id = q.value(0).toInt();
        QString name = q.value(1).toString();
        QString surname = q.value(2).toString();
        QString phone_number = q.value(3).toString();
        auto email = q.value(4).toString();
        Person p(_id, name, surname, phone_number, email);
        list.append(p);
    }
    return list;
}

