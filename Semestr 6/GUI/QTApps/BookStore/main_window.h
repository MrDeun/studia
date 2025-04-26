#ifndef BOOKSTORE_H
#define BOOKSTORE_H

#include <QMainWindow>
#include <QSqlTableModel>

#include "book.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class BookStore;
}
QT_END_NAMESPACE

class BookStore : public QMainWindow
{
    Q_OBJECT

public:
    BookStore(QWidget *parent = nullptr);
    ~BookStore();

private slots:
    void addBookClicked();
    void deleteBookClicked();
    void borrowBookClicked();
    void returnBookClicked();

private:
    std::vector<Book> bookList;
    int currentBookID;
    void updateList();
    Ui::BookStore *ui;
    

};
#endif // BOOKSTORE_H
