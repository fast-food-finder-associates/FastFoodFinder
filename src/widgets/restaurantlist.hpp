#pragma once
#include "src/widgets/restaurantitem.hpp"
#include <vector>
#include <QListWidget>

using ID = int;
using IDList = const std::vector<ID>&;

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
    void addItem(ID);
    void addItems(IDList);
    void removeItem(ID);
    void removeItems(IDList);
    void clearItems();

signals:
    void currentRestaurantChanged(ID);

private slots:
    void rowsInsertedHandler(const QModelIndex&, int, int);
};
