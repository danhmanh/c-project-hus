#include "chatclient.h"

#include "ui_chatclient.h"

#include "chatserver.h"

#include "ui_mainwindow.h"

#include "mainwindow.h"

#include <user.h>

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

void ChatClient::setLineEditNameOwner(QString text)
{
    ui->lineEditNameOwner->setText(text);
}

void ChatClient::setTextEditRules(QString text)
{
    ui->textEditRules->setText(text);
}

void ChatClient::setLineEditNick()
{
    ui->lineEditNick->setEnabled(true);
}

void ChatClient::setTimeStartRoom(QString text)
{
    ui->lineEditTimeStart->setText(text);
}
void ChatClient::setConnected()

{
    MainWindow mainWindow;

    ui->lineEditNick->setEnabled(false);

    ui->lineEditServer->setEnabled(false);

    ui->spinBoxPort->setEnabled(false);

    ui->lineEditMsg->setEnabled(true);

    ui->textEditChat->setEnabled(true);

    ui->textEditChat->clear();

    ui->btnSend->setEnabled(true);

    ui->btnConnect->setText("Disconnect");

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


}

/*************************************************

  Ham tat/bat ket noi den server

**************************************************/

void ChatClient::toggleConnection()

{

    if(socket->state() == QAbstractSocket::UnconnectedState)

    {

        socket->connectToHost(ui->lineEditServer->text(), ui->spinBoxPort->value());

         qDebug() << ui->lineEditNick->text() << "Connected!";
    }

    else

    {

        socket->disconnectFromHost();
        qDebug() << ui->lineEditNick->text() << "Disconnected!";
    }

}

void ChatClient::sendMessage()

{

    // "<nick> message\n"

    QString nick = ui->lineEditNick->text().toLatin1();

    QString msg = ui->lineEditMsg->text().toLatin1();

    socket->write(getTime().toLatin1()+  " ["  + ui->lineEditNick->text().toLatin1() + "] : " + ui->lineEditMsg->text().toLatin1() + "\n");

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

//            qDebug() << line.simplified();
            line.clear();

    }
//    if(fisrt.firstName != last.lastName){
//        ui->textEditChat->("Da doi ten");
//    }

}

void ChatClient::on_btnConnect_clicked()
{
    QString name = ui->lineEditNick->text();
        bool check = false;
        for(int i = 0; i < listUser.size(); i++) {
            if (listUser[i] == name) {
                check = true;
            }
        }
        if(check == false) {
            listUser << name;
            user.WriteUser(name);
            online_status << "online";
        }
}

void ChatClient::on_btnRename_clicked()
{
    ui->lineEditNick->setEnabled(true);

    QString firstName = ui->lineEditNick->text().toLatin1();

//    return firstName;

//    qDebug() << firstName << "la nick name dau tien" ;
}
void ChatClient::on_btn_OK_clicked()
{
    ui->lineEditNick->setEnabled(false);

    QString lastName = ui->lineEditNick->text().toLatin1();

    ui->textEditChat->append(lastName +" la nick name moi");

}

QString ChatClient::getTime() {
    ChatServer chatServer;
    chatServer.setTime();
    return chatServer.timeCT;
}
