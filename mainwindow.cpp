#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "chatserver.h"

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

void MainWindow::on_pushButton_clicked()
{
//    ChatServer chatServer;
//    chatServer.show();
//    chatServer.setVisible(true);
    chatServer = new ChatServer();
    chatServer->show();

}
