#pragma once
#include <QListWidget>
#include "src/widgets/menulistitem.hpp"

using IDQtys = std::map<IDs,Qty>;

/**
 * @brief MenuList class
 *
 * Provides a simple way to list menu items.
 * This list isn't tied to a specific restaurant, any menu item can be added.
 *
 * To use:
 * @code{.cpp}
 * MenuList* list = new RestaurantList(widget);
 * list->addAllItems(restaurant);
 * @endcode
 *
 * This will create a menu list within its parent widget.
 * Then it will add all the menu items of the restaurant to the list.
 */
class MenuList : public QListWidget
{
    Q_OBJECT

public:
    /* Constructor */
    MenuList(QWidget* parent);

    /* Getters */
    IDQtys getIDQty() const;
    IDs getSelected() const;

    /* Setters */
    void setQty(IDs, int qty) const;

    /* List modifiers */
    void addItem(RestaurantID, const MenuItem&);
    void addAllItems(const Restaurant&);
    void removeItem(IDs);
    void allowDeleted(bool);

    /* Quantity */
    void showQty(bool);
    void resetQty();

signals:
    void currentMenuItemChanged(IDs) const;
    void showQtyEmitter(bool) const;
    void resetQtyEmitter() const;

private slots:
    void rowToIDsConverter(int row) const;
    void quantityChangedHandler(IDs, Qty);

private:
    IDQtys m_IDQtys;
    bool m_showQty;
    bool m_allowDeleted;
};
