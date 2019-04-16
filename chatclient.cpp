#include "chatclient.h"

#include "ui_chatclient.h"

#include "chatserver.h"

#include "ui_mainwindow.h"

#include "mainwindow.h"

static const int DEFAULT_PORT = 1080;

ChatClient::ChatClient(QWidget *parent) :

    QWidget(parent),

    ui(new Ui::ChatClient)

{

    ui->setupUi(this);

    //Khoi tao cho cac dieu khien (widget)

    ui->spinBoxPort->setRange(1000,32767);

    ui->spinBoxPort->setValue(DEFAULT_PORT);

    ui->lineEditServer->setText("localhost");

    //Khai bao socket va buffer du lieu

    socket = new QTcpSocket(this);

    buffer = new QBuffer(this);

    buffer->open(QIODevice::ReadWrite);

    //Dang ky signal/slot cho cac su kien

    //Su kien click nut Connect

    connect(ui->btnConnect, SIGNAL(clicked()), this, SLOT(toggleConnection()));

    //Su kien go message va enter (gui di)

    connect(ui->lineEditMsg, SIGNAL(returnPressed()), this, SLOT(sendMessage()));

    //Hoac click nut Send (gui di)

    connect(ui->btnSend, SIGNAL(clicked()), this, SLOT(sendMessage()));

    //Su kien ket noi Socket thanh cong

    connect(socket, SIGNAL(connected()), this, SLOT(setConnected()));

    //Su kien ngat ket noi

    connect(socket, SIGNAL(disconnected()), this, SLOT(setDisconnected()));

    //Su kien san sang nhan du lieu

    connect(socket, SIGNAL(readyRead()), this, SLOT(receiveMessage()));

    //Ban dau chua ket noi

    setDisconnected();

}

ChatClient::~ChatClient()

{

    delete ui;

}

/*************************************************

  Ham xu ly cac dieu khien khi ket noi thanh cong

**************************************************/

void ChatClient::setLineEditPort(QString text)
{
    ui->spinBoxPort->setValue(text.toInt());
}

void ChatClient::setLineEditNick(QString text)
{
    ui->lineEditNick->setText(text);
}

void ChatClient::setLineEditNick()
{
    ui->lineEditNick->setEnabled(true);
}

void ChatClient::setConnected()

{
    MainWindow mainWindow;

    ui->lineEditServer->setEnabled(false);

    ui->spinBoxPort->setEnabled(false);

    ui->lineEditMsg->setEnabled(true);

    ui->textEditChat->setEnabled(true);

    ui->textEditChat->clear();

    ui->btnSend->setEnabled(true);

    ui->btnConnect->setText("Disconnect");

//    ui->textEditChat->append("<" + ui->lineEditNick->text().toLatin1() + "> " + "join!");

}

void ChatClient::setDisconnected()

{


    ui->lineEditServer->setEnabled(true);

    ui->spinBoxPort->setEnabled(true);

    ui->lineEditNick->setEnabled(false);



    ui->lineEditMsg->setEnabled(false);

    ui->textEditChat->setEnabled(false);

    ui->textEditChat->clear();

    ui->btnSend->setEnabled(false);

    ui->btnConnect->setText("Connect");

//    ui->textEditChat->append("<" + ui->lineEditNick->text().toLatin1() + "> " + "left!");

    qDebug() << ui->lineEditNick->text() << "Disconnected!";
}

/*************************************************

  Ham tat/bat ket noi den server

**************************************************/

void ChatClient::toggleConnection()

{

    if(socket->state() == QAbstractSocket::UnconnectedState)

    {

        socket->connectToHost(ui->lineEditServer->text(), ui->spinBoxPort->value());

    }

    else

    {

        socket->disconnectFromHost();

    }

}

void ChatClient::sendMessage()

{

    // "<nick> message\n"

    QString nick = ui->lineEditNick->text().toLatin1();

    QString msg = ui->lineEditMsg->text().toLatin1();

    //socket->write("<" + nick + "> " + msg + "\n");

    socket->write("<" + ui->lineEditNick->text().toLatin1() + "> " + ui->lineEditMsg->text().toLatin1() + "\n");

    ui->lineEditMsg->clear();

}

void ChatClient::receiveMessage()

{

    // missing some checks for returns values for the sake of simplicity

    qint64 bytes = buffer->write(socket->readAll());

    // go back as many bytes as we just wrote so that it can be read

    buffer->seek(buffer->pos() - bytes);

    // read only full lines, line by line

    while (buffer->canReadLine())

    {

            QString line = buffer->readLine();

            ui->textEditChat->append(line.simplified());

            qDebug() << line.simplified();
            line.clear();

    }

}

void ChatClient::on_btnConnect_clicked()
{
    qDebug() << ui->lineEditNick->text() << " Connected!";
}
