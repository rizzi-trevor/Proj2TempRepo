#include "adminwindow.h"
#include "ui_adminwindow.h"

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
    myDb.clearDb();

    myDb.InitCollegeList("C:/Users/Trevor Rizzi/Desktop/College-Touring/College Campus Distances and Souvenirs.xlsx");

    myDb.initSouvenirList("C:/Users/Trevor Rizzi/Desktop/College-Touring/College Campus Distances and Souvenirs.xlsx");

    myDb.initDistanceList("C:/Users/Trevor Rizzi/Desktop/College-Touring/College Campus Distances and Souvenirs.xlsx");

}

void AdminWindow::clearCollegeData()
{
    myDb.clearDb();
    qDebug() << "Database: clear";

}
