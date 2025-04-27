#include "addbookdialog.h"
#include "ui_addbookdialog.h"
#include <QMessageBox>
#include <qmessagebox.h>

AddBookDialog::AddBookDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::AddBookDialog)
{
    ui->setupUi(this);
}
void AddBookDialog::validateAndAccept(){
    if(getName().isEmpty()){
        QMessageBox::warning(this,"Validation Error","Name cannot be empty!");
        ui->lineEdit->setFocus();
        return;
    }
    if(getSurname().isEmpty()){
        QMessageBox::warning(this,"Validation Error","Surname cannot be empty");
        ui->lineEdit_2->setFocus();
        return;
    }

    accept();
}

QString AddBookDialog::getName(){
    return ui->lineEdit->text();
}

QString AddBookDialog::getSurname(){
    return ui->lineEdit_2->text();
}

QString AddBookDialog::getEmail(){
    return ui->lineEdit_3->text();
}

QString AddBookDialog::getPhoneNumber(){
    return ui->lineEdit_4->text();
}

AddBookDialog::~AddBookDialog(){
    delete ui;
}
