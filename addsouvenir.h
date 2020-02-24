#ifndef ADDSOUVENIR_H
#define ADDSOUVENIR_H

#include <QDialog>

namespace Ui {
class addSouvenir;
}

class addSouvenir : public QDialog
{
    Q_OBJECT

public:
    explicit addSouvenir(QWidget *parent = nullptr);
    ~addSouvenir();

private:
    Ui::addSouvenir *ui;
};

#endif // ADDSOUVENIR_H
