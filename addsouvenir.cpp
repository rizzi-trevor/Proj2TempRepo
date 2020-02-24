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
