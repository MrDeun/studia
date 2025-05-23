#ifndef PERSON_H
#define PERSON_H

#include <QString>
#include <qobject.h>
class Person {
  private:
   int id;
   QString name;
   QString surname;
   QString phone_number;
   QString email;
public:
  Person(int id, const QString &name, const QString &surname,
         const QString &phone_number, const QString &email);
  QString getName()const{return name;}
  QString getSurname()const{return surname;}
  QString getPhoneNumber()const{return phone_number;}
  QString getEmail()const{return email;}
  int getID()const{return id;}
  ~Person() = default;
};

#endif // PERSON_H
