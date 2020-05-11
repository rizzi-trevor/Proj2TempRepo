#include "tripplanner.h"
#include "ui_tripplanner.h"
#include <vector>

#include "QVBoxLayout"

tripPlanner::tripPlanner(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::tripPlanner)
{
    ui->setupUi(this);
    updateCombo();
    updateComboTwo();
    updateDistTable();
    updateMLBTable();
    initializeList();
    ui->startTrip->setEnabled(false);

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

void tripPlanner::onRoofClick()
{
    QSqlQueryModel* model=new QSqlQueryModel();

    QSqlQuery* qry=new QSqlQuery();

    qry->prepare("SELECT TeamName, StadiumName, RoofType FROM MLB WHERE RoofType = (:RoofType) ORDER BY TeamName ASC");
    qry->bindValue(":RoofType", "Open");

    if(qry->exec())
    {
        qDebug() << "souvenir table updated.";
    }

    model->setQuery(*qry);

    ui->souvenirView->setModel(model);
    ui->souvenirView->setModel(model);
    ui->souvenirView->resizeColumnsToContents();


}

void tripPlanner::onDateClick()
{
    QSqlQueryModel* model=new QSqlQueryModel();

    QSqlQuery* qry=new QSqlQuery();

    qry->prepare("SELECT TeamName, StadiumName, DataOpened FROM MLB ORDER BY DataOpened ASC");

    if(qry->exec())
    {
        qDebug() << "souvenir table updated.";
    }

    model->setQuery(*qry);

    ui->souvenirView->setModel(model);
    ui->souvenirView->setModel(model);
    ui->souvenirView->resizeColumnsToContents();

}

void tripPlanner::onSeatingClick()
{
    QSqlQueryModel* model=new QSqlQueryModel();

    QSqlQuery* qry=new QSqlQuery();

    qry->prepare("SELECT TeamName, StadiumName, SeatingCapacity FROM MLB ORDER BY SeatingCapacity ASC");

    if(qry->exec())
    {
        qDebug() << "souvenir table updated.";
    }

    model->setQuery(*qry);

    ui->souvenirView->setModel(model);
    ui->souvenirView->setModel(model);
    ui->souvenirView->resizeColumnsToContents();



}

void tripPlanner::onGreatClick()
{
    QSqlQueryModel* model=new QSqlQueryModel();

    QSqlQuery* qry=new QSqlQuery();

    qry->prepare("SELECT TeamName, StadiumName, max(DistanceField) FROM MLB ");

    if(qry->exec())
    {
        qDebug() << "souvenir table updated.";
    }

    model->setQuery(*qry);

    ui->souvenirView->setModel(model);
    ui->souvenirView->setModel(model);
    ui->souvenirView->resizeColumnsToContents();



}

void tripPlanner::onLeastClick()
{
    QSqlQueryModel* model=new QSqlQueryModel();

    QSqlQuery* qry=new QSqlQuery();

    qry->prepare("SELECT TeamName, StadiumName, min(DistanceField) FROM MLB ");

    if(qry->exec())
    {
        qDebug() << "souvenir table updated.";
    }

    model->setQuery(*qry);

    ui->souvenirView->setModel(model);
    ui->souvenirView->setModel(model);
    ui->souvenirView->resizeColumnsToContents();



}

void tripPlanner::initializeList()
{
    QSqlQuery *query = new QSqlQuery();

    checkBoxVector.clear();

    QWidget *container = new QWidget;
    QVBoxLayout *vBoxLayout = new QVBoxLayout;

    container->setLayout(vBoxLayout);

    ui->scrollArea->setWidget(container);



    query->prepare("SELECT DISTINCT begStadium FROM Distances");
    if(!query->exec())
    {
        qDebug() << "tripPlanner initializeList query failed";


    }
    else
    {
        while(query->next())
        {
            QCheckBox* checkBox = new QCheckBox(query->value(0).toString());
            checkBox->setCheckState(Qt::CheckState::Unchecked);
            checkBoxVector.push_back(checkBox);
            connect(checkBox, &QCheckBox::stateChanged, this, &tripPlanner::ChecboxChanged);
        }

        for(int i = 0; i < checkBoxVector.size(); i++)
        {
            vBoxLayout->addWidget(checkBoxVector[i]);
        }
    }
}

void tripPlanner::ChecboxChanged()
{

    qDebug() << "Signal caught";

    int checkedCount = 0;

    for(int i = 0; i < checkBoxVector.size(); i++)
    {
        if(checkBoxVector[i]->checkState() == Qt::CheckState::Checked)
        {
            checkedCount++;
        }
    }

    if(checkedCount == 11000)
    {
        for(int i = 0; i < checkBoxVector.size(); i++)
        {
            if(checkBoxVector[i]->checkState() == Qt::CheckState::Unchecked)
            {
                checkBoxVector[i]->setDisabled(true);
            }
            qDebug() << checkBoxVector[i] << endl;
        }
    }
    else
    {
        for(int i = 0; i < checkBoxVector.size(); i++)
        {
            checkBoxVector[i]->setDisabled(false);
        }
    }
}


void tripPlanner::selectedCollegeList()// creates a list of the selected colleges from the checked boxes
{
    selectedColleges.clear();
    QSqlQuery *query = new QSqlQuery();
    int i = 0;

    query->prepare("SELECT DISTINCT begStadium FROM Distances");
    if(!query->exec())
    {
        qDebug() << "tripPlanner initializeList query failed";


    }
    else
    {
        while(query->next())
        {
            if(checkBoxVector[i]->checkState() == Qt::CheckState::Checked)
            {
                QString temp = query->value("begStadium").toString();
                selectedColleges << temp;
                qDebug() << temp;
            }
            i++;
        }

    }

}

void tripPlanner::onPlanClick()
{
    distance = 0;
    QString startingStadium;
    QString tripID;
    startingStadium = this->ui->colName->currentText();
    tripID = this->ui->trip->text();

    selectedCollegeList();

    for(int i = 0; i < selectedColleges.size(); i++)
    {
        if(selectedColleges[i] != startingStadium)
        {
            remainingChoices.push_back(selectedColleges[i]);
        }
    }
    path.push_back(startingStadium);


    if(!collegeDoesExist(startingStadium)) // checks if the user input a correct stadium
    {
        this->ui->warningLabel->setText("Please enter a college that you have selected on the left!");
    }
    else
    {

        qDebug() << myDb.tripIdExists(tripID);
        qDebug() << tripID;
        if(tripID.size() == 3 && !myDb.tripIdExists(tripID))
        {
            this->ui->warningLabel->setText("");

            plannedColleges.clear();
            id = tripID;

            algorithm();

            distanceTo << 0; // adds 0 for distance to next college at last college

            myDb.reOpen();

            for(int index = 0; index < path.size(); index++)
            {
                myDb.addTrip(tripID, path[index], index, distNext[index]); // uploads trip to DB
            }


            qDebug() << path;

            showTrip(tripID);

            QString out = QString::number(distance);
            ui->startTrip->setEnabled(true);


        }
        else
        {
            qDebug() << "I AM HERE//idk ";
        }

    }

    for(int i = 0; i < plannedColleges.size(); i++)
    {
        qDebug() << plannedColleges[i];
    }

    path.clear();
    remainingChoices.clear();
    distNext.clear();

}

bool tripPlanner::collegeDoesExist(QString colName)// checks if a college is added to the trip
{
    for(int i = 0; i < selectedColleges.size(); i++)
    {
        if(colName == selectedColleges[i]) // only going once!!!!
        {
            qDebug() << "true";
            return true;
        }
    }

    return false;
}

bool tripPlanner::planDoesExist(QString colName) // checks if a college is in the planned list
{
    for(int i = 0; i < plannedColleges.size(); i++)
    {
        if(colName == plannedColleges[i])
        {
            return true;
        }
    }

    return false;
}

void tripPlanner::showTrip(QString ID)
{
    QSqlQueryModel* model=new QSqlQueryModel();

    QSqlQuery* qry=new QSqlQuery();
    qDebug() << ID;

    qry->prepare("SELECT stadium FROM Trips WHERE tripID = (:tripId)");
    qry->bindValue(":tripId" , ID);
    if(qry->exec())
    {
        qDebug() << "trip table updated.";
    }
    else
        qDebug() << "failed trip table";

    model->setQuery(*qry);

    //clear here?
    ui->window->setModel(new QSqlQueryModel());
    ui->window->setModel(model);
    ui->window->setColumnWidth(20, 400);
}

void tripPlanner::updateComboTwo()
{
    QSqlQueryModel* model=new QSqlQueryModel();

    QSqlQuery* qry=new QSqlQuery();

    qry->prepare("SELECT DISTINCT begStadium FROM Distances");

    if(qry->exec())
    {
        qDebug() << "college1 table updated.";
    }
    else
        qDebug() << "failed";

    model->setQuery(*qry);

    ui->colName->setModel(model);
}

void tripPlanner::onGraphInfoClick()
{
    info = new graphInfo;

    info->show();

}


void tripPlanner::algorithm()// start is the user selected starting college
{
    QStringList local;
    int closestDist = 100000;
    int closestIndex;
    int tempDist;

    if(remainingChoices.size() > 0)
    {
        for(int i = 0; i < remainingChoices.size(); i++)
        {
            local << path.back() << remainingChoices[i];
            tempDist = performDijkstra(local);
            if(tempDist < closestDist)
            {
                closestDist = tempDist;
                closestIndex = i;
            }

            local.clear();
        }

        distNext.push_back(closestDist);
        qDebug() << closestDist;
        path.push_back(remainingChoices.at(closestIndex));
        qDebug() << remainingChoices.at(closestIndex);
        remainingChoices.erase(remainingChoices.begin() + closestIndex);

        algorithm();

    }
    else
    {
        distNext.push_back(0);
    }


}

void tripPlanner::onStartTrip()
{
    this->hide();
    progress = new tripprogress(this, id);

    progress->show();

}
