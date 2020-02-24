#ifndef TRIPPLANNER_H
#define TRIPPLANNER_H

#include <QDialog>
#include "dbmanager.h"
#include <qcheckbox.h>
namespace Ui {
class tripPlanner;
}

class tripPlanner : public QDialog
{
    Q_OBJECT

public:
    explicit tripPlanner(QWidget *parent = nullptr);
    ~tripPlanner();


    void initializeList();


private slots:
    void ChecboxChanged();

private:
    Ui::tripPlanner *ui;

    DbManager myDb = DbManager("C:/Users/Nick/source/repos/CS1D-Project1-College-Touring/college.db");
    QVector<QCheckBox*> checkBoxVector;
};

#endif // TRIPPLANNER_H
