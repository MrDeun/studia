#include "personrepository.h"
#include "person.h"
#include <qlist.h>
#include <qsqlquery.h>

void PersonRepository::addPerson(const QString &name, const QString &surname,
                                 const QString &phone_number,
                                 const QString &email) {
  QSqlQuery q;
  q.prepare("insert into persons values(?,?,?,?)");
  q.addBindValue(name);
  q.addBindValue(surname);
  q.addBindValue(phone_number);
  q.addBindValue(email);

  q.exec();
}

void PersonRepository::deletePerson(int id) {
  QSqlQuery q;
  q.prepare("delete from persons where id = (?)");
  q.addBindValue(id);
  q.exec();
}

Person PersonRepository::getPerson(int id) {
  QSqlQuery q;
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

QList<Person> PersonRepository::getAllPersons() {
    
    QSqlQuery q;
    q.prepare("select * from persons");
    QList<Person> list;
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

