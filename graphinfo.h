#ifndef GRAPHINFO_H
#define GRAPHINFO_H

#include <QDialog>
#include <QListWidget>
#include <QSqlQuery>
#include <QtDebug>
#include <qsqlquerymodel.h>
#include <qsortfilterproxymodel.h>
#include <QSqlQuery>
#include <QMessageBox>
#include "bfs.h"
#include "dfsgraph.h"
#include "graphAdjList.h"
#include "dbmanager.h"

/**
 * @brief implements the BFS using the bfs class
 * @return total distance
 */
int performBFS();

/**
 * @brief implements the DFS using the dfsgraph class
 * @return total distance
 */
int performDFS();

/**
 * @brief implements the MST using the graphAdjList class
 * @return total distance
 */
int performMST();

/**
 * @brief implements the MST using the graphAdjList class
 * @param teamsSelected - the two teams to travel between
 * @return total distance
 */
int performDijkstra(QStringList teamsSelected) ;


/**
 * @brief Converts team names to stadium names
 * @param teamsSelected list of teams
 * @return - QStringList contaning the stadium names
 */
QStringList convertTeamNamesToStadiumNames(QStringList teamsSelected) ;

namespace Ui {
class graphInfo;
}

class graphInfo : public QDialog
{
    Q_OBJECT

public:
    explicit graphInfo(QWidget *parent = nullptr);
    ~graphInfo();


public slots:
    void onCloseClick();

private:
    Ui::graphInfo *ui;

};




#endif // GRAPHINFO_H
