#include <QMessageBox>

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "mytcpclient.h"

MyTcpClient::MyTcpClient(QObject *parent) :
    QObject(parent)
{

}

void MyTcpClient::setSocket(void)
{
    tcpSocket = new QTcpSocket(this);
    
    in.setDevice(tcpSocket);
    in.setVersion(QDataStream::Qt_5_10);
    
    connect(tcpSocket, &QIODevice::readyRead, this, &MyTcpClient::readyRead);
    connect(tcpSocket,
    QOverload<QAbstractSocket::SocketError>::of(&QAbstractSocket::error),
    this, &MyTcpClient::displayError);
    
    qDebug() << "A new socket created!";
}

void MyTcpClient::readyRead()
{
    in.startTransaction();
    
    QString input;
    in >> input;

    if (!in.commitTransaction())
    return;
    
    qDebug() << "client: " << input;
}

void MyTcpClient::displayError(QAbstractSocket::SocketError socketError)
{
    switch (socketError) {
    case QAbstractSocket::RemoteHostClosedError:
         break;
    case QAbstractSocket::HostNotFoundError:
        QMessageBox::information(0, "Fortune Client",
            "The host was not found. Please check the "
            "host name and port settings.");
        break;
    case QAbstractSocket::ConnectionRefusedError:
        QMessageBox::information(0, "Fortune Client",
            "The connection was refused by the peer. "
            "Make sure the fortune server is running, "
            "and check that the host name and port "
            "settings are correct.");
        break;
    default:
        QMessageBox::information(0, "Fortune Client",
        QString("The following error occurred: %1.")
            .arg(tcpSocket->errorString()));
        break;
    }
}
