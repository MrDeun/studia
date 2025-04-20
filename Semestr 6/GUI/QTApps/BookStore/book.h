#ifndef BOOK_H
#define BOOK_H

#include <string>

class Book
{
private:
    const int id;
    const std::string title;
    const std::string author;
public:
    Book();
    const std::string& getTitle() {return this->title;}

};

#endif // BOOK_H
