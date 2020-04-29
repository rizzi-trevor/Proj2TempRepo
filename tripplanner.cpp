#include "tripplanner.h"
#include "ui_tripplanner.h"

#include "QVBoxLayout"

tripPlanner::tripPlanner(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::tripPlanner)
{
    ui->setupUi(this);
    updateCombo();
    updateDistTable();
    updateMLBTable();

}

tripPlanner::~tripPlanner()
{
    delete ui;
}

void tripPlanner::onTypologyClick()
{
    QString collegeName = "National";
    qDebug() << collegeName;

    QSqlQueryModel* model=new QSqlQueryModel();

    QSqlQuery* qry=new QSqlQuery();

    qry->prepare("SELECT TeamName, StadiumName, Ballpark FROM MLB ORDER BY Ballpark ASC");


    if(qry->exec())
    {
        qDebug() << "souvenir table updated.";
    }

    model->setQuery(*qry);

    ui->souvenirView->setModel(model);
    ui->souvenirView->setModel(model);
    ui->souvenirView->resizeColumnsToContents();

}

void tripPlanner::onAmericanClick()
{
    QString collegeName = "American";
    qDebug() << collegeName;

    QSqlQueryModel* model=new QSqlQueryModel();

    QSqlQuery* qry=new QSqlQuery();

    qry->prepare("SELECT * FROM MLB WHERE League = (:League) ORDER BY TeamName ASC");

    qry->bindValue(":League", collegeName);

    if(qry->exec())
    {
        qDebug() << "souvenir table updated.";
    }

    model->setQuery(*qry);

    ui->souvenirView->setModel(model);
    ui->souvenirView->setModel(model);
    ui->souvenirView->resizeColumnsToContents();
}

void tripPlanner::onShowClick()
{
    QSqlQueryModel* model=new QSqlQueryModel();

    QSqlQuery* qry=new QSqlQuery();

    qry->prepare("SELECT * FROM MLB");

    if(qry->exec())
    {
        qDebug() << "souvenir table updated.";
    }

    model->setQuery(*qry);

    ui->souvenirView->setModel(model);
    ui->souvenirView->setModel(model);
    ui->souvenirView->resizeColumnsToContents();


}

void tripPlanner::onNationalClick()
{
    QString collegeName = "National";
    qDebug() << collegeName;

    QSqlQueryModel* model=new QSqlQueryModel();

    QSqlQuery* qry=new QSqlQuery();

    qry->prepare("SELECT * FROM MLB WHERE League = (:League) ORDER BY StadiumName ASC");

    qry->bindValue(":League", collegeName);

    if(qry->exec())
    {
        qDebug() << "souvenir table updated.";
    }

    model->setQuery(*qry);

    ui->souvenirView->setModel(model);
    ui->souvenirView->setModel(model);
    ui->souvenirView->resizeColumnsToContents();

}

void tripPlanner::onStadiumsClick()
{
    QSqlQueryModel* model=new QSqlQueryModel();

    QSqlQuery* qry=new QSqlQuery();

    qry->prepare("SELECT TeamName, StadiumName FROM MLB ORDER BY StadiumName ASC");

    if(qry->exec())
    {
        qDebug() << "souvenir table updated.";
    }

    model->setQuery(*qry);

    ui->souvenirView->setModel(model);
    ui->souvenirView->setModel(model);
    ui->souvenirView->resizeColumnsToContents();

}

void tripPlanner::onTeamClick()
{
    QSqlQueryModel* model=new QSqlQueryModel();

    QSqlQuery* qry=new QSqlQuery();

    qry->prepare("SELECT TeamName, StadiumName FROM MLB ORDER BY TeamName ASC");

    if(qry->exec())
    {
        qDebug() << "souvenir table updated.";
    }

    model->setQuery(*qry);

    ui->souvenirView->setModel(model);
    ui->souvenirView->setModel(model);
    ui->souvenirView->resizeColumnsToContents();

}

void tripPlanner::updateCombo()
{
    QSqlQueryModel* model=new QSqlQueryModel();

    QSqlQuery* qry=new QSqlQuery();

    qry->prepare("SELECT DISTINCT TeamName FROM MLB");

    if(qry->exec())
    {
        qDebug() << "college1 table updated.";
    }
    else
        qDebug() << "failed";

    model->setQuery(*qry);

    ui->comboBox->setModel(model);
}


void tripPlanner::updateDistTable()
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
    ui->collegeView->resizeColumnsToContents();
}

void tripPlanner::updateMLBTable()
{
    QSqlQueryModel* model=new QSqlQueryModel();

    QSqlQuery* qry=new QSqlQuery();

    qry->prepare("SELECT * FROM MLB");

    if(qry->exec())
    {
        qDebug() << "souvenir table updated.";
    }

    model->setQuery(*qry);

    ui->souvenirView->setModel(model);
    ui->souvenirView->setModel(model);
    ui->souvenirView->resizeColumnsToContents();

}

void tripPlanner::onSearchClick()
{
    QString collegeName = this->ui->comboBox->currentText();
    qDebug() << collegeName;

    QSqlQueryModel* model=new QSqlQueryModel();

    QSqlQuery* qry=new QSqlQuery();

    qry->prepare("SELECT * FROM MLB WHERE TeamName = (:TeamName)");

    qry->bindValue(":TeamName", collegeName);

    if(qry->exec())
    {
        qDebug() << "souvenir table updated.";
    }

    model->setQuery(*qry);

    ui->souvenirView->setModel(model);
    ui->souvenirView->setModel(model);
    ui->souvenirView->resizeColumnsToContents();


}
