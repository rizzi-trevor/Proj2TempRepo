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

void DbManager::initCollegeList(const QString &path)//path to the excel file
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
           //QSqlDatabase myDB = QSqlDatabase::database("sqlite_connection");


           if(myDB.open())
           {

               querytoDb->prepare("INSERT INTO Colleges(collegeName) values(:collegeName)");

               QString column1 = query->value(0).toString();

               if(compare != column1)
               {
                   querytoDb->bindValue(":collegeName",query->value(0).toString());
                   qDebug() << querytoDb->exec() << endl;
               }


               compare = column1;

           }
       }

       fileDB.close();

       //QSqlDatabase::removeDatabase("xlsx_connection"); // need to put this out of scope of the initialised db

   }




}

