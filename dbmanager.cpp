#include "dbmanager.h"

DbManager::DbManager(const QString &path)
{
    myDB = QSqlDatabase::addDatabase("QSQLITE");

    myDB.setDatabaseName(path);

    if(!myDB.open())
    {
        qDebug() << "Error: can't connect to database!" << endl;

    }
    else
    {
        qDebug() << "Database: Connected" << endl;
    }

    QSqlQuery query;
    query.prepare("PRAGMA foreign_keys = ON");

    if(query.exec())
    {
        qDebug() << "foreign keys on" << endl;
    }


}

void DbManager::InitCollegeList(const QString &path)//path to the excel file
{
   QSqlDatabase fileDB = QSqlDatabase::addDatabase("QODBC", "xlsx_connection");
   fileDB.setDatabaseName("DRIVER={Microsoft Excel Driver (*.xls, *.xlsx, *.xlsm, *.xlsb)};DBQ=" + path);

   if(fileDB.open())
   {
       qDebug() << "Excel connection successful" << endl;

       QSqlQuery *query = new QSqlQuery(fileDB);
       query->exec("select * from [" + QString("Distances") + "$A1:A111]");   //Distances is the sheet name!

       QSqlQuery * querytoDb = new QSqlQuery(myDB);

       querytoDb->exec("CREATE TABLE Colleges ("
                       "collegeName TEXT);");

       QString compare = "";

       while(query->next())
       {

           if(myDB.open())
           {

               querytoDb->prepare("INSERT INTO Colleges(collegeName) values(:collegeName)");

               QString column1 = query->value(0).toString();

               if(compare != column1)
               {
                   querytoDb->bindValue(":collegeName",query->value(0).toString());
                   qDebug() << querytoDb->exec();

               }
               compare = column1;
           }
       }

       fileDB.close();
   }
}

void DbManager::initSouvenirList(const QString &path)
{
    QSqlDatabase fileDB = QSqlDatabase::addDatabase("QODBC", "xlsx_connection");
    fileDB.setDatabaseName("DRIVER={Microsoft Excel Driver (*.xls, *.xlsx, *.xlsm, *.xlsb)};DBQ=" + path);

    if(fileDB.open())
    {
        qDebug() << "Excel connection successful" << endl;

        QSqlQuery *query = new QSqlQuery(fileDB);
        query->exec("select * from [" + QString("Souvenirs") + "$A1:C61]");

        QSqlQuery * querytoDb = new QSqlQuery(myDB);

        querytoDb->exec("CREATE TABLE Souvenirs ("
                        "collegeName TEXT,"
                        "souvenirName TEXT,"
                        "cost FLOAT);");

        QString tempColumn1;
        QString check;

        while(query->next())
        {
            if(myDB.open())
            {
                querytoDb->prepare("INSERT INTO Souvenirs(collegeName, souvenirName, cost) VALUES(:collegeName, :souvenirName, :cost)");

                QString column1 = query->value(0).toString();
                check = column1;
                if(column1 == "" || column1 == " ")
                {
                    column1 = tempColumn1;
                }

                QString column2 = query->value(1).toString();

                float column3 = query->value(2).toFloat();

                if(check == "" && column2 != "")
                {
                    querytoDb->bindValue(":collegeName", column1);
                    querytoDb->bindValue(":souvenirName",column2);
                    querytoDb->bindValue(":cost",column3);
                    qDebug() << querytoDb->exec();

                }

                tempColumn1 = column1;
            }
        }
        fileDB.close();
    }
}

void DbManager::initDistanceList(const QString &path)
{
    QSqlDatabase fileDB = QSqlDatabase::addDatabase("QODBC", "xlsx_connection");
    fileDB.setDatabaseName("DRIVER={Microsoft Excel Driver (*.xls, *.xlsx, *.xlsm, *.xlsb)};DBQ=" + path);

    if(fileDB.open())
    {
        qDebug() << "Excel connection successful" << endl;

        QSqlQuery *query = new QSqlQuery(fileDB);
        query->exec("select * from [" + QString("Distances") + "$A2:C111]");

        QSqlQuery * querytoDb = new QSqlQuery(myDB);

        querytoDb->exec("CREATE TABLE Distances ("
                        "startCollege TEXT,"
                        "endCollege TEXT,"
                        "distance INTEGER);");

        while(query->next())
        {
            //QSqlDatabase myDB = QSqlDatabase::database("sqlite_connection");

            if(myDB.open())
            {
                querytoDb->prepare("INSERT INTO Distances(startCollege, endCollege, distance) VALUES(:startCollege, :endCollege, :distance)");

                QString column1 = query->value(0).toString();

                QString column2 = query->value(1).toString();

                int column3 = query->value(2).toInt();

                querytoDb->bindValue(":startCollege", column1);
                querytoDb->bindValue(":endCollege",column2);
                querytoDb->bindValue(":distance",column3);
                qDebug() << querytoDb->exec();
            }
        }
        fileDB.close();
    }
}

//QSqlDatabase::removeDatabase("xlsx_connection"); // need to put this out of scope of the initialised db


void DbManager::addUser(const QString &user, const QString &pass)
{
    QSqlQuery *query = new QSqlQuery(myDB);

   if(!userExists(user))
   {
    if(myDB.open())
    {
        query->exec("CREATE TABLE Logins ("
                    "Username TEXT,"
                    "Password TEXT);");

        query->prepare("INSERT INTO Logins(Username, Password) VALUES(:Username, :Password)");

        query->bindValue(":Username", user);
        query->bindValue(":Password", pass);
        qDebug() << query->exec();
    }
   }

}

bool DbManager::userExists(const QString &user)
{
    bool exists = false;

    QSqlQuery *checkQuery = new QSqlQuery(myDB);

    checkQuery->prepare("SELECT FROM Logins WHERE (Username) = (:Usernmae)");
    checkQuery->bindValue(":Username", user);

    if(checkQuery->exec())
    {
        if(checkQuery->next())
        {
                exists = true;
                QString userName = checkQuery->value("Username").toString();
                qDebug() << userName;
        }
    }
    else
    {
        qDebug() << "person exists failed: " << checkQuery->lastError();
    }

    return exists;
}

