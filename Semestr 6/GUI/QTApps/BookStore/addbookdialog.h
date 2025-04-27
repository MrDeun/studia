#ifndef ADDBOOKDIALOG_H
#define ADDBOOKDIALOG_H

#include <QDialog>

namespace Ui {
class AddBookDialog;
}

class AddBookDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddBookDialog(QWidget *parent = nullptr);
    QString getName();
    QString getSurname();
    QString getPhoneNumber();
    QString getEmail();
    ~AddBookDialog();
private slots:
    void validateAndAccept();
private:
    Ui::AddBookDialog *ui;

};

#endif // ADDBOOKDIALOG_H
