#ifndef TRIPSUMMARY_H
#define TRIPSUMMARY_H

#include <QDialog>
#include "dbmanager.h"

namespace Ui {
class tripSummary;
}

class tripSummary : public QDialog
{
    Q_OBJECT

public:
    explicit tripSummary(QWidget *parent = nullptr);
    explicit tripSummary(const QString& id, QWidget *parent = nullptr);

    ~tripSummary();



private slots:
    void on_school_comboBox_currentIndexChanged(const QString &arg1);

    void updateTripSchoolList();

private:
    Ui::tripSummary *ui;
    DbManager myDb = DbManager(PROJECT_PATH + "/college.db");

    QString tripID;
};

#endif // TRIPSUMMARY_H
