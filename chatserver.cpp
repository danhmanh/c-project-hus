#include "chatserver.h"

#include "ui_chatserver.h"

#include <QHostAddress>

#include <QTcpSocket>

#include <QBuffer>

#include "mainwindow.h"

#include "logger.h"

static const int DEFAULT_PORT = 1080;

int port;
QHostAddress server_addr;

ChatServer::ChatServer(QWidget *parent) :

    QWidget(parent),

    ui(new Ui::ChatServer)

{
     qDebug() << name;

    ui->setupUi(this);

    server = new QTcpServer();

    //Dang ky signal/slot cho su kien co client ket noi den

    connect(server, SIGNAL(newConnection()), this, SLOT(addConnection()));

    server_addr = QHostAddress::LocalHost; //Lay dia chi may host

    //server_addr = QHostAddress::Any;

    port = DEFAULT_PORT; //Cong mac dinh

    ui->lineEditIP->setText(server_addr.toString()); //Hien dia chi nay len lineEdit

    ui->lineEditIP->isEnabled();

    ui->lineEditPort->setText(QString::number(port));


}

ChatServer::~ChatServer()

{

    delete ui;

}

void ChatServer::setLabelText(QString text)
{
    ui->lineEditName->setText(text);
}

void ChatServer::on_btnStart_clicked()

{

    port = ui->lineEditPort->text().toInt();

    //server bat dau lang nghe ket noi
    QString port_str = QString::number(port);
    QString line = "Connect port: "+ port_str +"\n";

    logger.WriteMessage(line.arg(port), getTime());

    bool b = server->listen(server_addr, port);

    if(b)

    {

        qDebug("Server started!");

        ui->btnStart->setEnabled(false);

        ui->btnStop->setEnabled(true);

        ui->btnNewMember->setEnabled(true);

        chatClient = new ChatClient();

        chatClient->setLineEditNick(name);

        chatClient->setLineEditPort(QString::number(port));



        chatClient->show();

//        this->hide();


    }

    else

    {

        qDebug("server can't start! check IP or Port");

    }

}

void ChatServer::on_btnStop_clicked()

{

    if(server->isListening()) //Neu server dang lang nghe

    {

        server->close(); //thi dung

        ui->btnStart->setEnabled(true);

        ui->btnStop->setEnabled(false);

        QApplication::quit();


    }

}

/*******************************************************

Ham xu ly su kien khi co client ket noi den

Thuc hien:

- Tao socket phuc vu ket noi va them vao danh sach quan ly

- Tao bo dem du lieu tuong ung cho socket do va them vao danh sach quan ly

********************************************************/

void ChatServer::addConnection()

{

    QTcpSocket* connection = server->nextPendingConnection();

    connections.append(connection); //Them ket noi vao danh sach

    QBuffer *buffer = new QBuffer(this); //Tao bo dem du lieu cho connection nay

    buffer->open(QIODevice::ReadWrite);

    buffers.insert(connection, buffer); //Luu vao danh sach

    //Dang ky signal/slot cho moi connection khi co su kien disconnect hoac du lieu gui toi

    connect(connection, SIGNAL(disconnected()), this, SLOT(removeConnection()));

    connect(connection, SIGNAL(readyRead()), this, SLOT(receiveMessage()));

}

/*******************************************************

Ham xu ly su kien khi co client ngat ket noi

Thuc hien:

- Lay socket cua ket noi can ngat

- Lay bo dem du lieu dang quan ly

- Thuc hien ngat ket noi va giai phong bo dem du lieu

********************************************************/

void ChatServer::removeConnection()

{

    //Lay socket gui su kien ngat ket noi

    QTcpSocket* socket = static_cast<QTcpSocket*>(sender());

    QBuffer *buffer = buffers.take(socket); //Lay bo dem du lieu cua ket noi nay (tu danh sach bo dem)

    buffer->close(); //Ket thuc gui nhan

    buffer->deleteLater();//giai phong bo dem

    connections.removeAll(socket); //Xoa socket nay khoi danh sach ket noi server dang quan ly

    socket->deleteLater(); //Giai phong socket

}

/*******************************************************

Ham xu ly su kien khi co du lieu san sang nhan tu mot socket

********************************************************/

void ChatServer::receiveMessage()

{

    //Xac dinh ket noi nao co thong diep den

    QTcpSocket* socket = static_cast<QTcpSocket*>(sender());

    //Lay bo dem du lieu tuong ung voi socket (tu bang hash buffers)

    QBuffer *buffer = buffers.value(socket);

    //ghi toan bo du lieu cua socket nay vao bo dem (buffer) da xac dinh o tren

    qint64 bytes = buffer->write(socket->readAll()); //bytes chua kich thuoc ghi thanh cong

    //dich chuyen ve dau bo dem bang ham seek

    buffer->seek(buffer->pos() - bytes);

    //Vong lap doc tung dong (line) cua thong diep chua trong bo dem

    while (buffer->canReadLine())

    {

            QByteArray line = buffer->readLine();//doc tung dong

            //Gui broadcast den tat ca cac ket noi dang quan ly
            logger.WriteMessage(line, getTime());

            foreach (QTcpSocket* connection, connections)

            {
                    connection->write(line); //Gui bang cach ghi ra socket                
            }

    }

}

void ChatServer::setTime() {
    QDate cd = QDate::currentDate();
    QTime ct = QTime::currentTime();
    timestr = cd.toString() + " " + ct.toString();
}

QString ChatServer::getTime() {
    setTime();
    return timestr;
}
void ChatServer::on_btnNewMember_clicked()
{
    chatClient = new ChatClient();

    chatClient->setLineEditNick();

    chatClient->show();
}
