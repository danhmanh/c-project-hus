#ifndef CHATCLIENT_H

#define CHATCLIENT_H

#include <QWidget>

#include <QBuffer>

#include <QTcpSocket>

namespace Ui {

    class ChatClient;

}

class ChatClient : public QWidget

{

    Q_OBJECT

public:

    explicit ChatClient(QWidget *parent = 0);

    ~ChatClient();

//Khai bao cac ham slot

private slots:

    void setConnected();

    void setDisconnected();

    void toggleConnection();

    void sendMessage();

    void receiveMessage();

private:

    Ui::ChatClient *ui;

    QBuffer *buffer;

    QTcpSocket *socket;

};

#endif // CHATCLIENT_H
