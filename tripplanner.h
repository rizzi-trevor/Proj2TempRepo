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

    /**
     * @brief Updates combo box in MLB information
     */
    void updateCombo();

    /**
     * @brief Updates the table in the Distances tab
     */
    void updateDistTable();

    /**
     * @brief Updates the table in the MLB information tab
     */
    void updateMLBTable();

    /**
     * @brief Creates the checkbox list of stadiums
     */
    void selectedCollegeList();

    /**
     * @brief Checks if a stadium name exists
     */
    bool collegeDoesExist(QString colName);

    /**
     * @brief Checks if the given trip ID already exists
     */
    bool planDoesExist(QString colName);

    /**
     * @brief Displays the trip order of the stadiums
     */
    void showTrip(QString ID);

    /**
     * @brief Updates teh combo box for available stadiums
     */
    void updateComboTwo();

    /**
     * @brief Trip planning algorithm using dijkstra
     */
    void algorithm();


public slots:
    /**
     * @brief Displays stadiums by ballpark topology
     * in MLB information tab
     */
    void onTypologyClick();

    /**
     * @brief Displays stadiums in the American League
     * in MLB information tab
     */
    void onAmericanClick();

    /**
     * @brief Displays all stadiums
     * in MLB information tab
     */
    void onShowClick();

    /**
     * @brief Displays stadiums in the National League
     * in MLB information tab
     */
    void onNationalClick();

    /**
     * @brief Displays teams and stadiums sorted by stadium name
     * in MLB information tab
     */
    void onStadiumsClick();

    /**
     * @brief Displays teams and stadiums sorted by team name
     * in MLB information tab
     */
    void onTeamClick();

    /**
     * @brief Displays team that matches searched team name
     * in MLB information tab
     */
    void onSearchClick();

    /**
     * @brief Displays stadiums by roof type
     * in MLB information tab
     */
    void onRoofClick();

    /**
     * @brief Displays stadiums by creation year
     * in MLB information tab
     */
    void onDateClick();

    /**
     * @brief Displays stadiums by number of seats
     * in MLB information tab
     */
    void onSeatingClick();


    /**
     * @brief Displays stadiums by largest distance field
     * in MLB information tab
     */
    void onGreatClick();

    /**
     * @brief Displays stadiums by shortest distance field
     * in MLB information tab
     */
    void onLeastClick();


    /**
     * @brief Initalizes checkbox list
     */
    void initializeList();

    /**
     * @brief Plans trip path
     * requires a valid tripID entered
     * uses the algorithm function to determine path through stadiums
     * requires a valid starting stadium
     */
    void onPlanClick();

    /**
     * @brief Opens a dialogue displaying the BFS, DFS, and MST distances of the stadium graph
     */
    void onGraphInfoClick();


    /**
     * @brief Initiates the start of the trip
     * requires valid trip plan and ID
     */
    void onStartTrip();



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

    vector<QString> path;

    vector<QString> remainingChoices;

    vector<int> distNext;



};

#endif // TRIPPLANNER_H
