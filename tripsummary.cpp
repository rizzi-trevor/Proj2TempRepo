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

    qry->prepare("SELECT souvenir, price, quantity, total FROM Purchases WHERE (tripID, stadium) = (:tripId, :college)");
    qry->bindValue(":tripId" , tripID);
    qry->bindValue(":college" , schoolName);
    if(qry->exec())
    {
        qDebug() << "on_school_comboBox_currentIndexChanged SUCCESS";
    }
    else
        qDebug() << "on_school_comboBox_currentIndexChanged FAIL";

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

    qry->prepare("SELECT stadium, distanceToNext FROM Trips WHERE tripID = (:tripId) ORDER BY tripProgress ASC");
    qry->bindValue(":tripId" , tripID);
    if(qry->exec())
    {
        qDebug() << "updateTripSchoolList SUCCESS";
    }
    else
        qDebug() << "updateTripSchoolList FAIL";

    model->setQuery(*qry);
    ui->tripOrder_tableView->setModel(model);
}



void tripSummary::updateSchoolComboBox()
{
    QSqlQueryModel* model=new QSqlQueryModel();

    QSqlQuery* qry=new QSqlQuery();
    qDebug() << tripID;

    qry->prepare("SELECT stadium FROM Trips WHERE tripID = (:tripId)");
    qry->bindValue(":tripId" , tripID);
    if(qry->exec())
    {
        qDebug() << "updateSchoolComboBox SUCCESS";
    }
    else
        qDebug() << "updateSchoolComboBox FAIL";


    model->setQuery(*qry);
    ui->school_comboBox->setModel(model);
}

void tripSummary::updateTotalDistance()
{
    QSqlQuery qry;
    int total;

   qDebug() << tripID;

   qry.prepare("SELECT SUM(DistanceToNext) FROM trips WHERE (tripID) = (:tripId)");
   qry.bindValue(":tripId" , tripID);

   if(qry.exec())
   {
       qDebug() << "updateTotalDistance SUCCESS";
   }
   else
       qDebug() << "updateTotalDistance FAIL";

   qry.next();

   total = qry.record().value(0).toInt();

   ui->totalDistanceDisplay_label->setText(QString::number(total) + " mi.");
}

void tripSummary::updateSchoolTotal()
{
     QSqlQuery qry;
     double total;

    qDebug() << tripID;

    qry.prepare("SELECT SUM(total) FROM Purchases WHERE (tripID, stadium) = (:tripId, :college)");
    qry.bindValue(":tripId" , tripID);
    qry.bindValue(":college" , ui->school_comboBox->currentText());

    if(qry.exec())
    {
        qDebug() << "updateSchoolTotal SUCCESS";
    }
    else
        qDebug() << "updateSchoolTotal FAIL";

    qry.next();

    total = qry.record().value(0).toDouble();

    ui->schoolTotalDisplay_label->setText('$' + QString::number(total));
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
        qDebug() << "updateTripTotal SUCCESS";
    }
    else
        qDebug() << "updateTripTotal FAIL";

    qry.next();

    total = qry.record().value(0).toDouble();

    ui->tripTotalDisplay_label->setText('$' + QString::number(total));
}
