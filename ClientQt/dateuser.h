#ifndef DATEUSER_H
#define DATEUSER_H

#include <QDialog>

namespace Ui {
class DateUser;
}

class DateUser : public QDialog
{
    Q_OBJECT

public:
    explicit DateUser(QWidget *parent = 0, QString login=NULL, QString password=NULL);
    ~DateUser();
    QString Login();
    QString Password();
private:
    Ui::DateUser *ui;
};

#endif // DATEUSER_H
