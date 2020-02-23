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

    //myDb.clearDb(); deletes the tables with college info

    if(!myDb.isOpen())
    {
        ui->dbStatus->setText("Failed to open database!");
    }
    else
    {
        ui->dbStatus->setText("Connected...");
    }


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

    userName = this->ui->Username->text();
    passWord = this->ui->Password->text();

    //check for admin login -> open admin window
    //check for reg login ->open user window

    //***************************************

    if(passWord == myDb.getPassword(userName))
    {
        if(myDb.checkAdmin(userName))
        {
            this->hide();
            admin = new AdminWindow(this);
            admin->show();
        }
        else
        {
            this->hide();
            //open the user window here
            //
            //
            //
        }
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


