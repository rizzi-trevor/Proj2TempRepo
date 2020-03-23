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

    updateSchoolComboBox();
    updateTripSchoolList();
    updateTotalDistance();
    updateTripTotal();
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

    qry->prepare("SELECT souvenir, price, quantity, total FROM Purchases WHERE (tripID, college) = (:tripId, :college)");
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

    updateSchoolTotal();

}




void tripSummary::updateTripSchoolList()
{
    QSqlQueryModel* model=new QSqlQueryModel();

    QSqlQuery* qry=new QSqlQuery();
    qDebug() << tripID;

    qry->prepare("SELECT college, distance FROM Trips WHERE tripID = (:tripId) ORDER BY tripProgess ASC");
    qry->bindValue(":tripId" , tripID);
    if(qry->exec())
    {
        qDebug() << "trip table updated.";
    }
    else
        qDebug() << "failed trip table";

    model->setQuery(*qry);
    ui->tripOrder_tableView->setModel(model);
}

void tripSummary::updateSchoolComboBox()
{
    QSqlQueryModel* model=new QSqlQueryModel();

    QSqlQuery* qry=new QSqlQuery();
    qDebug() << tripID;

    qry->prepare("SELECT college FROM Trips WHERE tripID = (:tripId) ORDER BY tripProgess ASC");
    qry->bindValue(":tripId" , tripID);
    if(qry->exec())
    {
        qDebug() << "trip table updated.";
    }
    else
        qDebug() << "failed trip table";

    model->setQuery(*qry);
    ui->school_comboBox->setModel(model);
}

void tripSummary::updateTotalDistance()
{
    QSqlQuery qry;
    int total;

   qDebug() << tripID;

   qry.prepare("SELECT SUM(distance) FROM trips WHERE (tripID) = (:tripId)");
   qry.bindValue(":tripId" , tripID);

   if(qry.exec())
   {
       qDebug() << "trip table updated.";
   }
   else
       qDebug() << "failed trip table";

   qry.next();

   total = qry.record().value(0).toInt();

   ui->schoolTotal_label->setText(QString::number(total) + " mi.");
}

void tripSummary::updateSchoolTotal()
{
     QSqlQuery qry;
     double total;

    qDebug() << tripID;

    qry.prepare("SELECT SUM(total) FROM Purchases WHERE (tripID, college) = (:tripId, :college)");
    qry.bindValue(":tripId" , tripID);
    qry.bindValue(":college" , ui->school_comboBox->currentText());

    if(qry.exec())
    {
        qDebug() << "trip table updated.";
    }
    else
        qDebug() << "failed trip table";

    qry.next();

    total = qry.record().value(0).toDouble();

    ui->schoolTotal_label->setText('$' + QString::number(total));
}

void tripSummary::updateTripTotal()
{

    QSqlQuery qry;
    double total;


    qDebug() << tripID;

    qry.prepare("SELECT SUM(total) FROM Purchases WHERE tripID = (:tripId)");
    qry.bindValue(":tripId" , tripID);
    if(qry.exec())
    {
        qDebug() << "trip table updated.";
    }
    else
        qDebug() << "failed trip table";

    qry.next();

    total = qry.record().value(0).toDouble();

    ui->tripTotalDisplay_label->setText('$' + QString::number(total));
}
