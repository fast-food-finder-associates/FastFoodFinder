#pragma once
#include <QListWidget>
#include "src/datastore/Restaurant.hpp"

using RestaurantID = int;

class RestaurantList : public QListWidget
{
    Q_OBJECT

public:

    /* Enum class for each view state */
    enum StartFrom { Saddleback, FirstRestaurant, None};

    /* Constructor */
    RestaurantList(QWidget* parent);

    /* Getters */
    RestaurantID getSelected() const;
    template<typename Container>
    void getRestaurantIDs(Container&) const;

    /* List modifiers */
    void addItem(const Restaurant&);
    template<typename Iterator>
    void addItems(Iterator begin, Iterator end);
    void removeItem(const Restaurant&);
    template<typename Iterator>
    void removeItems(Iterator begin, Iterator end);

    // m_tripCoiceStorage modifier
    void addListToTripDB(Iterator begin, Iterator end);

signals:
    void currentRestaurantChanged(RestaurantID) const;

private slots:
    void rowToIDConverter(int row) const;

private:
    static const QSize itemSizeHint;
};

/* Templated getters */
template<typename Container>
void RestaurantList::getRestaurantIDs(Container& container) const
{
//    qDebug() << QString::number(this->count());
    for(int i = 0; i < this->count(); i++)
    {
        QListWidgetItem* item = this->item(i);
        QVariant data = item->data(Qt::ItemDataRole::UserRole);
//        container.push_back(data.toInt());
        container.push(data.toInt());
    }
}

/* Templated list modifiers */
template<typename Iterator>
void RestaurantList::addItems(Iterator begin, Iterator end)
{
    for(Iterator it = begin; it != end; ++it)
        addItem(*it);
}

template<typename Iterator>
void RestaurantList::removeItems(Iterator begin, Iterator end)
{
    for(Iterator it = begin; it != end; ++it)
        removeItem(*it);
}
