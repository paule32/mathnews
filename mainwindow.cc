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
    
    client = new MyTcpClient;
    client->setSocket();
}

void MainWindow::on_pushButton_clicked()
{
    if (server == nullptr) {
        server = new MyTcpServer;
        server->startServer();
        
        if (server->tcpServer->isListening()) {
            ui->pushButton->setText("DissConnect");
            ui->logBox->addItem("Server started!");
        }
        else {
            ui->pushButton->setText("Connect");
            ui->logBox->addItem(
            "Error: Server could not start.");
            delete server;
            server = nullptr;
        }
    }
    else {
        server->tcpServer->close();
        
        ui->pushButton->setText("Connect");
        ui->logBox->addItem("Server offline.");
        
        delete server;
        server = nullptr;
    }
}
