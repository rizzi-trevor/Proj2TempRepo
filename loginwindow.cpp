#include "loginwindow.h"
#include "ui_loginwindow.h"
#include "dbmanager.h"



LoginWindow::LoginWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::LoginWindow)
{
    ui->setupUi(this);

    //Running instances just to test the database creation
    // Makes necessary tables from input file

    myDb.InitCollegeList("C:/Users/Trevor Rizzi/Desktop/College-Touring/College Campus Distances and Souvenirs.xlsx");

    myDb.initSouvenirList("C:/Users/Trevor Rizzi/Desktop/College-Touring/College Campus Distances and Souvenirs.xlsx");

    myDb.initDistanceList("C:/Users/Trevor Rizzi/Desktop/College-Touring/College Campus Distances and Souvenirs.xlsx");



}

LoginWindow::~LoginWindow()
{
    delete ui;
}


void LoginWindow::onPlanClick()
{
    this->hide();
    //opens the user window = user window not yet implemented
    //myUser = new userWindow(this);
    //myUser->show();
}

void LoginWindow::onLoginClick()
{
    QString passWord;
    QString userName;

    passWord = this->ui->Username->text();
    userName = this->ui->Password->text();
    if(userName == "N" && passWord == "N")
    {


        //opens the user window = user window not yet implemented

        this->hide();
        //myUser = new userWindow(this);
        //myUser->show();
    }
    else
    {
        this->ui->invalidLabel->setText("Invalid Credentials!");
    }

}

void LoginWindow::onCreateClick()
{
    QString passWord;
    QString userName;

    userName = this->ui->Username->text();
    passWord = this->ui->Password->text();


    if(userName != "" && passWord!= "")
    {
        myDb.addUser(userName, passWord);

        //now open the user window
        this->hide();
        //myUser = new userWindow(this);
        //myUser->show();
    }


}

void LoginWindow::onClearClick()
{
    this->ui->Username->setText("");
    this->ui->Password->setText("");
    this->ui->invalidLabel->setText("");


}

