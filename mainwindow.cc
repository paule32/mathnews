#include <QApplication>
#include <QSettings>

#include <QPixmap>
#include <QBitmap>
#include <QCursor>

#include <QSqlQuery>
#include <QSqlRecord>

#include <QMessageBox>
#include <QDebug>

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "dbmanager.h"
#include "mytcpclient.h"
#include "symbolinputbox.h"

struct news {
    int post_new;
    int post_old;
    QTreeWidgetItem * item;
    QString text;
} news_items[] = {
    5, 0, nullptr, "text1",
    6, 0, nullptr, "text2",
    7, 0, nullptr, "text3",
    8, 5, nullptr, "re: text1",
    9, 5, nullptr, "re: text11",
   10, 7, nullptr, "resssst",
    0, 0, 0      , 0
};

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    win = this;
    
    QPixmap pix(":/cursor.png","PNG");
    pix.setMask(QBitmap(QPixmap(":/mask_cursor.png","PNG")));
    QCursor crs_normal(pix,9,9);    
    QApplication::setOverrideCursor(crs_normal);
    
    ui->symbolWidget->init();
    ui->inputBox->init();
    
    QHeaderView *pos1 = ui->postTreeWidget->header();
    pos1->resizeSection(0,300);
    
    ui->sendButton->setEnabled(false);
    
    ui->postTreeWidget->hideColumn(4);
    ui->postTreeWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->postTreeWidget->setSelectionMode(QAbstractItemView::SingleSelection);

    QTreeWidgetItem * item = nullptr;
    
    for (int p = 0; p < 6; ++p) {
        if (news_items[p].post_old == 0) {
            item = new QTreeWidgetItem;
            item->setText(0,news_items[p].text);
            
            news_items[p].item = item;
            
            ui->postTreeWidget
              ->topLevelItem(0)
              ->addChild(item);
        }
        else {
            for (int o = 0; o < 6; ++o) {
                int _old = news_items[p].post_old;
                int _new = news_items[o].post_new;
                
                if (_new == _old) {
                    qDebug() << news_items[p].text;
                    qDebug() << news_items[o].text;
                    
                    if (news_items[p].item == nullptr)
                        news_items[p].item =  ui->postTreeWidget->topLevelItem(0);
                    if (news_items[o].item == nullptr)
                        news_items[o].item =
                        news_items[p].item ;
                        
                    item = new QTreeWidgetItem(news_items[o].item);
                    item->setText(0,news_items[p].text);
                    
                    news_items[o].item->addChild(item);
                    news_items[o].item = item->parent();
                    break;
                }
            }
        }
    }

#if 0 
    database = new DbManager(QApplication::applicationDirPath());
    
    // prepare postlist with data ...
    QSqlQuery  query("SELECT * FROM thread");
    
    int fld1 = query.record().indexOf("id");
    int fld2 = query.record().indexOf("name");
    int fld3 = query.record().indexOf("body");
    int fld4 = query.record().indexOf("source");

    int pos  = 0;
    
    QTreeWidgetItem * mitem = nullptr;
    
//  int fe1 = 0;
//  query.first(); while (query.next()) fe1 = query.value(fld1).toInt();
//  query.last (); while (query.next()) fe2 = query.value(fld1).toInt();
    
    
    query.first();
    while (query.next())
    {
        int     f1 = query.value(fld1).toInt();
        QString f2 = query.value(fld2).toString();
        QString f3 = query.value(fld3).toString();
        int     f4 = query.value(fld4).toInt();

        news_items.resize(f1-1);
        
        mitem = new QTreeWidgetItem(ui->postTreeWidget);
        mitem->setText(0,f2);
        
        if (f4 == 0) {
            ui->postTreeWidget->addTopLevelItem(mitem);
            news_items.append(item);
            qDebug() << "added";
        }
        else { qDebug() << "nsss";
        ui
            ->postTreeWidget
            ->currentItem()
            ->insertChild(f4,item);
            news_items.append(item);
            qDebug() << "22222";
        }
    }
#endif
}

MainWindow::~MainWindow()
{
    QApplication::restoreOverrideCursor();
    delete database;
    delete ui;
}

void MainWindow::on_comboBox_activated(const QString &arg1)
{
    qDebug() << arg1;
    if (arg1 == "griechisches Alphabet")
    ui->symbolWidget->init(); else
    if (arg1 == "Zahlen")
    ui->symbolWidget->init_zahlen(); else
    
    if (arg1 == "Mathe Operatoren")
    ui->symbolWidget->init_operatoren();
}

void MainWindow::readTcpData()
{
    QByteArray data = socket->readAll();
    qDebug() << "FS: " << data;
}

void MainWindow::on_sendButton_clicked()
{
    QTcpSocket *socket;
    QByteArray ba;

    ba = "QUIT";
    
    socket = new QTcpSocket(this);
    connect( socket, SIGNAL(readyRead()), SLOT(readTcpData()) );
    socket->connectToHost("127.0.0.1",6161);
    
    if (socket->waitForConnected()) {
        socket->write(ba);
    }
    
    qDebug() << "www";
    
    if (ui->replyEditLine->text().trimmed().length() < 1
    ||  ui->replyEditLine->text().trimmed().length() > 100) {
        ui->replyEditLine->setText("<no reply text>");
        qDebug() << "invalid reply text.";
    }
    
    DbManager * db = new DbManager(QApplication::applicationDirPath());
    if (!db->addNewThread(
            ui->replyEditLine->text(),
            date.toString(),
            time.toString(),
            ui->inputBox->document()->toRawText(),
            thread_id))
    {        
        QMessageBox::warning(this,
        "Error !!!",
        "Database entry could not update.");
        delete db; return;
    }   delete db;
    
    ui->sendButton->setEnabled(false);
    
    auto * re_thread = new QTreeWidgetItem ;

    re_thread->setText(0, title);
    re_thread->setText(1, "UserRepler");
    re_thread->setText(2, date.toString());
    re_thread->setText(3, time.toString());
    re_thread->setText(4, thread_id);
        
    item->addChild(re_thread);
    item->setExpanded(true);
    item->setSelected(false);
    
    re_thread->setSelected(true);

    
//    client = new MyTcpClient;
//    client->setSocket();
}

void MainWindow::on_pushButton_clicked()
{
    if (server == nullptr) {
        server = new MyTcpServer;
        server->startServer();
        
        if (server->tcpServer->isListening()) {
            ui->pushButton->setText("DissConnect");
            ui->logBox->addItem("Server started!");
        }
        else {
            ui->pushButton->setText("Connect");
            ui->logBox->addItem(
            "Error: Server could not start.");
            delete server;
            server = nullptr;
        }
    }
    else {
        server->tcpServer->close();
        
        ui->pushButton->setText("Connect");
        ui->logBox->addItem("Server offline.");
        
        delete server;
        server = nullptr;
    }
}

void MainWindow::on_actionExit_triggered()
{
    close();
}

void MainWindow::on_actionAbout_triggered()
{
    QMessageBox::aboutQt(this);
}

void MainWindow::on_postTreeWidget_itemPressed(QTreeWidgetItem *item, int column)
{
    if (column == 0) {
        if (item->text(0) == "Willkommen"
        &&  item->text(1) == "Jens Kallup") {
            ui->inputBox->clear();
            ui->inputBox->appendPlainText("Viel Spaß !");
        }
    }
    
    thread_string = item->text(0);
    thread_id     = item->text(4).toInt();
    
    ui->replyEditLine->setText(thread_string);
}

void MainWindow::on_replyButton_clicked()
{
    item = ui->postTreeWidget->currentItem();
    
    if (item == nullptr
    ||  item->text(0).trimmed().length() < 1) {
        QMessageBox::warning(this,
        "Warning !!!",
        "Please select thread, to Reply.");
        return;
    }

    date = QDate::currentDate();
    time = QTime::currentTime();
    
    // check for selection - zitat ...
    QString cite = "data text";
    QString poster = "poster";
    
    if (cite.trimmed().length() > 0) {
        cite =
            QString("<p><font color='black'>Am %1, um %2 schrieb %3:<br><b>"
            "<font color='blue';>%4</font></b></font></p><p></p>").
            arg(date.toString()).
            arg(time.toString()).
            arg(poster).
            arg(cite);
       
        ui->inputBox->document()->clear();
        ui->inputBox->document()->setHtml(cite);
    }
    
         title = item->text(0);
    if (!title.contains("Re:"))
         title = title.insert(0,"Re: ");

    thread_id = item->text(4);
    
    ui->sendButton->setEnabled(true);
}

extern void start_calculation(void);
void MainWindow::on_solveButton_clicked()
{
    start_calculation();
}
