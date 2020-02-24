#include "adminwindow.h"
#include "ui_adminwindow.h"
#include "confirmpage.h"

AdminWindow::AdminWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AdminWindow)
{
    ui->setupUi(this);
}

AdminWindow::~AdminWindow()
{
    delete ui;
}


void AdminWindow::onInitialise()
{
    confirmpage confirm;
    bool check = false;

    confirm.setModal(true);
    confirm.exec();
    check = confirm.getData();

    if(check)
    {
        myDb.clearDb();

        myDb.InitCollegeList("C:/Users/Trevor Rizzi/Desktop/College-Touring/College Campus Distances and Souvenirs.xlsx");

        myDb.initSouvenirList("C:/Users/Trevor Rizzi/Desktop/College-Touring/College Campus Distances and Souvenirs.xlsx");

        myDb.initDistanceList("C:/Users/Trevor Rizzi/Desktop/College-Touring/College Campus Distances and Souvenirs.xlsx");
    }
    else
    {
        qDebug() << "Cancel!";
    }

}

void AdminWindow::clearCollegeData()
{
    confirmpage confirm;
    bool check = false;

    confirm.setModal(true);
    confirm.exec();
    check = confirm.getData();

    if(check)
    {
        myDb.clearDb();
        qDebug() << "Database: clear";
    }
    else
    {
        qDebug() << "Cancel!";
    }
}
