#include "addsouvenir.h"
#include "ui_addsouvenir.h"

addSouvenir::addSouvenir(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addSouvenir)
{
    ui->setupUi(this);
}

addSouvenir::~addSouvenir()
{
    delete ui;
}

void addSouvenir::on_pushButton_2_released()
{
    hide();
}

void addSouvenir::on_pushButton_released()
{
    confirmpage confirm;
    bool check = false;

    confirm.setModal(true);
    confirm.exec();
    check = confirm.getData();

    bool success = false;

    if(ui->collegeEdit->text() == "")
    {
        ui->collegeEdit->setPlaceholderText("college name empty!");
        success = true;
    }

    if(ui->souEdit->text() == "")
    {
        ui->souEdit->setPlaceholderText("souvinir name empty!");
        success = true;
    }

    if(myDb.souExists(ui->souEdit->text()))
    {
        ui->souEdit->setText("");
        ui->souEdit->setPlaceholderText("souvinir name exists!");
        success = true;
    }

    if(!success && check)
    {
        myDb.addSou(ui->collegeEdit->text(),ui->souEdit->text(),ui->costBox->value());
        hide();
    }
}
