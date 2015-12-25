#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTextCodec>
#include "config.h"
#include "dateuser.h"
#include "registr.h"
#include <QFileDialog>

class QTcpSocket;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    QString Login;
    QString Password;
    QString Host;
    int Port;
    QTcpSocket* socket;
    QTextCodec* codec;
    bool StatusLogin;
    QFile *confFile;
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    void FileConfig();
    void Connected();
    void login();
    void HandlerEvent(QString Event);
    void SaveConfig();
    void closeEvent(QCloseEvent *);

public slots:
    void slotSendToServer(QString);
    void slotReadServer();

private slots:
    void on_Connect_triggered();
    void on_Config_triggered();
    void on_DateUser_triggered();
    void on_Registr_triggered();
    void on_action_triggered();
};

#endif // MAINWINDOW_H
