#ifndef BORROWBOOKDIALOG_H
#define BORROWBOOKDIALOG_H

#include <QDialog>

#include "bookrepository.h"
#include "borrowing_repository.h"
#include "personrepository.h"
namespace Ui {
class BorrowBookDialog;
}

class BorrowBookDialog : public QDialog {
  Q_OBJECT

public:
  explicit BorrowBookDialog(QWidget *parent = nullptr);
  ~BorrowBookDialog();
  void setContainers(std::vector<Book> *_b, std::vector<Person> *_p);
  int getBookID(){return id_book;}
  int getPersonID(){return id_person;}
private slots:
  void changedBookBoxText(const QString &label);
  void changedPersonBoxText(const QString &label);
  void validateAndAccept();

private:
  Ui::BorrowBookDialog *ui;
  int id_book = -1;
  int id_person = -1;
  std::vector<Book> *availableBooks = nullptr;
  std::vector<Person> *persons = nullptr;
};

#endif // BORROWBOOKDIALOG_H
