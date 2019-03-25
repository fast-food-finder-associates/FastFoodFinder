#include "restaurantsview.hpp"
#include "ui_restaurantsview.h"

/**
 * @brief Constructor
 *
 * Instantiates the view with list a restaurant and menu list.
 *
 * @param parent The parent widget that this view will be in
 * @param store The data store that contains all the data
 */
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
            this, &RestaurantsView::fillMenuList);
}

/**
 * @brief Destructor
 *
 * Deletes all dynamically allocated memory.
 */
RestaurantsView::~RestaurantsView()
{
    delete m_ui;
    delete m_restList;
    delete m_menuList;
}

/**
 * @brief Reset view
 *
 * Resets the view so it looks just like it was when it was created.
 */
void RestaurantsView::resetView()
{
    resetUi();
}

/**
 * @brief Reset all ui in the view
 *
 * Reset the restaurant name label.
 * Reload the restaurant list.
 * Clear the menu list.
 */
void RestaurantsView::resetUi()
{
    m_ui->label_restName->setText("Restaurant");

    /* Restaurant list */
    m_restList->clear();
    m_restList->addItems(m_store->list.begin(), m_store->list.end());

    /* Menu list */
    m_menuList->clear();
}

/**
 * @brief Fill menu list
 *
 * If the ID is valid, fill the menu list will items from the restaurant ID.
 *
 * @param id The restaurant ID that will fill the menu list
 */
void RestaurantsView::fillMenuList(RestaurantID id)
{
    if(id == -1)
        return;

    Restaurant restaurant = m_store->FindbyNumber(id);
    m_ui->label_restName->setText(QString::fromStdString(restaurant.GetName()));
    m_menuList->addAllItems(restaurant);
}
