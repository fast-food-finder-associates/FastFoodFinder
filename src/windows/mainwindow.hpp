#pragma once
#include <QMainWindow>
#include "src/widgets/navbar.hpp"
#include "src/widgets/restaurantlist.hpp"
#include "src/widgets/menulist.hpp"
#include "src/datastore/RestaurantDataStore.hpp"
#include "src/views/adminview.hpp"

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

signals:
    void logout() const;

private slots:
    void changeView(int);
    void menuListChange(int);
    void resetUi();

private:
    Ui::MainWindow* m_ui;
    NavBar* m_navbar;
    RestaurantList* m_restaurantList;
    MenuList* m_menuList;
    AdminView* m_adminView;
    RestaurantDataStore m_store;
};
