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
    connect(this, &QListWidget::currentRowChanged, this, &RestaurantList::currentRestaurantChanged);
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
    QListWidgetItem* item = new QListWidgetItem(restaurant.first, this);
    QFont font("fontAwesome", 16);
    item->setFont(font);

    QListWidget::addItem(item);
}

void  RestaurantList::addItems(const Restaurants& restaurants)
{
    QFont font("fontAwesome", 16);

    /* Fill the QListWidget with items */
    for(const Restaurant& restaurant : restaurants)
    {
        QListWidgetItem* item = new QListWidgetItem(this);
        item->setText(restaurant.first);
        item->setFont(font);
        QListWidget::addItem(item);
    }
}
