#pragma once
#include "src/widgets/restaurantitem.hpp"
#include <vector>
#include <QListWidget>

using IDList = std::vector<ID>;

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
    void addItems(const IDList&);
    void removeItem(ID);
    void removeItems(const IDList&);
    void clearItems();

signals:
    void currentRestaurantChanged(ID) const;

private slots:
    void rowToIDConverter(int row) const;
};
