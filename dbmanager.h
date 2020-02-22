#ifndef DBMANAGER_H
#define DBMANAGER_H

#include <QAbstractItemModel>
#include <QtSql>
#include <QDebug>
#include <QFileInfo>
#include "QSqlDatabase" //?
#include "QSqlQuery"//?
#include "QDebug"//?

class DbManager
{


public:
    DbManager(const QString &path);

    void InitCollegeList(const QString &path);


private:

    QSqlDatabase myDB;
};

#endif // DBMANAGER_H
