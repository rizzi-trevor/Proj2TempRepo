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

         currentCol = trip[counter];

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
         currentCol = trip[counter];

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

    QSqlQueryModel* model=new QSqlQueryModel();

    QSqlQuery* qry=new QSqlQuery();

    qry->prepare("SELECT souvenir, quantity, total FROM Cart");

    if(qry->exec())
    {
        qDebug() << "college1 table updated.";
    }
    else
        qDebug() << "failed";

    model->setQuery(*qry);

    ui->cartTable->setModel(model);
}

void tripprogress::updateTotal()
{
    QSqlQueryModel* model=new QSqlQueryModel();

    QSqlQuery* qry=new QSqlQuery();

    qry->prepare("SELECT SUM(total) FROM Cart");

    if(qry->exec())
    {
        qDebug() << "college1 table updated.";
    }
    else
        qDebug() << "failed";

    model->setQuery(*qry);

    ui->totalView->setModel(model);
}

void tripprogress::on_souvTable_clicked(const QModelIndex &index)
{

    if(index.isValid())
    {
        row = index.row();
        souvenirName = index.sibling(row, 0).data().toString();
        souvenirPrice = index.sibling(row, 1).data().toDouble();

        qDebug() << endl;

        qDebug() << tripID << " " << currentCol;
        qDebug() << souvenirName << " " << souvenirPrice << endl;
        qDebug() << index << endl;

    }

}

void tripprogress::on_addCart_clicked()
{
    int count = 1;
    int counter = myDb.cartQuantity(currentCol, souvenirName);

    if(counter == 0)
    {
        myDb.addCart(tripID,currentCol,souvenirName, souvenirPrice,count);
    }
    else
    {
        counter++;


        myDb.updateCart(currentCol,souvenirName,counter);
        qDebug() << counter;

    }
    updateTotal();
    updateCart();
}


void tripprogress::on_pushButton_4_released()
{
    myDb.addPurchase();
    myDb.resetCart();
}

void tripprogress::on_removeCart_clicked()
{
    myDb.removeCart(currentCol, souvenirName);
    updateCart();
    updateTotal();
}
