#include <QObject>
#include <QByteArray>
#include <QMessageBox>
#include <QtNetwork/QTcpSocket>
#include <QtNetwork/QTcpServer>
#include <QtNetwork/QAbstractSocket>
#include <QDebug>

#include "mytcpserver.h"
#include "mytcpclient.h"

#include "mainwindow.h"
#include "ui_mainwindow.h"

QString list = "215 list of newsgroups follows\r\n";

MyTcpServer::MyTcpServer(QObject *parent) :
    QTcpServer(parent)
{
}

void MyTcpServer::doConnect(MainWindow *win)
{
    if(!listen(QHostAddress::Any, 6161))
    {
        win->ui->pushButton->setText("Connect");
        win->ui->logBox->addItem(
            "Error: "
            "Server could not start.");
        close();
    }
    else
    {
        win->ui->pushButton->setText("DissConnect");
        win->ui->logBox->addItem("Server started!");
    }
}

void MyTcpServer::incomingConnection(qintptr socketDescriptor)
{
    QByteArray ba;
    QString str;
    
    MyClient *client = new MyClient(this);
    client->setSocket(socketDescriptor);
    
    ba  = client->socket->read(20);
    str = ba.data();
    
    qDebug() << "server: " << str << ba;
    if (str == "QUIT") {
        ba = "205 closing connection";
        client->socket->write(ba);
        client->socket->close();
        qDebug() << "quiter close";
    }
}
