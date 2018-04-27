#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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
    void on_comboBox_activated(const QString &arg1);
    void on_pushButton_clicked();
    void on_pushButton_10_clicked();
    
public:
    MyTcpServer * server = nullptr;
    MyTcpClient * client = nullptr;
    
    Ui::MainWindow *ui;
};

extern MainWindow *win;

#endif // MAINWINDOW_H
