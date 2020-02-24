#ifndef TRIPPLANNER_H
#define TRIPPLANNER_H

#include <QDialog>

namespace Ui {
class tripPlanner;
}

class tripPlanner : public QDialog
{
    Q_OBJECT

public:
    explicit tripPlanner(QWidget *parent = nullptr);
    ~tripPlanner();

private:
    Ui::tripPlanner *ui;
};

#endif // TRIPPLANNER_H
