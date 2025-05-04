#include "addpersondialog.h"
#include "ui_addpersondialog.h"
#include <qmessagebox.h>

AddPersonDialog::AddPersonDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::AddPersonDialog)
{
    ui->setupUi(this);
}

QString AddPersonDialog::getName(){return ui->lineEdit->text();}
QString AddPersonDialog::getSurname(){return ui->lineEdit->text();}
QString AddPersonDialog::getPhoneNumber(){return ui->lineEdit->text();}
QString AddPersonDialog::getEmail(){return ui->lineEdit_4->text();}
void AddPersonDialog::validateAndAccept(){
    if(ui->lineEdit->text().isEmpty()){
        QMessageBox::warning(this,"Person Creation error","Name cannot be empty!");
        return;
    }
    if(ui->lineEdit_2->text().isEmpty()){
        QMessageBox::warning(this,"Person creation error","Surnname cannot be empty!");
        return;
    }
    accept();
}

AddPersonDialog::~AddPersonDialog()
{
    delete ui;
}
