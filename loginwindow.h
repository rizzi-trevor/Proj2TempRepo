#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QMainWindow>
#include "dbmanager.h"

QT_BEGIN_NAMESPACE
namespace Ui { class LoginWindow; }
QT_END_NAMESPACE

class LoginWindow : public QMainWindow
{
    Q_OBJECT

public slots:
    void onPlanClick();
    void onLoginClick();
    void onCreateClick();
    void onClearClick();


public:
    LoginWindow(QWidget *parent = nullptr);
    ~LoginWindow();

private:
    Ui::LoginWindow *ui;

    DbManager myDb = DbManager("C:/Users/Trevor Rizzi/Documents/College-Touring/college.db");

};
#endif // LOGINWINDOW_H
