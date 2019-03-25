#include "menulist.hpp"

/**
 * @brief Constructor
 *
 * Constructs a menu list within the given parent widget.
 * All default settings are set when created.
 *
 * @param parent The widget to display the list in
 */
MenuList::MenuList(QWidget* parent)
    : QListWidget(parent), m_showQty(false), m_showHidden(false)
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
    connect(this, &QListWidget::currentRowChanged, this, &MenuList::rowToIDsConverter);
}

/**
 * @brief Get IDs and its corresponding spinbox value
 *
 * Returns the IDs of the menu item (including the restaurant ID),
 * and the corresponding quantity that is determined by the spinbox value.
 *
 * @return The IDs and its corresponding spinbox value
 */
IDQtys MenuList::getIDQty() const
{
    return m_IDQtys;
}

/**
 * @brief Get selected IDs
 *
 * Converts the selected item into its IDs.
 *
 * @return The IDs that is selected; if nothing is selected, IDs(-1, -1) is returned.
 */
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

/**
 * @brief Set IDs' quantity
 *
 * Sets the IDs' corresponding quantity to a value.
 * This is done by dynamic casting all the QListWidgetItems within the list and
 * checking if its attatched MenuListItem widget has the right IDs.
 *
 * @param id The IDs corresponding to a menu item
 * @param qty The value of the new quantity
 */
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

/**
 * @brief Add menu item to the list
 *
 * Appends the given menu item to the list.
 * Any connections needed to the new item is done here.
 * If the menu item is hidden, it isn't added to the list unless MenuList::showHidden(true) is called.
 *
 * @param restID The restaurant ID that the menu item belongs to
 * @param menuItem The menu item to add
 */
void MenuList::addItem(RestaurantID restID, const MenuItem& menuItem)
{
    if(menuItem.IsDeleted() && !m_showHidden)
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

/**
 * @brief Add multiple menu items to the list
 *
 * Appends multiple menu items to the list given a restaurant.
 * Calls MenuList::addItem() for each menu item of the restaurant.
 *
 * @param restaurant The restaurant to add all of its items to the list
 */
void MenuList::addAllItems(const Restaurant& restaurant)
{
    QListWidget::clear();

    for(MenuItem menuItem : restaurant.GetMenu())
        addItem(restaurant.GetNumber(), menuItem);
}

/**
 * @brief Remove menu item from the list
 *
 * Removes a menu item from the list given the corresponding restaurant and menu IDs.
 * This is done by dynamic casting all the QListWidgetItems within the list and
 * checking if its attatched MenuListItem widget has the right IDs.
 *
 * @param id The IDs of the restaurant and the menu item to remove
 */
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

/**
 * @brief Allow hidden menu items
 *
 * Sets whether or not hidden menu items will be added or not.
 * NOTE: Calling this function after menu items are added will have no affect on those items.
 *
 * @param v Bool value
 */
void MenuList::showHidden(bool v)
{
    m_showHidden = v;
}

/**
 * @brief Show the quantity spinbox
 *
 * If true, quantity spinboxes will show on each menu item.
 * This is useful if you need to input quantity for each item.
 *
 * @param v Bool value
 */
void MenuList::showQty(bool v)
{
    m_showQty = v;
    emit showQtyEmitter(v);
}

/**
 * @brief Reset quantities
 *
 * Clears out the container holding the IDs-quantity relationship.
 */
void MenuList::resetQty()
{
    m_IDQtys.clear();
    emit resetQtyEmitter();
}

/**
 * @brief Row to IDs converter
 *
 * Converts a row in the list to IDs.
 *
 * @param row The row of the item to convert
 */
void MenuList::rowToIDsConverter(int row) const
{
    //Get the QListWidgetItem at the specified row
    QListWidgetItem* item = QListWidget::item(row);

    //Attempt to cast the linked widget into a MenuListItem
    MenuListItem* menuItem = dynamic_cast<MenuListItem*>(QListWidget::itemWidget(item));

    //If successful, emit a signal
    if(menuItem != nullptr)
        emit currentMenuItemChanged(menuItem->getIDs());
}

/**
 * @brief Quantity change handler
 *
 * When a quantity spinbox has changed value, this function will store that new value.
 *
 * @param id The IDs of the changed menu item
 * @param qty The new quantity value
 */
void MenuList::quantityChangedHandler(IDs id, int qty)
{
    if(qty != 0)
        m_IDQtys[id] = qty; //Store/replace the key with the value
    else
        m_IDQtys.erase(id); //Erase the the key-value pair
}
