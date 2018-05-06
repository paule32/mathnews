#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDate>
#include <QTime>
#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <QMainWindow>
#include <QLabel>
#include <QMovie>

#include "dbmanager.h"

#include "mytcpclient.h"
#include "mytcpserver.h"

namespace Ui {
class MainWindow;
}

class MyTcpServer;
class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
private slots:
    void readTcpData();
    void on_comboBox_activated(const QString &arg1);
    void on_pushButton_clicked();
    void on_actionExit_triggered();
    void on_actionAbout_triggered();
    
    void on_sendButton_clicked();
    void on_postTreeWidget_itemPressed(QTreeWidgetItem *item, int column);
    void on_replyButton_clicked();
    
    void on_solveButton_clicked();
    
public:
    MyTcpServer * server = nullptr;
    MyTcpClient * client = nullptr;
    
    QTreeWidgetItem * item;
    QTcpSocket * socket = nullptr;
    
    DbManager  * database = nullptr;
    
    QDate date;
    QTime time;
    
    QString title;
    QString thread_string;
    QString thread_id;
        
    Ui::MainWindow *ui;
};

extern MainWindow *win;

#endif // MAINWINDOW_H
