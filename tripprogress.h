#ifndef TRIPPROGRESS_H
#define TRIPPROGRESS_H

#include <QMainWindow>
#include "dbmanager.h"
#include "confirmpage.h"
#include "tripsummary.h"

/**
 * @file
 */


/**
 * \class tripprogress
 *
 * \brief class for displaying and calculating student trip progress, destinations, and student shopping cart for souverniers
 *
 * tripprogress displays an overview of what the user has planned for his trip
 * this updates all data from souvenier, collegename, price, quantity, etc for the plan tripped, as well as the student cart, the student next, and previous destinations
 *
 */

namespace Ui {
class tripprogress;
}

class tripprogress : public QDialog
{
    Q_OBJECT

public:
    /**
    * @brief default explicit Constructor
    *
    * Constructor sets up ui for tripprogress
    * and initializes counter to default
    * @param *parent - for QDialog
    */
    explicit tripprogress(QWidget *parent = nullptr);

    tripprogress(QWidget *parent, QString I_D);

    /**
    * @brief Destructor
    *
    * Close the tripprogress UI
    */
    ~tripprogress();

    /**
    * @brief field member for storing tripID
    *
    */
    QString tripID;

    /**
    * @brief field member for storing currentCol(db)
    */
    QString currentCol;

    /**
    * @brief field member for storing college souvenirName
    */
    QString souvenirName;

    /**
    * @brief field member for storing college souvenirPrice
    */
    double souvenirPrice;

    /**
    * @brief field member for storing sql table row
    */
    int row;

    /**
    * @brief updates sql query to update requested college souverniers and displays Ui table with updated model
    * @return nothing - void
    */
    void displaySouv();

    /**
    * @brief calculates and displays next destination for student planned trip
    * @return nothing - void
    */
    void nextTrip();

    /**
    * @brief calculates and displays previous destination for student planned trip
    * @return nothing - void
    */
    void prevTrip();

    /**
     * @brief Retreives teh distance to the next stadium from the database for display
     */
    void getDistance();

    /**
    * @brief calculates and displays updated student cart for souveniers, total and quantity requested by the student at each school destination
    * @return nothing - void
    */
    void updateCart();

    /**
    * @brief calculates and displays updated student price total for shopping souverniers from cart
    * @return nothing - void
    */
    void updateTotal();

  public slots:
    /**
    * @brief initializes tripProgress on execution , binds tripID, updates size, and calculates nextTrip
    * @return nothing - void
    */
    void onLoadClick();

    /**
    * @brief executes nextTrip();
    * @return nothing - void
    */
    void onNextClick();

    /**
    * @brief executes prevTrip();
    * @return nothing - void
    */
    void onPrevClick();

private slots:

    /**
     * @brief Gets the data of the chosen cell in the table
     * @param index - Cell click in the table
     */
    void on_souvTable_clicked(const QModelIndex &index);

    /**
    * @brief updates database, cart, and total;
    * @return nothing - void
    */
    void on_addCart_clicked();

    /**
     * @brief Checkout the cart to make a purchase
     */
    void on_pushButton_4_released();

    /**
     * @brief Removes an item from the cart
     */
    void on_removeCart_clicked();

private:
    /**
    * @brief points to tripprogress UI
    */
    Ui::tripprogress *ui;

    /**
     * @brief assigns DB to predefined PROJECT_PATH constant
     */
    DbManager myDb = DbManager(PROJECT_PATH + "/college.db");

    /**
    * @brief stores list of each trip/destination data
    */
    QStringList trip;

    QString teamName;

    int counter;
    int max;
};

#endif // TRIPPROGRESS_H
