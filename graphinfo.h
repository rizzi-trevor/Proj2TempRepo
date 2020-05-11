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


int performMST();
int performDijkstra(QStringList teamsSelected, QString ID) ;
QStringList convertTeamNamesToStadiumNames(QStringList teamsSelected) ;
int performBFS();
int performDFS();

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
