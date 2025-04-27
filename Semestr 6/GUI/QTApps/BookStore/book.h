#ifndef BOOK_H
#define BOOK_H

#include <QString>

class Book
{
public:
    int id;
    const QString author;
    const QString title;
    Book(const int id, const QString& author, const QString& title);
    ~Book() = default;
};

#endif // BOOK_H
