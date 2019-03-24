#include "menulist.hpp"

/* Constructor */
MenuList::MenuList(QWidget* parent)
    : QListWidget(parent), m_showQty(false), m_allowDeleted(false)
{
    /* List widget settings */
    QListWidget::setStyleSheet("QListWidget { background-color: #303030; color: white; }");
    QListWidget::resize(parent->size());
    QListWidget::setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
    QListWidget::setUniformItemSizes(true);

    /* Settings for wrapping */
    QListWidget::setWrapping(false);
    QListWidget::setFlow(QListView::TopToBottom);

    //Emits a signal when a menu item is selected with information about the menu item
    connect(this, &QListWidget::currentRowChanged, this, &MenuList::currentMenuItemHandler);
}

/* Getters */
IDQtys MenuList::getIDQty() const
{
    return m_IDQtys;
}

IDs MenuList::getSelected() const
{
    //Get the QListWidgetItem at the specified row
    QListWidgetItem* item = QListWidget::item(QListWidget::currentRow());

    //Attempt to cast the linked widget into a MenuListItem
    MenuListItem* menuItem = dynamic_cast<MenuListItem*>(QListWidget::itemWidget(item));

    //If successful, return the menu item's IDs
    if(menuItem != nullptr)
        return menuItem->getIDs();
    else
        return IDs(-1, -1);
}

/* Setters */
void MenuList::setQty(IDs id, int qty) const
{
    for(int i = 0; i < QListWidget::count(); i++)
    {
        QListWidgetItem* listItem = QListWidget::item(i);
        MenuListItem* widget = dynamic_cast<MenuListItem*>(QListWidget::itemWidget(listItem));

        if(widget != nullptr && id == widget->getIDs())
        {
            widget->setQty(qty);
            return;
        }
    }
}

/* List modifiers */
void MenuList::addItem(RestaurantID restID, const MenuItem& menuItem)
{
    if(menuItem.IsDeleted() && !m_allowDeleted)
        return;

    QListWidgetItem* listItem = new QListWidgetItem(this);
    listItem->setSizeHint(MenuListItem::getItemSizeHint());

    MenuListItem* widget = new MenuListItem(this, restID, menuItem);
    QListWidget::setItemWidget(listItem, widget);

    widget->showQty(m_showQty);

    //Allows all MenuItem's to toggle its quantity widgets through the emitter
    connect(this, &MenuList::showQtyEmitter, widget, &MenuListItem::showQty);

    //Handles the quantity change of a menu item
    connect(widget, &MenuListItem::quantityChanged, this, &MenuList::quantityChangedHandler);

    //Resets each spinbox of each MenuItem when emitted
    connect(this, &MenuList::resetQtyEmitter, widget, &MenuListItem::resetQty);
}

void MenuList::addAllItems(const Restaurant& restaurant)
{
    QListWidget::clear();

    for(MenuItem menuItem : restaurant.GetMenu())
        addItem(restaurant.GetNumber(), menuItem);
}

void MenuList::removeItem(IDs id)
{
    for(int i = 0; i < QListWidget::count(); i++)
    {
        QListWidgetItem* listItem = QListWidget::item(i);
        MenuListItem* widget = dynamic_cast<MenuListItem*>(QListWidget::itemWidget(listItem));

        if(widget != nullptr && id == widget->getIDs())
        {
            QListWidget::removeItemWidget(listItem);
            return;
        }
    }
}

void MenuList::allowDeleted(bool v)
{
    m_allowDeleted = v;
}

/* Quantity */
void MenuList::showQty(bool v)
{
    m_showQty = v;
    emit showQtyEmitter(v);
}

void MenuList::resetQty()
{
    m_IDQtys.clear();
    emit resetQtyEmitter();
}

/* Private slots */
void MenuList::currentMenuItemHandler(int row) const
{
    //Get the QListWidgetItem at the specified row
    QListWidgetItem* item = QListWidget::item(row);

    //Attempt to cast the linked widget into a MenuListItem
    MenuListItem* menuItem = dynamic_cast<MenuListItem*>(QListWidget::itemWidget(item));

    //If successful, emit a signal
    if(menuItem != nullptr)
        emit currentMenuItemChanged(menuItem->getIDs());
}

void MenuList::quantityChangedHandler(IDs id, int qty)
{
    if(qty != 0)
        m_IDQtys[id] = qty; //Store/replace the key with the value
    else
        m_IDQtys.erase(id); //Erase the the key-value pair
}
