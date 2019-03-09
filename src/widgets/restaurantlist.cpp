#include "restaurantlist.hpp"

/* Constructor */
RestaurantList::RestaurantList(QWidget* parent, const Restaurants& restaurants)
    : QListWidget(parent)
{
    setStyleSheet("QListWidget { background-color: #303030; color: white; }");

    //Initial size
    resize(parent->size());

    addItems(restaurants);

    //Rebroadcasts the QListWidget's signal
    connect(this, SIGNAL(currentRowChanged(int)), this, SIGNAL(currentRestaurantChanged(int)));
}

/* Setters */
void RestaurantList::setWidth(int width)
{
    resize(width, height());
}

void RestaurantList::setHeight(int height)
{
    resize(width(), height);
}

void RestaurantList::setSize(QSize size)
{
    resize(size);
}

void RestaurantList::addItem(const Restaurant& restaurant)
{
    QListWidget::addItem(restaurant.first);
}

void  RestaurantList::addItems(const Restaurants& restaurants)
{
    /* Fill the QListWidget with items */
    for(const Restaurant& restaurant : restaurants)
        QListWidget::addItem(restaurant.first);
}
