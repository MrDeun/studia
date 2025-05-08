#include "borrowbookdialog.h"
#include "ui_borrowbookdialog.h"
#include <qmessagebox.h>

BorrowBookDialog::BorrowBookDialog(QWidget *parent)
    : QDialog(parent), ui(new Ui::BorrowBookDialog) {
  ui->setupUi(this);
}

void BorrowBookDialog::validateAndAccept(){
    if(id_book<0){
        QMessageBox::warning(this,"Borrow Book Dialog Error","Incorrect Book ID");
        return;
    } if(id_person<0){
        QMessageBox::warning(this,"Borrow Book Dialog Error","Incorrect Person ID");
        return;
    }
    accept();
}

void BorrowBookDialog::changedBookBoxText(const QString &label) {
    int startPos = label.lastIndexOf('(') + 1;
    int endPos = label.lastIndexOf(')');
    int lenght = endPos - startPos;

    id_book = label.mid(startPos,lenght).toInt();
}
void BorrowBookDialog::changedPersonBoxText(const QString &label) {
    int startPos = label.lastIndexOf('(') + 1;
    int endPos = label.lastIndexOf(')');
    int lenght = endPos - startPos;

    id_person = label.mid(startPos,lenght).toInt();
}
void BorrowBookDialog::setContainers(std::vector<Book> *_b,
                                     std::vector<Person> *_p) {
  availableBooks = _b;
  persons = _p;

  for (const auto &b : *availableBooks){
      const QString label = QString("(%1) \"%2\"").arg(QString::number(b.getID()),b.getTitle());
      ui->comboBox_2->addItem(label);
  }
  for (const auto &p : *persons){
      const QString label = QString("(%1) %2 %3").arg(QString::number(p.getID()),p.getName(),p.getSurname());
      ui->comboBox->addItem(label);
  }

}

BorrowBookDialog::~BorrowBookDialog() { delete ui; }
