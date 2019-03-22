#ifndef PLANTRIP_HPP
#define PLANTRIP_HPP

#include <QWidget>
#include "src/widgets/restaurantlist.hpp"
#include "src/widgets/menulist.hpp"
#include "src/datastore/RestaurantDataStore.hpp"
#include "src/widgets/navbar.hpp"
#include <queue>

namespace Ui {
class PlanTrip;
}

class PlanTrip : public QWidget
{
    Q_OBJECT

    /* Enum class for each view state */
    enum StartFrom { Saddleback, ChosenAndN, FirstRestaurant, None};

//TODO: make enum for page states

// Make enum for choice states
public:
     PlanTrip(QWidget *parent = nullptr, RestaurantDataStore *m_store = nullptr, NavBar * m_navbar = nullptr);
    ~PlanTrip();

public slots:
     void changeHeaderOptions(StartFrom);
        void on_TripButton_clicked();
        void resetPlanTripView();
        void activeTrip();
        Restaurant& getRestaurantPointer(int id);
        void on_next_clicked();

private slots:
    void on_pushButton_clicked();

private:
    Ui::PlanTrip *m_ui;
    std::queue<int> m_planTripVector;
    MenuList* m_tripMenuList;
    MenuList* m_tripFoodCart;
    RestaurantList* m_planTripListDrag;
    RestaurantList* m_planTripListDrop;
    RestaurantDataStore* m_store;
    NavBar *m_navbar;
    StartFrom m_state;
};

#endif // PLANTRIP_HPP
