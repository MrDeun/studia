#ifndef ADDBOOKDIALOG_H
#define ADDBOOKDIALOG_H

#include <QDialog>
#include <QMessageBox>

namespace Ui {
class AddBookDialog;
}

class AddBookDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddBookDialog(QWidget *parent = nullptr);
    ~AddBookDialog();
    QString getTitle();
    QString getAuthor();
private slots:
    void validateAndAccept();
private:
    Ui::AddBookDialog *ui;
};

#endif // ADDBOOKDIALOG_H
