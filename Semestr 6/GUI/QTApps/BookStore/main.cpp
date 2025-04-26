#include "bookstore.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    BookStore w;
    w.show();
    return a.exec();
}
