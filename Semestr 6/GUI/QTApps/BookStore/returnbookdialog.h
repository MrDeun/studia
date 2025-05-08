#ifndef RETURNBOOKDIALOG_H
#define RETURNBOOKDIALOG_H

#include <QDialog>

#include "borrowing_repository.h"

namespace Ui {
class ReturnBookDialog;
}

class ReturnBookDialog : public QDialog {
  Q_OBJECT

public:
  explicit ReturnBookDialog(QWidget *parent = nullptr);
  void setBorrows(std::vector<Borrowing> *_borrows, QSqlQuery &q);
  int getIndex() { return currentIndex; }
  ~ReturnBookDialog();
private slots:
  void validateAndAccept();
  void changedBookChoice(const QString &label);

private:
  Ui::ReturnBookDialog *ui;
  std::vector<Borrowing> *m_borrows;
  int currentIndex;
};

#endif // RETURNBOOKDIALOG_H
