#ifndef CLIENT_H
#define CLIENT_H

#include <QWidget>

class QTcpSocket;

namespace Ui {
    class Client;
}

class Client : public QWidget
{
    Q_OBJECT
    QTcpSocket* socket;
    quint16 nextBlockSize;
public:
    explicit Client(QWidget *parent = 0);
    ~Client();

private:
    Ui::Client *ui;


public slots:
    void SendToServer();
    void slotSendToServer(QString);
    void slotReadServer();

private slots:
    void on_pushButton_clicked();

};

#endif // CLIENT_H
