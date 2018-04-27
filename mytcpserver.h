#ifndef MYTCPSERVER_H
#define MYTCPSERVER_H

#include <QObject>
#include <QtNetwork/QTcpSocket>
#include <QtNetwork/QTcpServer>
#include <QtNetwork/QAbstractSocket>
#include <QDebug>

#include "mainwindow.h"

class MainWindow;
class MyTcpServer : public QTcpServer
{
    Q_OBJECT
public:
    explicit MyTcpServer(QObject *parent = 0);
    void doConnect(MainWindow *win);
        
protected:
    void incomingConnection(qintptr socketDescriptor);    
    
signals:
    
public slots:
    
private:

};

#endif // MYTCPSERVER_H
