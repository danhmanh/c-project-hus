#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "chatserver.h"
#include "chatclient.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btnCreateRoom_clicked()
{

        chatServer = new ChatServer();
        chatServer->show();

}

void MainWindow::on_btnJoinRoom_clicked()
{
    if (chatServer->server->isListening()) {
        chatClient = new ChatClient();

        chatClient->setLineEditNick();

   //     chatClient->setLineEditPort("0000");

        chatClient->show();

        chatClient->setLineEditNameOwner(chatServer->nameOwner);

        chatClient->setTextEditRules(chatServer->rules);

        chatClient->setTimeStartRoom(chatServer->timeStart);
    }else {
        qDebug("Has no room!");
    }
}

void MainWindow::on_btnExit_clicked()
{
    QApplication::quit();
}
