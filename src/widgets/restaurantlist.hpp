#pragma once
#include "src/widgets/restaurantitem.hpp"
#include <vector>
#include <QListWidget>

using Restaurants = std::vector<Restaurant>;

class RestaurantList : public QWidget
{
    Q_OBJECT

public:
    /* Constructor */
    RestaurantList(QWidget* parent);

    /* Destructor */
    ~RestaurantList() override;

    /* Drag and drop */
    void setDragDropMode(QAbstractItemView::DragDropMode);

    /* List modifiers */
    //TODO these should be restaurant IDs later
    void addItem(const Restaurant&);
    void addItems(const Restaurants&);
    void removeItem(const Restaurant&);
    void removeItems(const Restaurants&);
    void clearItems();

signals: //TODO without the backend, we don't have restaurant IDs
    void currentRestaurantChanged(int restaurantID);

private:
    QListWidget* m_listWidget;
};
