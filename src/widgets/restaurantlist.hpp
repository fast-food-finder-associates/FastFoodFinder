#pragma once
#include <QListWidget>
#include "src/datastore/Restaurant.hpp"

using RestaurantID = int;

/**
 * @class RestaurantList class
 *
 * Provides a simple way to list restaurant objects.
 *
 * To use:
 * @code{.cpp}
 * RestaurantList* list = new RestaurantList(widget);
 * list->addItems(vector.begin(), vector.end());
 * @endcode
 *
 * This will create a restaurant list within its parent widget.
 * Then it will traverse through the iterators listing each restaurant.
 */
class RestaurantList : public QListWidget
{
    Q_OBJECT

public:

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
    void showHidden(bool);

signals:
    void currentRestaurantChanged(RestaurantID) const;

private slots:
    void rowToIDConverter(int row) const;

private:
    static const QSize itemSizeHint;
    bool m_showHidden;
};

/**
 * @brief Get all restaurant IDs
 *
 * Given a container supporting push_back(), all restaurant IDs are put into the container.
 * To get the restaurant ID, we get the QVariant of each QListWidgetItem
 *
 * @param container The container supporting push_back() that will hold all the restaurant IDs
 */
template<typename Container>
void RestaurantList::getRestaurantIDs(Container& container) const
{

    for(int i = 0; i < this->count(); i++)
    {
        QListWidgetItem* item = this->item(i);
        QVariant data = item->data(Qt::ItemDataRole::UserRole);

        container.push_back(data.toInt());
    }
}

/**
 * @brief Add multiple restaurants to the list
 *
 * Appends multiple restaurants to the list by iterating through the given iterators.
 * For each restaurant, RestaurantList::addItem() is called.
 *
 * @param begin The beginning iterator
 * @param end The end iterator
 */
template<typename Iterator>
void RestaurantList::addItems(Iterator begin, Iterator end)
{
    for(Iterator it = begin; it != end; ++it)
        addItem(*it);
}

/**
 * @brief Remove multiple restaurants from the list
 *
 * Removes multiple restaurants from the list by iterating through the given iterators.
 * For each restaurant, RestaurantList::removeItem() is called.
 *
 * @param begin The beginning iterator
 * @param end The end iterator
 */
template<typename Iterator>
void RestaurantList::removeItems(Iterator begin, Iterator end)
{
    for(Iterator it = begin; it != end; ++it)
        removeItem(*it);
}
