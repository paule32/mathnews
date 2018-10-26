#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDate>
#include <QTime>
#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <QMainWindow>
#include <QLabel>
#include <QMovie>

#include "mathwebpage.h"

namespace Ui {
class MainWindow;
}

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
    void on_actioncatch_triggered();
    void on_pushButton_2_clicked();

protected slots:
    void downProgress(int progress);
    void downProgressEnd(bool);

public:
    QTreeWidgetItem * item;
    
    QDate date;
    QTime time;
    
    QString title;
    QString thread_string;
    QString thread_id;

    QWebEngineProfile * web_profile = nullptr;
    QWebEngineView    * web_view    = nullptr;

    MathWebPage       * web_page    = nullptr;
        
    Ui::MainWindow *ui;
};

extern MainWindow *win;

#endif // MAINWINDOW_H
