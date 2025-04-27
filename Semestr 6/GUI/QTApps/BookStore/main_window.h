#ifndef BOOKSTORE_H
#define BOOKSTORE_H

#include <QMainWindow>
#include <QSqlTableModel>

#include "bookrepository.h"
#include "personrepository.h"

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

    QList<Person> persons;
    QList<Book> books;

    int currentBookID;
    void updateList();
    Ui::BookStore *ui;

    
    

};
#endif // BOOKSTORE_H
