#ifndef ADMINWINDOW_H
#define ADMINWINDOW_H

#include <QMainWindow>
#include "dbmanager.h"
#include <QDialog>
#include "addsouvenir.h"

namespace Ui {
class AdminWindow;
}

class AdminWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit AdminWindow(QWidget *parent = nullptr);
    void updateCollegeTable();
    void updateSouvenirTable();
    ~AdminWindow();

private slots:
    void onInitialise();
    void clearCollegeData();
    void on_addSouvenir_released();

    void on_removeSouvenir_released();
    void onAddColleges();

    void on_souvenirView_clicked(const QModelIndex &index);

    void on_removeSouvenir_2_clicked();

private:
    QString souve;

    Ui::AdminWindow *ui;


    DbManager myDb = DbManager("C:/Users/farna/Documents/CS1D-Project1-College-Touring/college.db");

};

#endif // ADMINWINDOW_H
