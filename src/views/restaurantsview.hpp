#pragma once
#include <QWidget>
#include "src/widgets/menulist.hpp"
#include "src/widgets/restaurantlist.hpp"
#include "src/datastore/RestaurantDataStore.hpp"

namespace Ui
{
class RestaurantsView;
}

class RestaurantsView : public QWidget
{
    Q_OBJECT

public:
    RestaurantsView(QWidget* parent, RestaurantDataStore*);
    ~RestaurantsView();

public slots:
    void resetView();
    void resetUi();

private slots:
    void fillMenuList(RestaurantID);

private:
    Ui::RestaurantsView* m_ui;
    RestaurantDataStore* m_store;
    RestaurantList* m_restList;
    MenuList* m_menuList;
};
