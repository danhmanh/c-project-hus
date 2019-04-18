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

    void on_btnConnect_clicked();

    void on_btnRename_clicked();

    void on_btn_OK_clicked();

    QString getTime();

private:

    Ui::ChatClient *ui;

    QBuffer *buffer;

    QTcpSocket *socket;

public:

    QString nameOwner;

    QString rules;

    QString timeStart;

    QList<QString> listUser;

    QList<QString> online_status;

public slots:

    void setLineEditPort(QString);
    void setLineEditNick(QString);
    void setLineEditNick();
    void setLineEditNameOwner(QString);
    void setTextEditRules(QString);
    void setTimeStartRoom(QString);

};

#endif // CHATCLIENT_H

