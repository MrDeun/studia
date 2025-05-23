#ifndef PERSON_REPO
#define PERSON_REPO

#include "person.h"
#include <vector>
#include <qsqlquery.h>

namespace PersonRepository{
    static int id_person = 0;
    void addPerson(QSqlQuery& q, const QString& name, const QString& surname, const QString& phone_number, const QString& email);
    void deletePerson(QSqlQuery& q,int id);
    Person getPerson(QSqlQuery& q,int id);
    std::vector<Person> getAllPersons(QSqlQuery& q);
};

#endif