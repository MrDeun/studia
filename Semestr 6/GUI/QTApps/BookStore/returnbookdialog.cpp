#include "returnbookdialog.h"
#include "ui_returnbookdialog.h"

#include "bookrepository.h"
#include "personrepository.h"

ReturnBookDialog::ReturnBookDialog(QWidget *parent)
    : QDialog(parent), currentIndex(-1), ui(new Ui::ReturnBookDialog),
      m_borrows(nullptr) {
  ui->setupUi(this);
}

void ReturnBookDialog::setBorrows(std::vector<Borrowing> *_borrows,
                                  QSqlQuery &q) {
  m_borrows = _borrows;

  ui->comboBox->clear();
  for (const auto &bor : *m_borrows) {
    const Person p = PersonRepository::getPerson(q, bor.getPersonID());
    const Book b = BookRepository::getBookByID(q, bor.getBookID());
    ui->comboBox->addItem(
        QString("(%1) %2 - %3")
            .arg(QString::number(bor.getID()), p.getName(), b.getTitle()));
  }
}
void ReturnBookDialog::changedBookChoice(const QString &label) {
  int startPos = label.lastIndexOf('(') + 1;
  int endPos = label.lastIndexOf(')');
  int lenght = endPos - startPos;
  currentIndex = label.mid(startPos, lenght).toInt();
}

void ReturnBookDialog::validateAndAccept() {
  if (currentIndex < 0) {
    QMessageBox::warning(nullptr, "Dialog error",
                         "Non-valid borrowing record was chosen!");
    return;
  }
  accept();
}

ReturnBookDialog::~ReturnBookDialog() { delete ui; }
