#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtNetwork>
#include <QTextCodec>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setlocale(LC_ALL, "russian");

    socket = new QTcpSocket(this);
    connect(socket, SIGNAL(readyRead()), this, SLOT(slotReadServer()));

    codec = QTextCodec::codecForName("UTF-8");

    Port=0;
    Host.clear();

    Login.clear();
    Password.clear();
    StatusLogin = false;

    confFile = new QFile("config.cfg");
    FileConfig();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::slotReadServer()
{
    setlocale(LC_ALL, "russian");

    forever
    {
        if (socket->bytesAvailable()<=0)
            break;

       QByteArray block = socket->readAll();
       QString str = codec->toUnicode(block.data());

       HandlerEvent(str);
    }
}

void MainWindow::slotSendToServer(QString str)
{
    QByteArray arrBlock;
    QDataStream out(&arrBlock, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_1);

    socket->write(codec->fromUnicode(str)); // передаем данные
}

void MainWindow::closeEvent(QCloseEvent *event)
{
     slotSendToServer("~close");
     SaveConfig();
     close();
}

void MainWindow::on_Connect_triggered()
{
    if(Port!=0 && !Host.isEmpty())
    {
        socket->connectToHost(Host, Port);
        if(socket->waitForConnected())
        {
            ui->statusBar->showMessage("Соединение установлено");

            if(!Login.isEmpty() && !Password.isEmpty())
                login();
            else
                QMessageBox::information(this, "Внимание", "Для работы задайте имя пользователя и пароль в настройках!");
        }
        else
            ui->statusBar->showMessage("Соединение не установлено");
    }
    else
        QMessageBox::critical(this, "Ошибка", "Не указан порт или хост, \n проверьте файл настроек!");
}


void MainWindow::on_Config_triggered()
{
    Config dlg(this);

    if(dlg.exec()==QDialog::Accepted)
    {
        QString host = dlg.host();
        int port = dlg.port();

        confFile->open(QIODevice::Text | QIODevice::ReadOnly);

        if(confFile->isOpen())
        {
            QString text;
            text.clear();
            while(!confFile->atEnd())
            {
                QString s=confFile->readLine();
                s.chop(1);
                QStringList list=s.split(":", QString::SkipEmptyParts);

                if(list.size()>=2)
                {
                    if(list.at(0).indexOf("Login")!=-1)
                        text+=list.at(0)+":"+list.at(1)+"\n";
                    else if(list.at(0).indexOf("Password")!=-1)
                        text+=list.at(0)+":"+list.at(1)+"\n";
                }
            }
            text+="Host:"+host+"\n";
            text+="Port:"+QString::number(port)+"\n";

            confFile->close();
            confFile->open(QIODevice::Text | QIODevice::WriteOnly);

            QTextStream stream(confFile);
            stream<<text;

            confFile->close();
            FileConfig();
        }
        else
        {
            QMessageBox::critical(this, "Ошибка", "Не найден файл настроек");
        }
    }
}


void MainWindow::login()
{
    ui->statusBar->showMessage("Авторизация...", 3000);
    slotSendToServer("~login:"+Login+":"+Password);
}


void MainWindow::FileConfig()
{
   // QFile confFile(":/config.cfg");
    confFile->open(QIODevice::Text | QIODevice::ReadOnly);

    if(confFile->isOpen())
    {
        while(!confFile->atEnd())
        {
            QString s=confFile->readLine();
            s.chop(1);
            QStringList list=s.split(":", QString::SkipEmptyParts);
            if(list.size()>=2)
            {
                if(list.at(0).indexOf("Login")!=-1)
                    Login = list.at(1);
                else if(list.at(0).indexOf("Password")!=-1)
                    Password = list.at(1);
                else if(list.at(0).indexOf("Host")!=-1)
                    Host = list.at(1);
                else if(list.at(0).indexOf("Port")!=-1)
                    Port = list.at(1).toInt();
            }
        }
        confFile->close();
        on_Connect_triggered();
    }
    else
    {
        QMessageBox::critical(this, "Ошибка", "Не найден файл настроек");
    }
}


void MainWindow::HandlerEvent(QString Event)
{
    if(Event.at(0)=='~')
    {
       if(Event.indexOf("~LoginOk")!=-1)
       {
           StatusLogin=true;
           ui->statusBar->showMessage("Авторизировался");
       }
       else if(Event.indexOf("~LoginNot")!=-1)
       {
           ui->statusBar->showMessage("Неверный логин или пароль");
       }
       else if(Event.indexOf("~RegOk")!=-1)
       {
           QMessageBox::warning(this, "Регистрация", "Регистрация прошла успешно!");
       }
       else if(Event.indexOf("~RegNot")!=-1)
       {
           QMessageBox::warning(this, "Регистрация", "Регистрация прошла не успешно!");
       }
       else if(Event.indexOf("~DelOk")!=-1)
       {
           QMessageBox::warning(this, "Удаление", "Удаление прошло успешно!");
       }
       else if(Event.indexOf("~DelNot")!=-1)
       {
           QMessageBox::warning(this, "Удаление", "Удаление прошло не успешно!");
       }
    }
}

void MainWindow::on_DateUser_triggered()
{
    DateUser dlg(this, Login, Password);

    if(dlg.exec()==QDialog::Accepted)
    {
        Login = dlg.Login();
        Password = dlg.Password();
    }
}

void MainWindow::SaveConfig()
{
    confFile->open(QIODevice::Text | QIODevice::ReadOnly);

    if(confFile->isOpen())
    {
        QString text;
        text.clear();
        while(!confFile->atEnd())
        {
            QString s=confFile->readLine();
            s.chop(1);
            QStringList list=s.split(":", QString::SkipEmptyParts);

            if(list.size()>=2)
            {
                if(list.at(0).indexOf("Host")!=-1)
                    text+=list.at(0)+":"+list.at(1)+"\n";
                else if(list.at(0).indexOf("Port")!=-1)
                    text+=list.at(0)+":"+list.at(1)+"\n";
            }
        }
        text+="Login:"+Login+"\n";
        text+="Password:"+Password+"\n";

        confFile->close();
        confFile->open(QIODevice::Text | QIODevice::WriteOnly);

        QTextStream stream(confFile);
        stream<<text;

        confFile->close();
        FileConfig();
    }
    else
    {
        QMessageBox::critical(this, "Ошибка", "Не найден файл настроек");
    }
}

void MainWindow::on_Registr_triggered()
{
    Registr dlg(this);

    if(dlg.exec()==QDialog::Accepted)
    {
        Login = dlg.Login();
        Password = dlg.Password();

        slotSendToServer("~reg:"+Login+":"+Password);
    }
}

void MainWindow::on_action_triggered()
{
    slotSendToServer("~del:"+Login+":"+Password);
}
