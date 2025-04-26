#ifndef BOOK_H
#define BOOK_H

#include <QString>

class Book
{
private:
    int id;
    const QString author;
    const QString title;
public:
    Book(const int id, const QString& author, const QString& title);
    ~Book() = default;
    const QString& getAuthor(){return this->author;}
    const QString& getTitle(){return this->title;}
    const int getID(){return this->id;}
};

#endif // BOOK_H
