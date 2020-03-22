#include "tripprogress.h"
#include "ui_tripprogress.h"

tripprogress::tripprogress(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::tripprogress)
{
    ui->setupUi(this);
    counter = -1;


}

tripprogress::~tripprogress()
{
    delete ui;
}

void tripprogress::onLoadClick()
{
    QSqlQuery* qry=new QSqlQuery();

    qry->prepare("SELECT college FROM Trips WHERE tripID = (:tripId)");
    qry->bindValue(":tripId" , tripID);

    trip.clear();

    if(!qry->exec())
    {
        qDebug() << "tripProgress initializeList query failed";


    }
    else
    {
        while(qry->next())
        {
                QString temp = qry->value("college").toString();
                trip << temp;
        }

    }
    qDebug() << trip;

    max = trip.size();

    nextTrip();

    this->ui->load->deleteLater();
}

void tripprogress::nextTrip()// shows next college in trip
{
    QSqlQueryModel* model=new QSqlQueryModel();

    QSqlQuery* qry=new QSqlQuery();

    counter++;

    if( counter < max)
    {

         QString curCol;

         curCol = trip[counter];

         this->ui->label->setText("CURRENTLY AT: " + curCol);

         qry->prepare("SELECT souvenirName, cost FROM Souvenirs WHERE collegeName = (:collegeName)");
         qry->bindValue(":collegeName", curCol);

         if(qry->exec())
         {
             qDebug() << "souvenir table updated.";
         }

         model->setQuery(*qry);

         ui->souvTable->setModel(model);
         ui->souvTable->resizeColumnsToContents();

    }
    else
    {
        counter--;
    }


}


void tripprogress::prevTrip() // shows prev college in trip
{
    QSqlQueryModel* model = new QSqlQueryModel();

    QSqlQuery* qry=new QSqlQuery();

    counter--;

    if( counter >= 0)
    {

         QString curCol;

         curCol = trip[counter];

         this->ui->label->setText("CURRENTLY AT: " + curCol);

         qry->prepare("SELECT souvenirName, cost FROM Souvenirs WHERE collegeName = (:collegeName)");
         qry->bindValue(":collegeName", curCol);

         if(qry->exec())
         {
             qDebug() << "souvenir table updated.";
         }

         model->setQuery(*qry);

         ui->souvTable->setModel(model);
         ui->souvTable->resizeColumnsToContents();
    }
    else
    {
        counter++;
    }

}

void tripprogress::displaySouv()
{
    QSqlQueryModel* model = new QSqlQueryModel();

    QSqlQuery* qry=new QSqlQuery();

    qry->prepare("SELECT souvenirName FROM Souvenirs WHERE collegeName = (:startCollege)");
    qry->bindValue(":startCollege", currentCol);

    if(qry->exec())
    {
        qDebug() << "college table updated.";
    }
    else
        qDebug() << "failed";

    model->setQuery(*qry);

    ui->souvTable->setModel(model);
    ui->souvTable->setColumnWidth(20, 400);

}

void tripprogress::onNextClick()
{
    nextTrip();
}

void tripprogress::onPrevClick()
{
    prevTrip();
}

void tripprogress::updateCart()
{

    // unfinished :/

}
