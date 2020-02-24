#ifndef DBMANAGER_H
#define DBMANAGER_H

#include <QAbstractItemModel>
#include <QtSql>
#include <QDebug>
#include <QFileInfo>
#include "QSqlDatabase"
#include "QSqlQuery"
#include "QDebug"

class DbManager
{


public:
    DbManager(const QString &path);

    void InitCollegeList(const QString &path);

    void initSouvenirList(const QString &path);

    void initDistanceList(const QString &path);

    void addUser(const QString &user, const QString &pass);
    
    void addColleges(const QString &path);

    bool userExists(const QString &user);

    void clearDb();

    bool isOpen() const;

    bool checkAdmin(const QString &username) const;

    QString getPassword(const QString &username) const;


private:
    QSqlDatabase myDB;
};

#endif // DBMANAGER_H
