#pragma once
#include <QListWidget>
#include <vector>
#include <utility>

using Restaurant = std::pair<QString, double>;
using Restaurants = std::vector<Restaurant>;

class RestaurantList : public QWidget
{
    Q_OBJECT

public:
    /* Constructor */
    RestaurantList(QWidget* parent, QSize size);

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
    const QSize m_itemSize;
    QListWidget* m_listWidget;
};
