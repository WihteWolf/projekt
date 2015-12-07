#include "client.h"
#include "ui_client.h"
#include <QtNetwork>
#include <QTextCodec>
#include <QMessageBox>

Client::Client(QWidget *parent) :
    QWidget(parent), nextBlockSize(0),
    ui(new Ui::Client)
{
    setlocale(LC_ALL, "russian");

    ui->setupUi(this);
    socket = new QTcpSocket(this);

    connect(socket, SIGNAL(readyRead()), this, SLOT(slotReadServer()));

    connect(ui->pushButton_2, SIGNAL(clicked()), SLOT(SendToServer()));
    connect(ui->lineEdit_3, SIGNAL(returnPressed()), SLOT(SendToServer()));

    ui->textEdit->setReadOnly(true);

    ui->lineEdit->setText("localhost");
    ui->lineEdit_2->setText("2323");
}

Client::~Client()
{
    delete ui;
}

void Client::SendToServer()
{
    QString str, text=ui->lineEdit_3->text();

    slotSendToServer(text);
    ui->lineEdit_3->clear();
}
void Client::slotReadServer()
{
    setlocale(LC_ALL, "russian");

    QDataStream in(socket);  // создаем поток на основе сокета
    in.setVersion(QDataStream::Qt_4_5);  // задаем версию формата потока

    forever
    {
        // сначала считываем размер блока данных
        if (!nextBlockSize) // если размер блока равен 0
        {
            if (socket->bytesAvailable() < sizeof(quint16))
                break;
            // если размер полученных данных меньше 2 байт, завершаем чтение данных
            in >> nextBlockSize; // считываем размер блока
        }

        if (socket->bytesAvailable() < nextBlockSize)
            break;  /* если данных в потоке меньше, чем указанный рамер блока, значит произошла ошибка, прерываем цикл */


            QDate date;
            QString str;
            in >> date >> str;

            ui->textEdit->append(date.toString() + " " + str);
    }
    nextBlockSize = 0;
}

void Client::slotSendToServer(QString str)
{
    setlocale(LC_ALL, "russian");

    QByteArray arrBlock;
    QDataStream out(&arrBlock, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_5);

    out << quint16(0) << QTime::currentTime() << str;
    out.device()->seek(0);  // переходим в начало блока
    out << quint16(arrBlock.size() - sizeof(quint16));

    socket->write(arrBlock); // передаем данные
    //qDebug()<<arrBlock.size();
}

void Client::on_pushButton_clicked()
{
    QString strHost=ui->lineEdit->text();// считываем номер компьютера
    int port=ui->lineEdit_2->text().toInt(); // считываем номер порта
    socket->connectToHost(strHost, port); // Устанавливаем связь с сервером
}
