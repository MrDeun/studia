#ifndef PERSON_REPO
#define PERSON_REPO

#include "person.h"
#include <qlist.h>

namespace PersonRepository{
    void addPerson(const QString& name, const QString& surname, const QString& phone_number, const QString& email);
    void deletePerson(int id);
    Person getPerson(int id);
    QList<Person> getAllPersons();
};

#endif