#ifndef TRIPPLANNER_H
#define TRIPPLANNER_H

#include <QDialog>
#include <QList>
#include "graphinfo.h"
#include "dbmanager.h"
#include <qcheckbox.h>
#include "tripsummary.h"
#include "tripprogress.h"

namespace Ui {
class tripPlanner;
}

class tripPlanner : public QDialog
{
    Q_OBJECT

public:
    /**
    * @brief default explicit Constructor
    *
    * Constructor sets up ui for tripPlanner
    * and executes initalizeList(), and updateCombo()
    * @param *parent - for QDialog
    */
    explicit tripPlanner(QWidget *parent = nullptr);

    /**
    * @brief Destructor
    *
    * Close the tripPlanner UI
    */
    ~tripPlanner();

    void updateCombo();

    void updateDistTable();

    void updateMLBTable();

    void selectedCollegeList();

    void planAlgorithm(QString start, int dist);

    bool collegeDoesExist(QString colName);

    bool planDoesExist(QString colName);

    void showTrip(QString ID);

    void updateComboTwo();


public slots:
    void onTypologyClick();

    void onAmericanClick();

    void onShowClick();

    void onNationalClick();

    void onStadiumsClick();

    void onTeamClick();

    void onSearchClick();

    void onRoofClick();

    void onDateClick();

    void onSeatingClick();

    void onGreatClick();

    void onLeastClick();

    void initializeList();

    void onPlanClick();

    void onGraphInfoClick();



private slots:
     void ChecboxChanged();


private:
    /**
    * @brief points to tripPlanner UI
    */
    Ui::tripPlanner *ui;

    /**
    * @brief assigns DB to predefined PROJECT_PATH constant
    */
    DbManager myDb = DbManager(PROJECT_PATH + "/college.db");

    tripprogress *progress;

    QVector<QCheckBox*> checkBoxVector;

    QStringList selectedColleges;

    QStringList plannedColleges;
    int distance;

    QString id;

    QList<int> distanceTo;

    graphInfo *info;



};

#endif // TRIPPLANNER_H
