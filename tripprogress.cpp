#include "tripprogress.h"
#include "ui_tripprogress.h"

tripprogress::tripprogress(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::tripprogress)
{
    ui->setupUi(this);
    counter = -1;

    //Hiding previous
    ui->pushButton_2->hide();
    myDb.resetCart();

}

tripprogress::tripprogress(QWidget *parent, QString I_D)
    :QDialog(parent),
    ui(new Ui::tripprogress)
{
    tripID = I_D;

    ui->setupUi(this);
    counter = -1;

    //Hiding previous
    ui->pushButton_2->hide();
    myDb.resetCart();

}

tripprogress::~tripprogress()
{
    myDb.resetCart();

    delete ui;
}

void tripprogress::onLoadClick()
{
    QSqlQuery* qry=new QSqlQuery();

    qry->prepare("SELECT stadium FROM Trips WHERE tripID = (:tripId)");
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
                QString temp = qry->value("stadium").toString();
                trip << temp;
        }

    }
    qDebug() << trip;

    max = trip.size();

    nextTrip();

    this->ui->load->deleteLater();


    ui->addCart->setDisabled(false);
    ui->addCart->setDisabled(false);
    ui->removeCart->setDisabled(false);
    ui->pushButton_4->setDisabled(false);
    ui->pushButton_2->setDisabled(false);
    ui->pushButton->setDisabled(false);


    getDistance();
}

void tripprogress::nextTrip()// shows next college in trip
{
    myDb.resetCart();
    updateCart();
    updateTotal();

    QSqlQueryModel* model=new QSqlQueryModel();

    QSqlQuery* qry=new QSqlQuery();
    qDebug() << counter;
    counter++;

    if( counter < max)
    {

         QString curCol;

         curCol = trip[counter];

         currentCol = trip[counter];

         qry->prepare("SELECT TeamName FROM MLB WHERE StadiumName = (:stadiumName)");
         qry->bindValue(":stadiumName", trip[counter]);

         if(qry->exec())
         {
             teamName = qry->value(0).toString();
         }


         this->ui->label->setText("CURRENTLY AT: " + curCol);

         qry->prepare("SELECT SouvenirName, Price FROM Souvenirs WHERE TeamName = (:teamName)");
         qry->bindValue(":teamName", teamName);

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
        confirmpage confirm;
        bool check = false;

        confirm.setModal(true);
        confirm.exec();
        check = confirm.getData();

        if(check)
        {
            this->hide();
            tripSummary *summary = new tripSummary(tripID, this);

            summary->show();
        }
        else
        {
            counter--;
        }


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

         qry->prepare("SELECT SouvenirName, Price FROM Souvenirs WHERE TeamName = (:teamName)");
         qry->bindValue(":teamName", curCol);

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

void tripprogress::getDistance()
{
    QString distance;

    QSqlQuery* qry=new QSqlQuery();

    qry->prepare("SELECT distanceToNext From Trips WHERE (stadium) = (:stadium)");
    qry->bindValue(":stadium", currentCol);

    if(qry->exec())
    {
        while(qry->next())
        {
            distance = qry->value(0).toString();
        }

        if(counter+1 < max)
            distance = "Distance to " + trip[counter+1] + ": " + distance;
        else
            distance = "You're at the last stadium!";

        ui->distanceLabel->setText(distance);
        qDebug() << distance;
        qDebug() << "show next college!";
    }
    else
        qDebug() << "doesn't show next colelge!";
}

void tripprogress::displaySouv()
{
    QSqlQueryModel* model = new QSqlQueryModel();

    QSqlQuery* qry=new QSqlQuery();

    qry->prepare("SELECT SouvenirName FROM Souvenirs WHERE StadiumName = (:stadiumName)");
    qry->bindValue(":stadiumName", currentCol);

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
    getDistance();
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

    model->setHeaderData(0, Qt::Horizontal, tr("Cart Total") );

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
    confirmpage confirm;
    bool check;

    confirm.setModal(true);
    confirm.exec();
    check = confirm.getData();

    if(check)
    {
        myDb.addPurchase();
        myDb.resetCart();
    }
}

void tripprogress::on_removeCart_clicked()
{
    myDb.removeCart(currentCol, souvenirName);
    updateCart();
    updateTotal();
}
