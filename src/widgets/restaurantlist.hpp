#pragma once
#include <QListWidget>
#include <vector>
#include <QString>

using Restaurant = std::pair<QString, double>;
using Restaurants = std::vector<Restaurant>;

class RestaurantList : public QListWidget
{
    Q_OBJECT

public:
    /* Constructor */
    RestaurantList(QWidget* parent, const Restaurants&);

    /* Setters */
    void setWidth(int);
    void setHeight(int);
    void setSize(QSize);

    void addItem(const Restaurant&);
    void addItems(const Restaurants&);

signals:
    void currentRestaurantChanged(int restaurantID);
};
