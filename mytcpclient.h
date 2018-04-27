#ifndef MYTCPCLIENT_H
#define MYTCPCLIENT_H

#include <QObject>
#include <QtNetwork/QTcpSocket>
#include <QtNetwork/QAbstractSocket>
#include <QThreadPool>
#include <QDebug>

#include "mytask.h"

class MyClient : public QObject
{
    Q_OBJECT
public:
    explicit MyClient(QObject *parent = 0);
    void setSocket(qintptr Descriptor);

signals:

public slots:
    void connected();
    void disconnected();
    void readyRead();

    void TaskResult(void);

public:
    QTcpSocket *socket;

};

#endif // MYTCPCLIENT_H
