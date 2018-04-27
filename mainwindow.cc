#include <QDebug>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "mytcpclient.h"

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

void MainWindow::on_comboBox_activated(const QString &arg1)
{
    qDebug() << arg1;
}

void MainWindow::on_pushButton_10_clicked()
{
    QTcpSocket socket(this);
    QByteArray ba;
    
    ba = "QUIT";
    socket.connectToHost("127.0.0.1",6161);
    socket.write(ba.data(),ba.length());
    
    qDebug() << "www";
}

void MainWindow::on_pushButton_clicked()
{
    if (ui->pushButton->text() == "Connect")
    {   ui->pushButton->setText("DissConnect");

        server = new MyTcpServer;
        server->doConnect(this);
    }
    else {
        ui->pushButton->setText("Connect");
        ui->logBox->addItem("Server disconnected!");
        server->close();
        delete server;
    }
}
