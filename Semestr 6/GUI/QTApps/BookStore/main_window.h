#ifndef BOOKSTORE_H
#define BOOKSTORE_H

#include <QMainWindow>
#include <QSqlTableModel>
#include <qsqldatabase.h>
#include <vector>

#include "book.h"
#include "person.h"
#include "borrowing_repository.cpp"

QT_BEGIN_NAMESPACE
namespace Ui {
class BookStore;
}
QT_END_NAMESPACE

enum VIEW_SELECTION {
    BOOKS,
    PERSONS,
};


class BookStore : public QMainWindow
{
    Q_OBJECT

public:
    BookStore(QWidget *parent = nullptr);
~BookStore();

private slots:
    void addBookClicked();
    void addPersonClicked();
    void deleteBookClicked();
    void deletePersonClicked();
    void borrowBookClicked();
    void returnBookClicked();
    void switchedTab();
    void clickedElementOfList();

private:
    VIEW_SELECTION currentView;

    std::vector<Person> persons;
    std::vector<Book> books;

    Person* currentPerson = nullptr;
    Book* currentBook = nullptr;


    void updateList();
    void initDB();
    Ui::BookStore *ui;

    QSqlDatabase db;
    

};
#endif // BOOKSTORE_H
