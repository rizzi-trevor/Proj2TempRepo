#include "tripplanner.h"
#include "ui_tripplanner.h"

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

    if(!collegeDoesExist(startingStadium)) // checks if the user input a correct college
    {
        this->ui->warningLabel->setText("Please enter a college that you have selected on the left!");
    }
    else
    {
        //updateSouvTable(startingCollege);
        //updateCollegeTable(startingCollege);

        qDebug() << myDb.tripIdExists(tripID);
        qDebug() << tripID;
        if(tripID.size() == 3 && !myDb.tripIdExists(tripID))
        {
            this->ui->warningLabel->setText("");
            //this->ui->tripWarning->setText("");
            plannedColleges.clear();
            id = tripID;
            planAlgorithm(startingStadium, distance); // will plan the trip
            distanceTo << 0; // adds 0 for distance to next college at last college
            for(int index = 0; index < plannedColleges.size(); index++)
            {
                myDb.addTrip(tripID, plannedColleges[index], index, distanceTo[index]); // uploads trip to DB
            }
            showTrip(tripID);

            QString out = QString::number(distance);
            //this->ui->dist->setText(out);

            //tripSummary *summary = new tripSummary(this);
            //summary->show();
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

}

void tripPlanner::planAlgorithm(QString start, int dist)// start is the user selected starting stadium
{

    performDijkstra(selectedColleges, id);

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
