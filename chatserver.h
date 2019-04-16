#ifndef CHATSERVER_H

#define CHATSERVER_H

#include <QWidget>

#include <QTcpServer>

#include <QList>

#include <QHash>

#include <chatclient.h>

#include <logger.h>


class QBuffer;

class QTcpSocket;

namespace Ui {

    class ChatServer;

}

class ChatServer : public QWidget

{

    Q_OBJECT

public:

    explicit ChatServer(QWidget *parent = 0);

    ~ChatServer();

    QString name;

private:

    QTcpServer *server;

    //Danh sach chua cac connection de phuc vu client ket noi den

    QList<QTcpSocket*> connections;

    //Mang bo dem du lieu, moi phan tu tuong ung du lieu cua mot socket

    QHash<QTcpSocket*, QBuffer*> buffers;

    Ui::ChatServer *ui;

    ChatClient *chatClient;

    QString timestr;

private slots: //Tao slots tu dong

    void on_btnStop_clicked();

    void on_btnStart_clicked();

private slots: //Tao bang cach viet ma

    void addConnection(); //Xu ly khi co mot client ket noi den

    void removeConnection(); //Xu ly khi co mot client ngat ket noi

    void receiveMessage(); //Nhan thong diep tu cac client

    void setTime();

    QString getTime();

    void on_btnNewMember_clicked();

public slots:

    void setLabelText(QString);
};

#endif // CHATSERVER_H
