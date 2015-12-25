#include "dateuser.h"
#include "ui_dateuser.h"

DateUser::DateUser(QWidget *parent, QString login, QString password) :
    QDialog(parent),
    ui(new Ui::DateUser)
{
    ui->setupUi(this);
    adjustSize();
    ui->lineEdit_2->setEchoMode(QLineEdit::Password);
    ui->lineEdit->setText(login);
    ui->lineEdit_2->setText(password);
}

DateUser::~DateUser()
{
    delete ui;
}

QString DateUser::Login()
{
    return ui->lineEdit->text();
}

QString DateUser::Password()
{
    return ui->lineEdit_2->text();
}
