#include "adminwindow.h"
#include "ui_adminwindow.h"
#include "confirmpage.h"

AdminWindow::AdminWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AdminWindow)
{
    ui->setupUi(this);
    updateCollegeTable();
    updateSouvenirTable();
}

AdminWindow::~AdminWindow()
{
    delete ui;
}

void AdminWindow::updateCollegeTable()
{
    QSqlQueryModel* model=new QSqlQueryModel();

    QSqlQuery* qry=new QSqlQuery();

    qry->prepare("SELECT * FROM Distances");

    if(qry->exec())
    {
        qDebug() << "college table updated.";
    }

    model->setQuery(*qry);

    ui->collegeView->setModel(model);
    ui->collegeView->setColumnWidth(0, 300);
}

void AdminWindow::updateSouvenirTable()
{
    QSqlQueryModel* model=new QSqlQueryModel();

    QSqlQuery* qry=new QSqlQuery();

    qry->prepare("SELECT * FROM Souvenirs");

    if(qry->exec())
    {
        qDebug() << "souvenir table updated.";
    }

    model->setQuery(*qry);

    ui->souvenirView->setModel(model);
    ui->souvenirView->setColumnWidth(0, 220);
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

        myDb.InitCollegeList(PROJECT_PATH + "/College_Campus_Distances_and_Souvenirs.xlsx");

        myDb.initSouvenirList(PROJECT_PATH + "/College_Campus_Distances_and_Souvenirs.xlsx");

        myDb.initDistanceList(PROJECT_PATH + "/College_Campus_Distances_and_Souvenirs.xlsx");
    }
    else
    {
        qDebug() << "Cancel!";
    }

    updateCollegeTable();
    updateSouvenirTable();

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

    updateCollegeTable();
    updateSouvenirTable();
}

void AdminWindow::on_addSouvenir_released()
{
    addSouvenir adding;
    adding.setModal(true);
    adding.exec();


    updateSouvenirTable();
}

void AdminWindow::on_removeSouvenir_released()
{
    bool success = false;
    confirmpage confirm;
    bool check = false;

    if(ui->removeEdit->text() == "")
    {
        ui->removeEdit->setPlaceholderText("souvenir name empty!");
        success = true;
    }

    if(!myDb.souExists(ui->removeEdit->text(), ui->labelCollege->text()))
    {
       ui->removeEdit->setText("");
       ui->removeEdit->setPlaceholderText("souvenir doesn't exist!");
       success = true;
    }

    if(!success)
    {
        confirm.setModal(true);
        confirm.exec();
        check = confirm.getData();
    }

    if(myDb.souExists(ui->removeEdit->text(), ui->labelCollege->text()) && !success && check)
    {
        myDb.removeSou(ui->removeEdit->text(), ui->labelCollege->text());
        ui->removeEdit->setText("");
        ui->removeEdit->setPlaceholderText("souvenir name");
    }
    else
    {
        qDebug() << "remove didn't work!";
    }

    updateSouvenirTable();
}

void AdminWindow::onAddColleges()
{
    confirmpage confirm;
    bool check = false;

    confirm.setModal(true);
    confirm.exec();
    check = confirm.getData();

    if(check)
    {
        myDb.addColleges(PROJECT_PATH + "/College_Campus_Distances_and_Souvenirs.xlsx");
    }
    else
    {
        qDebug() << "Cancel!";
    }

    updateCollegeTable();
    updateSouvenirTable();
}

void AdminWindow::on_souvenirView_clicked(const QModelIndex &index)
{

    if(index.isValid())
    {
        int row = index.row();
        QString firstText = index.sibling(row, 0).data().toString();
        QString secondText = index.sibling(row, 1).data().toString();
        double thirdText = index.sibling(row, 2).data().toDouble();

        ui->removeEdit->setText(secondText);
        ui->labelCollege->setText(firstText);
        ui->priceSpin->setValue(thirdText);

        qDebug() << firstText << " " << secondText << " " << thirdText << endl;
        qDebug() << index << endl;
    }

}

void AdminWindow::on_removeSouvenir_2_clicked()
{
    bool success = false;
    confirmpage confirm;
    bool check = false;

    if(ui->removeEdit->text() == "")
    {
        ui->removeEdit->setPlaceholderText("souvenir name empty!");
        success = true;
    }

    if(!myDb.souExists(ui->removeEdit->text(), ui->labelCollege->text()))
    {
       ui->removeEdit->setText("");
       ui->removeEdit->setPlaceholderText("souvenir doesn't exist!");
       success = true;
    }

    if(!success)
    {
        confirm.setModal(true);
        confirm.exec();
        check = confirm.getData();
    }

    if(myDb.souExists(ui->removeEdit->text(), ui->labelCollege->text()) && !success && check)
    {
        myDb.updateSou(ui->removeEdit->text(), ui->labelCollege->text(),ui->priceSpin->value());
        ui->removeEdit->setText("");
        ui->removeEdit->setPlaceholderText("souvenir name");
    }
    else
    {
        qDebug() << "remove didn't work!";
    }

    updateSouvenirTable();
}
