#pragma once
#include <vector>
#include <QListWidget>
#include "src/datastore/Restaurant.hpp"

using Iterator = std::list<Restaurant>::iterator;

class RestaurantList : public QListWidget
{
    Q_OBJECT

public:
    /* Constructor */
    RestaurantList(QWidget* parent);

    /* Static getters */
    static QSize getItemSizeHint();

    /* List modifiers */
    void addItem(const Restaurant&);
    void addItems(Iterator begin, Iterator end);
    void removeItem(const Restaurant&);
    void removeItems(Iterator begin, Iterator end);
    void clearItems();

signals:
    void currentRestaurantChanged(int ID) const;

private slots:
    void rowToIDConverter(int row) const;

private:
    static const QSize itemSizeHint;
};
