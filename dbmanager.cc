#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlError>

#include <QDebug>

#include "dbmanager.h"

DbManager::DbManager(const QString &path)
{
    Q_UNUSED(path);
    
    m_db = QSqlDatabase::addDatabase("QSQLITE");
    m_db.setDatabaseName(QString(path + "/mathnews.db"));
    
    if (!m_db.open()) {
        QMessageBox::warning(0,
        "Error !!!",
        "connection with database fail.");
        return;
    }
}

DbManager::~DbManager()
{
    if (m_db.open())
    m_db.close();
}

bool
DbManager::addNewThread(
    const QString &name,
    const QString &date,
    const QString &time,
    const QString &body,
    const QString &source)
{
    bool success = false;
    QSqlQuery query;

    QString req =
    QString(
    "INSERT INTO thread (name,datum,zeit,body,source)"
    " VALUES (:tname,:tdate,:ttime,:tbody,:tsource)");
    
    query.prepare(req);
    
    query.bindValue(":tname"  , name  );
    query.bindValue(":tdate"  , date  );
    query.bindValue(":ttime"  , time  );
    query.bindValue(":tbody"  , body  );
    query.bindValue(":tsource", source);
    
    if (query.exec()) {
        qDebug() << "new data ok.";
        success = true;
    }
    else {
        qDebug()
        << "db.add thread error:  "
        << query.lastError().text();
    }
    
    return success;
}

bool DbManager::getThreadID(void)
{
    bool success = false;
    QSqlQuery query;

    QString req =
    QString("SELECT name FROM lastid");
    
    query.prepare(req);
    if (query.exec()) {
        QSqlRecord rec = query.record();
        int rn = rec.indexOf("name");
        
        qDebug() << "last: " << query.value(rn);
        success = true;
    }
    return success;
}

bool DbManager::getThreadText(const QString &name, const QString &id)
{
    bool success = false;
    QSqlQuery query;
    
    QString req =
    QString("SELECT * FROM thread WHERE threadname = (:name) AND id = (:id)");

    query.prepare(req);
    query.bindValue(":name", name);
    query.bindValue(":id", id);
    
    if (query.exec())
    {
        QSqlRecord rec = query.record();
        int tn = rec.indexOf("threadname");
        
        qDebug() << query.value(tn);
        success = true;
    }
    else {
        qDebug()
        << "db.get thread error: "
        << query.lastError().text();
    }
    
    return success;
}
