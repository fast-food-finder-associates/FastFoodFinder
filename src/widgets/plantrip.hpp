#ifndef PLANTRIP_HPP
#define PLANTRIP_HPP

#include <map>
#include <QTimer>
#include <QWidget>
#include <QDateTime>
#include <QMessageBox>
#include "src/widgets/navbar.hpp"
#include "src/widgets/menulist.hpp"
#include "src/widgets/receiptlist.hpp"
#include "src/widgets/menulistitem.hpp"
#include "src/widgets/restaurantlist.hpp"
#include "src/datastore/UserDataStore.hpp"
#include "src/datastore/TripDataStore.hpp"
#include "src/datastore/RestaurantDataStore.hpp"


namespace Ui {
class PlanTrip;
}

class PlanTrip : public QWidget
{
    Q_OBJECT

    /* Enum class for each plan type */
    enum PlanType { Saddleback, ChosenAndN, FirstRestaurant, None};

public:

    /* Constructor */
    PlanTrip(QWidget *parent = nullptr, RestaurantDataStore *m_store = nullptr, NavBar * m_navbar = nullptr);

    /* Destructor */
    ~PlanTrip();

    /* setters */
    void changeHeaderOptions(PlanType);
    void setCurrentRest(const int);
    void setPlanType(const PlanType);
    void resetPlanTripView();
    void activeTrip();

    /* getters */
    QMessageBox::StandardButton promptToContinue();
    PlanType getPlanType() const;
    int getCurrentRest() const;

public slots:


private slots:
    void on_startPlanning_clicked();
    void on_TripButton_clicked();
    void on_addToCart_clicked();
    void on_checkout_clicked();
    void on_next_clicked();
    void on_ContinueToNext_clicked();
    void on_removeItem_clicked();

private:
    Ui::PlanTrip *m_ui;
    MenuList* m_tripFoodCart;
    MenuList* m_tripMenuList;
    RestaurantList* m_planTripListDrag;
    RestaurantList* m_planTripListDrop;
    std::vector<int> m_planTripList;
    RestaurantDataStore* m_store;
    int m_currentRest;
    PlanType m_planType;
    NavBar *m_navbar;
    list<int> m_sorted;
    vector<IDQtys> m_recieptVector;
    ReceiptList *m_receipt;
    TripDataStore *m_tripStore;
    int m_tripId;
};

#endif // PLANTRIP_HPP
