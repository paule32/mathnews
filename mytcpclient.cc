#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "mytcpclient.h"

MyClient::MyClient(QObject *parent) :
    QObject(parent)
{
    QThreadPool::globalInstance()->setMaxThreadCount(5);
}

void MyClient::setSocket(qintptr descriptor)
{
    // make a new socket
    socket = new QTcpSocket(this);

    qDebug() << "A new socket created!";

    connect(socket, SIGNAL(connected()), this, SLOT(connected()));
    connect(socket, SIGNAL(disconnected()), this, SLOT(disconnected()));
    connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()));

    socket->setSocketDescriptor(descriptor);

    win->ui->logBox->addItem(QString(
    "Client connected at %1").arg(descriptor));
}


// asynchronous - runs separately from the thread we created
void MyClient::connected()
{
    win->ui->logBox->addItem("Client connected event");
}

// asynchronous
void MyClient::disconnected()
{
    if (win != nullptr)
    win->ui->logBox->addItem(QString("Client disconnected."));
}

void MyClient::readyRead()
{
    qDebug() << "MyClient::readyRead()";
    qDebug() << socket->readAll();

    // Time consumer
    MyTask *mytask = new MyTask();
    mytask->setAutoDelete(true);
    
    // using queued connection
    connect(mytask,
        SIGNAL(Result(void)),
        this,
        SLOT(TaskResult(void)),
        Qt::QueuedConnection);

    win->ui->logBox->addItem(
    "Starting a new task using a thread from the QThreadPool");

    QThreadPool::globalInstance()->start(mytask);

}

void MyClient::TaskResult(void)
{
    QByteArray Buffer;
    Buffer.append("\r\nQUIT");
qDebug() << "qi";
    socket->write(Buffer);
}
