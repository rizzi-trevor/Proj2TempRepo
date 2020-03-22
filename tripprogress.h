#ifndef TRIPPROGRESS_H
#define TRIPPROGRESS_H

#include <QMainWindow>
#include "dbmanager.h"

namespace Ui {
class tripprogress;
}

class tripprogress : public QMainWindow
{
    Q_OBJECT

public:
    explicit tripprogress(QWidget *parent = nullptr);
    ~tripprogress();

    QString tripID;
    QString currentCol;


    void displaySouv();
    void nextTrip();
    void prevTrip();
    void updateCart();

  public slots:
    void onLoadClick();
    void onNextClick();
    void onPrevClick();

private:
    Ui::tripprogress *ui;

    DbManager myDb = DbManager(PROJECT_PATH + "/college.db");

    QStringList trip;

    int counter;
    int max;
};

#endif // TRIPPROGRESS_H
