#include "personrepository.h"
#include "person.h"
#include <vector>
#include <qmessagebox.h>
#include <qsqlerror.h>
#include <qsqlquery.h>

#define UNREACHABLE false

void PersonRepository::addPerson(QSqlQuery &q, const QString &name,
                                 const QString &surname,
                                 const QString &phone_number,
                                 const QString &email) {
  const auto query =
      QString("INSERT INTO persons(id,name,surname,phone_number,email) values "
              "(%1,'%2','%3','%4','%5');")
          .arg(QString::number(++id_person), name, surname, phone_number,
               email);
  if (!q.exec(query)) {
    QMessageBox::warning(nullptr, "Sql Error", q.lastError().text());
  }
}

void PersonRepository::deletePerson(QSqlQuery &q, int id){
  const QString query = QString("DELETE FROM persons WHERE id = %1").arg(QString::number(id));
  if(!q.exec(query)){
    QMessageBox::warning(nullptr,"Sql Error",q.lastError().text());
  }
}

Person PersonRepository::getPerson(QSqlQuery &q, int id){
  const QString query = QString("SELECT * FROM persons WHERE id = %1").arg(QString::number(id));
  if(!q.exec(query)){
    QMessageBox::warning(nullptr,"Sql Error",q.lastError().text());
  } else {
    while(q.next()){
      int id = q.value(0).toInt();
      QString name = q.value(1).toString();
      QString surname = q.value(2).toString();
      QString phone_number = q.value(3).toString();
      QString email = q.value(4).toString();

      return Person(id,name,surname,phone_number,email);
    }
  }
  assert(UNREACHABLE);
  return Person(404,"Not found","","","");
}
std::vector<Person> PersonRepository::getAllPersons(QSqlQuery &q){
  const QString query = QString("SELECT * FROM persons;");
  if(!q.exec(query)){
    QMessageBox::warning(nullptr,"Sql Error",q.lastError().text());
  } else {
    std::vector<Person> people;
    while(q.next()){
      int id = q.value(0).toInt();
      QString name = q.value(1).toString();
      QString surname = q.value(2).toString();
      QString phone_number = q.value(3).toString();
      QString email = q.value(4).toString();

      Person new_person(id,name,surname,phone_number,email);
      people.push_back(new_person);
    }
    return people;
  }
  return std::vector<Person>();
}
