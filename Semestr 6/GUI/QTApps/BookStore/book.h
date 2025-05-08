#ifndef BOOK_H
#define BOOK_H

#include <QString>

class Book
{
    int id;
    const QString author;
    const QString title;
public:
    Book(const int id, const QString& author, const QString& title);
    Book(const Book&) = default;
    ~Book() = default;
    
    QString getAuthor()const{return author;}
    QString getTitle()const{return title;}
    int getID()const{return id;}
    
};

#endif // BOOK_H
