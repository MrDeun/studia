#ifndef ADDPERSONDIALOG_H
#define ADDPERSONDIALOG_H

#include <QDialog>
#include <QMessageBox>

namespace Ui {
class AddPersonDialog;
}

class AddPersonDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddPersonDialog(QWidget *parent = nullptr);
    ~AddPersonDialog();
    QString getName();
    QString getSurname();
    QString getPhoneNumber();
    QString getEmail();
private slots:
    void validateAndAccept();
private:
    Ui::AddPersonDialog *ui;
};

#endif // ADDPERSONDIALOG_H
