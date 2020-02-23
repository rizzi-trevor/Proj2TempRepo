#ifndef ADMINWINDOW_H
#define ADMINWINDOW_H

#include <QMainWindow>
#include "dbmanager.h"

namespace Ui {
class AdminWindow;
}

class AdminWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit AdminWindow(QWidget *parent = nullptr);
    ~AdminWindow();

private slots:
    void onInitialise();
    void clearCollegeData();
private:

    Ui::AdminWindow *ui;


    DbManager myDb = DbManager("C:/Users/Trevor Rizzi/Documents/College-Touring/college.db");

};

#endif // ADMINWINDOW_H
