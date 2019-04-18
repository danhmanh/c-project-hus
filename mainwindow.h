#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "chatserver.h"

#include "chatclient.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QString nickname;

private slots:
//    void on_btnNewRoom_clicked();
//    void on_btnGo_clicked();
//    void on_btnCloseRoom_clicked();

    void on_btnCreateRoom_clicked();

    void on_btnJoinRoom_clicked();

    void on_btnExit_clicked();

private:
    Ui::MainWindow *ui;

    ChatServer *chatServer;

    ChatClient *chatClient;
};

#endif // MAINWINDOW_H
