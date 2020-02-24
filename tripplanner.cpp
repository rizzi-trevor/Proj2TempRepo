#include "tripplanner.h"
#include "ui_tripplanner.h"

tripPlanner::tripPlanner(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::tripPlanner)
{
    ui->setupUi(this);
}

tripPlanner::~tripPlanner()
{
    delete ui;
}
