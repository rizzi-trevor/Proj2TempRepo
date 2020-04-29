#include "adminwindow.h"
#include "ui_adminwindow.h"
#include "confirmpage.h"
#include "loginwindow.h"

AdminWindow::AdminWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AdminWindow)
{
    ui->setupUi(this);
    updateCollegeTable();
    updateSouvenirTable();
    updateCombo();
    souvTable();
}

AdminWindow::~AdminWindow()
{
    delete ui;
}

void AdminWindow::updateCollegeTable() //CHANGE FUNC NAME
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

void AdminWindow::updateSouvenirTable() // CHANGE FUNC NAME
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

        //myDb.InitCollegeList(PROJECT_PATH + "/College_Campus_Distances_and_Souvenirs.xlsx");

        myDb.initMlbList(PROJECT_PATH + "/MLB_Information.xlsx");
        myDb.initStadiumList(PROJECT_PATH + "/Distance_between_stadiums.xlsx");
        myDb.createSouvTable();
        //myDb.initSouvenirList(PROJECT_PATH + "/College_Campus_Distances_and_Souvenirs.xlsx");

       // myDb.initDistanceList(PROJECT_PATH + "/College_Campus_Distances_and_Souvenirs.xlsx");
    }
    else
    {
        qDebug() << "Cancel!";
    }

    updateCollegeTable();
    updateSouvenirTable();
        updateCombo();

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
        myDb.addColleges(PROJECT_PATH + "/Distance_between_expansion_stadium.xlsx");
    }
    else
    {
        qDebug() << "Cancel!";
    }

    updateCollegeTable();
    updateSouvenirTable();
    updateCombo();
}

void AdminWindow::on_souvenirView_clicked(const QModelIndex &index)
{


}

void AdminWindow::on_removeSouvenir_2_clicked()
{

}

void AdminWindow::on_pushButton_5_released()
{
    hide();

    LoginWindow *mainWindow = new LoginWindow();
    mainWindow->show();

}

void AdminWindow::on_pushButton_2_clicked()
{

}

void AdminWindow::on_addMLB_clicked()
{
    confirmpage confirm;
    bool check = false;

    confirm.setModal(true);
    confirm.exec();
    check = confirm.getData();

    if(check)
    {
        myDb.addMLB(PROJECT_PATH + "/MLB_Information_Expansion.xlsx");
    }
    else
    {
        qDebug() << "Cancel!";
    }

    updateCollegeTable();
    updateSouvenirTable();
    updateCombo();
}

void AdminWindow::updateCombo()
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

void AdminWindow::on_searchButton_clicked()
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

void AdminWindow::on_showALL_clicked()
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

void AdminWindow::on_showStadiums_clicked()
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

void AdminWindow::on_showStadiums_2_clicked()
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

void AdminWindow::on_pushButton_3_clicked()
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

void AdminWindow::on_pushButton_4_clicked()
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

void AdminWindow::on_pushButton_6_clicked()
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

void AdminWindow::souvTable()
{
    QSqlQueryModel* model=new QSqlQueryModel();

    QSqlQuery* qry=new QSqlQuery();

    qry->prepare("SELECT * FROM souvenirs ORDER BY TeamName ASC");

    if(qry->exec())
    {
        qDebug() << "REAL table updated.";
    }

    model->setQuery(*qry);

    ui->souTable->setModel(model);
    ui->souTable->setColumnWidth(0, 220);



}

void AdminWindow::on_pushButton_7_clicked()
{
    addSouvenir adding;
    adding.setModal(true);
    adding.exec();

    myDb.reOpen();
    souvTable();
}

void AdminWindow::on_souTable_clicked(const QModelIndex &index)
{
    if(index.isValid())
        {
            int row = index.row();
            QString firstText = index.sibling(row, 0).data().toString();
            QString secondText = index.sibling(row, 1).data().toString();
            souve = index.sibling(row, 1).data().toString();
            double thirdText = index.sibling(row, 2).data().toDouble();

            ui->removeEdit->setText(secondText);
            ui->labelCollege->setText(firstText);
            ui->priceSpin->setValue(thirdText);

            qDebug() << firstText << " " << secondText << " " << thirdText << endl;
            qDebug() << index << endl;
        }

    bool open = myDb.isOpen();

    if(open)
        qDebug() << "DB OPEN!";
    else
        qDebug() << "DB CLOSE!";
}

void AdminWindow::on_pushButton_8_clicked()
{
        bool success = false;
        confirmpage confirm;
        bool check = false;


        bool open = myDb.isOpen();

        if(open)
            qDebug() << "DB OPEN!";
        else
            qDebug() << "DB CLOSE!";

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

        souvTable();
}

void AdminWindow::on_updateButton_clicked()
{
    bool success = false;
        confirmpage confirm;
        bool check = false;

        if(ui->removeEdit->text() == "")
        {
            ui->removeEdit->setPlaceholderText("souvenir name empty!");
            success = true;
        }

        if(!success)
        {
            confirm.setModal(true);
            confirm.exec();
            check = confirm.getData();
        }


        if(!myDb.souExists(ui->removeEdit->text(), ui->labelCollege->text()))
        {
            if(!success && check)
            {
                myDb.updateSou(souve, ui->labelCollege->text(),ui->priceSpin->value(), ui->removeEdit->text());
            }
            else
            {
                qDebug() << "remove didn't work!";
            }
        }
        else if(souve == ui->removeEdit->text())
        {
            if(!success && check)
            {
                myDb.updateSou(souve, ui->labelCollege->text(),ui->priceSpin->value(), ui->removeEdit->text());
            }
            else
            {
                qDebug() << "remove didn't work!";
            }
        }

        souvTable();

}
