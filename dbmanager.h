#ifndef DBMANAGER_H
#define DBMANAGER_H

#include <QObject>
#include <QString>
#include <QSqlDatabase>

class DbManager
{
public:
    DbManager(const QString &path);
    ~DbManager();
    
    bool addNewThread(
        const QString &name,
        const QString &date,
        const QString &time,
        const QString &body,
        const QString &source);
        
    bool getThreadID(void);
    bool getThreadText(const QString &name, const QString &id);
    
    QSqlDatabase m_db;
    
    QString  dataBaseName;
    QVariant dataResult;
};

#endif // DBMANAGER_H
