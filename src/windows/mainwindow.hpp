#pragma once
#include <QMainWindow>
#include <queue>
#include "src/widgets/navbar.hpp"
#include "src/widgets/restaurantlist.hpp"
#include "src/widgets/menulist.hpp"
#include "src/datastore/RestaurantDataStore.hpp"

namespace Ui
{
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    /* Constructors */
    MainWindow();

    /* Destructor */
    ~MainWindow() override;

    /* Enum class for each view state */
    enum class ViewStates { MAIN, ADMIN };

signals:
    void logout() const;

private slots:
    void changeView(int);
    void changeNavState(ViewStates);
    void menuListChange(int);
    void on_TripButton_clicked();
    void resetPlanTripView();
    void activeTrip();
    Restaurant& getRestaurantPointer(int id);
    void on_next_clicked();

private:
    Ui::MainWindow* m_ui;
    NavBar* m_navbar;
    RestaurantList* m_restaurantList;
    RestaurantList* m_planTripListDrag;
    RestaurantList* m_planTripListDrop;
    MenuList* m_menuList;
    RestaurantDataStore m_store;
    std::queue<int> m_planTripVector;
    MenuList* m_tripMenuList;
    MenuList* m_tripFoodCart;
};
