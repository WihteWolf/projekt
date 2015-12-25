#include "config.h"
#include "ui_config.h"

Config::Config(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Config)
{
    ui->setupUi(this);
    adjustSize();
}

Config::~Config()
{
    delete ui;
}

QString Config::host()
{
    return ui->lineEdit->text();
}

int Config::port()
{
    return ui->lineEdit_2->text().toInt();
}
