#include "registr.h"
#include "ui_registr.h"
#include <qmessagebox.h>

Registr::Registr(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Registr)
{
    ui->setupUi(this);
    adjustSize();

    ui->lineEdit_2->setEchoMode(QLineEdit::Password);
    ui->lineEdit_3->setEchoMode(QLineEdit::Password);
}

Registr::~Registr()
{
    delete ui;
}

 QString Registr::Login()
 {
     return ui->lineEdit->text();
 }

 QString Registr::Password()
 {
     if(ui->lineEdit_2->text()!=ui->lineEdit_2->text())
     {
         QMessageBox::critical(this, "Ошибка", "Пароли не совподают!");
         return NULL;
     }
     else
        return ui->lineEdit_2->text();
 }
