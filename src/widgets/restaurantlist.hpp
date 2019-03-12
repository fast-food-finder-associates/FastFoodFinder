#pragma once
#include "src/widgets/restaurantitem.hpp"
#include <vector>
#include <QListWidget>

using Restaurants = std::vector<Restaurant>;

class RestaurantList : public QListWidget
{
    Q_OBJECT

public:
    /* Constructor */
    RestaurantList(QWidget* parent);

    /* Drag and drop */
    void setDragDropMode(QAbstractItemView::DragDropMode);
    void setDropActionMode(Qt::DropAction);

    /* List modifiers */
    //TODO these should be restaurant IDs later
    void addItem(const Restaurant&);
    void addItems(const Restaurants&);
    void removeItem(const Restaurant&);
    void removeItems(const Restaurants&);
    void clearItems();

signals: //TODO without the backend, we don't have restaurant IDs
    void currentRestaurantChanged(int restaurantID);

private slots:
    void rowsInsertedHandler(const QModelIndex&, int, int);
};
