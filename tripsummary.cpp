#include "tripsummary.h"
#include "ui_tripsummary.h"

tripSummary::tripSummary(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::tripSummary)
{
    ui->setupUi(this);
}

tripSummary::tripSummary(const QString &id, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::tripSummary)
{
    ui->setupUi(this);
    tripID = id;
}

tripSummary::~tripSummary()
{
    delete ui;
}

void tripSummary::on_school_comboBox_currentIndexChanged(const QString &schoolName)
{
    QSqlQueryModel* model=new QSqlQueryModel();

    QSqlQuery* qry=new QSqlQuery();
    qDebug() << tripID;

    qry->prepare("SELECT souvenir, price, quantity, total FROM purchases WHERE (tripID, college) = (:tripId, :college)");
    qry->bindValue(":tripId" , tripID);
    qry->bindValue(":college" , schoolName);
    if(qry->exec())
    {
        qDebug() << "";
    }
    else
    {
        qDebug() << "";
    }

    model->setQuery(*qry);

    //clear here?
    ui->souvenirsBySchool_tableView->setModel(model);
    //ui->tripOrder_tableView->setColumnWidth(20, 400);




}

void tripSummary::updateTripSchoolList()
{
    QSqlQueryModel* model=new QSqlQueryModel();

    QSqlQuery* qry=new QSqlQuery();
    qDebug() << tripID;

    qry->prepare("SELECT college FROM Trips WHERE tripID = (:tripId)");
    qry->bindValue(":tripId" , tripID);
    if(qry->exec())
    {
        qDebug() << "trip table updated.";
    }
    else
        qDebug() << "failed trip table";

    model->setQuery(*qry);

    //clear here?
    ui->tripOrder_tableView->setModel(model);
    ui->tripOrder_tableView->setColumnWidth(20, 400);
}
