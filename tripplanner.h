#ifndef TRIPPLANNER_H
#define TRIPPLANNER_H

#include <QDialog>
#include <QList>
#include "dbmanager.h"
#include <qcheckbox.h>
#include "tripsummary.h"
#include "tripprogress.h"

/**
 * @file
 */


/**
 * \class tripPlanner
 *
 * \brief class recusively planning (calculating) the most efficient trip, manages data tables, checks if data is valid, and begins inital processes of planning a trip
 *
 * tripPlanner manages the calculations for creating the most efficient trip for the student
 * this updates all data tables for colleges, their names and specific data values, and souveniers, with their respectives data values
 *
 */

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

public slots:
    void onTypologyClick();

    void onAmericanClick();

    void onShowClick();

    void onNationalClick();

    void onStadiumsClick();

    void onTeamClick();

    void onSearchClick();



private slots:
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


};

#endif // TRIPPLANNER_H
