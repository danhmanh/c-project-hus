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

void MainWindow::on_btnNewRoom_clicked()
{
     QString myText = ui->lineEditName->text();
    chatServer = new ChatServer();
    chatServer->name = ui->lineEditName->text();
    chatServer->setLabelText(myText);
    chatServer->show();
    qDebug() <<chatServer->name;
    ui->btnNewRoom->setEnabled(false);
    ui->btnCloseRoom->setEnabled(true);
    this->hide();
}



void MainWindow::on_btnGo_clicked()
{
    ui->btnNewRoom->setEnabled(true);
    ui->btnGo->setEnabled(false);
    ui->lineEditName->setEnabled(false);
    ui->lblName->setText("Hello " + ui->lineEditName->text());

}


void MainWindow::on_btnCloseRoom_clicked()
{
    QApplication::quit();
    ui->btnNewRoom->setEnabled(true);
}
