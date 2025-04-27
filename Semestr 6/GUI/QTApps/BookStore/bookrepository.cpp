#include "bookrepository.h"
#include <qsqlquery.h>

void BookRepository::addBook(const QString &author, const QString &title){
    QSqlQuery q;
    q.prepare("insert into books values (?,?,?)");
    q.addBindValue(author);
    q.addBindValue(title);
    q.exec();
}
