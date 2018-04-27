#ifndef MYTCPSERVER_H
#define MYTCPSERVER_H

#include <QObject>
#include <QtNetwork/QTcpSocket>
#include <QtNetwork/QTcpServer>
#include <QtNetwork/QAbstractSocket>
#include <QDebug>

#include "mainwindow.h"

class MainWindow;
class MyTcpServer : public QObject
{
    Q_OBJECT
public:
    explicit MyTcpServer(QObject *parent = 0);
    void startServer();
    
private slots:
    void incomingConnection();
    
public:
    QTcpServer * tcpServer = nullptr;
};

#endif // MYTCPSERVER_H
