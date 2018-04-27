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
    QObject(parent)
{
}

void MyTcpServer::startServer()
{
    QHostAddress addr("127.0.0.1");
    tcpServer = new QTcpServer;
    
    if (!tcpServer->listen(addr, 6161))
    return;
        
    connect(tcpServer,
        &QTcpServer::newConnection, this ,
        &MyTcpServer::incomingConnection);
}

void MyTcpServer::incomingConnection()
{
    QByteArray ba;
    QDataStream out(&ba, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_10);
    
    out << "Hello World";
    
    QTcpSocket *client = tcpServer->nextPendingConnection();
    connect(client, &QAbstractSocket::disconnected,
            client, &QObject::deleteLater);
            
    client->write(ba);
    client->disconnectFromHost();
    
    qDebug() << "Server: " << ba;

#if 0    
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
#endif
}
