#ifndef REGISTR_H
#define REGISTR_H

#include <QDialog>

namespace Ui {
class Registr;
}

class Registr : public QDialog
{
    Q_OBJECT

public:
    explicit Registr(QWidget *parent = 0);
    ~Registr();

    QString Login();
    QString Password();
private:
    Ui::Registr *ui;
};

#endif // REGISTR_H
