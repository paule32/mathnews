#ifndef MYTCPCLIENT_H
#define MYTCPCLIENT_H

#include <QObject>
#include <QtNetwork/QTcpSocket>
#include <QtNetwork/QAbstractSocket>
#include <QDataStream>
#include <QDebug>

#include "mytask.h"

class MyTcpClient : public QObject
{
    Q_OBJECT
public:
    explicit MyTcpClient(QObject *parent = 0);
    void setSocket(void);

signals:

public slots:
    void displayError(QAbstractSocket::SocketError socketError);
    void readyRead();

public:
    QTcpSocket * tcpSocket = nullptr;
    QDataStream in;

};

#endif // MYTCPCLIENT_H
