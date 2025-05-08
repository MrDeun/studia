#include "addbookdialog.h"
#include "ui_addbookdialog.h"

AddBookDialog::AddBookDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::AddBookDialog)
{
    ui->setupUi(this);
}

void AddBookDialog::validateAndAccept(){
    const QString& title = ui->lineEdit->text();
    if(title.isEmpty()){
        QMessageBox::warning(this,"Book Creation Error","Title can't be empty!");
        return;
    }
    const QString& author = ui->lineEdit_2->text();
    if(author.isEmpty()){
        QMessageBox::warning(this,"Book Creation Error","Author can't be empty!");
        return;
    }
    accept();
}
QString AddBookDialog::getTitle(){return ui->lineEdit->text();}
QString AddBookDialog::getAuthor(){return ui->lineEdit_2->text();}

AddBookDialog::~AddBookDialog()
{
    delete ui;
}
