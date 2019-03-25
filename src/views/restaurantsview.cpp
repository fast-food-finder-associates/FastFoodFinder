#include "restaurantsview.hpp"
#include "ui_restaurantsview.h"

RestaurantsView::RestaurantsView(QWidget* parent, RestaurantDataStore* store)
    : QWidget(parent), m_ui(new Ui::RestaurantsView), m_store(store)
{
    m_ui->setupUi(this);

    /* Restaurant list */
    m_restList = new RestaurantList(m_ui->widget_restList);
    m_restList->addItems(m_store->list.begin(), m_store->list.end());

    /* Menu list */
    m_menuList = new MenuList(m_ui->widget_menuList);
    m_menuList->setWrapping(true);
    m_menuList->setFlow(QListView::LeftToRight);

    //On current restaurant change, display its menu items
    connect(m_restList, &RestaurantList::currentRestaurantChanged,
            this, &RestaurantsView::menuListChange);
}

RestaurantsView::~RestaurantsView()
{
    delete m_ui;
    delete m_restList;
    delete m_menuList;
}

void RestaurantsView::resetView()
{
    resetUi();
}

void RestaurantsView::resetUi()
{
    m_ui->label_restName->setText("Restaurant");

    /* Restaurant list */
    m_restList->clear();
    m_restList->addItems(m_store->list.begin(), m_store->list.end());

    /* Menu list */
    m_menuList->clear();
}

void RestaurantsView::menuListChange(RestaurantID id)
{
    if(id == -1)
        return;

    Restaurant restaurant = m_store->FindbyNumber(id);
    m_ui->label_restName->setText(QString::fromStdString(restaurant.GetName()));
    m_menuList->addAllItems(restaurant);
}
