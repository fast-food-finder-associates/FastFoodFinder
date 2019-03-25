#pragma once
#include <QMainWindow>
#include "src/widgets/navbar.hpp"
#include "src/widgets/restaurantlist.hpp"
#include "src/widgets/menulist.hpp"
#include "src/datastore/RestaurantDataStore.hpp"
#include "src/views/adminview.hpp"
#include "src/views/restaurantsview.hpp"

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
    void resetUi();

private:
    Ui::MainWindow* m_ui;
    NavBar* m_navbar;
    RestaurantsView* m_restView;
    AdminView* m_adminView;
    RestaurantDataStore m_store;
};
