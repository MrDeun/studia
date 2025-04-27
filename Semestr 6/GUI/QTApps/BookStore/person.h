#ifndef PERSON_H
#define PERSON_H

#include <QString>
#include <qobject.h>
class Person {
public:
  const int id;
  const QString name;
  const QString surname;
  const QString phone_number;
  const QString email;
  Person(int id, const QString &name, const QString &surname,
         const QString &phone_number, const QString &email);
  ~Person() = default;
};

#endif // PERSON_H
