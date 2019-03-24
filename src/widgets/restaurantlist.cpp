#include "restaurantlist.hpp"

/* Static variables */
const QSize RestaurantList::itemSizeHint(170, 70);

/**
 * @brief Constructor
 *
 * Constructs a retaurant list within the given parent widget.
 * All default settings are set when created.
 *
 * @param parent Widget to display list in
 */
RestaurantList::RestaurantList(QWidget* parent)
    : QListWidget(parent), m_showHidden(false)
{
    /* List widget settings */
    QListWidget::setStyleSheet("QListWidget { background-color: #303030; color: white; }");
    QListWidget::resize(parent->size());
    QListWidget::setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
    QListWidget::setUniformItemSizes(true);

    /* Settings for wrapping */
    QListWidget::setWrapping(false);
    QListWidget::setFlow(QListView::TopToBottom);

    /* Settings for drag and drop */
    QListWidget::setDragDropMode(DragDropMode::NoDragDrop);
    QListWidget::setDefaultDropAction(Qt::DropAction::MoveAction);

    //Rebroadcasts the current row changed into a usable restaurant ID
    connect(this, &QListWidget::currentRowChanged, this, &RestaurantList::rowToIDConverter);
}

/**
 * @brief Get selected restaurant ID
 *
 * Returns the selected item's restaurant ID. If nothing is selected, -1 is returned.
 *
 * @return The restaurant ID that was selected; if nothing is selected, -1 is returned.
 */
RestaurantID RestaurantList::getSelected() const
{
    QListWidgetItem* item = QListWidget::currentItem();

    if(item != nullptr)
        return item->data(Qt::ItemDataRole::UserRole).toInt();
    else
        return -1;
}

/**
 * @brief Add restaurant to list
 *
 * Appends the given restaurant to the list.
 * If the restaurant is hidden, it isn't added to the list unless RestaurantList::showHidden(true) was called.
 * The restaurant ID is attatched to the QListWidgetItem using Qt::ItemDataRole::UserRole.
 *
 * @param rest Restaurant that is being added to the list
 */
void RestaurantList::addItem(const Restaurant& rest)
{
    if(rest.IsDeleted() && !m_showHidden)
        return;

    QFont font("Font Awesome 5 Free", 12);
    QString content = "\uf2e7 " + QString::fromStdString(rest.GetName()) + "\n" +
                      "\uf3c5 " + QString::number(static_cast<double>(rest.GetDistSaddleback()), 'f', 2) + " mi.";

    QListWidgetItem* listItem = new QListWidgetItem(content, this);
    listItem->setSizeHint(itemSizeHint);
    listItem->setFont(font);

    //Store the ID into the item to reference a restaurant later on
    listItem->setData(Qt::ItemDataRole::UserRole, rest.GetNumber());
}

/**
 * @brief Remove restaurant from list
 *
 * Removes a given restaurant from the list.
 * If the restaurant isn't found, nothing happens.
 * To find the correct restaurant, we look at the QVariant of each QListWidgetItem.
 *
 * @param rest Restaurant that will be removed from the list
 */
void RestaurantList::removeItem(const Restaurant& rest)
{
    for(int i = 0; i < QListWidget::count(); i++)
    {
        QListWidgetItem* item = QListWidget::item(i);
        QVariant data = item->data(Qt::ItemDataRole::UserRole);

        if(data.toInt() == rest.GetNumber())
        {
            QListWidget::removeItemWidget(item);
            QListWidget::model()->removeRow(i);
            return;
        }
    }
}

/**
 * @brief Show hidden restaurants
 *
 * Sets whether or not to show hidden restaurants.
 * NOTE: Calling this function after restaurants items will not affect previously added restaurants.
 *
 * @param v Bool value
 */
void RestaurantList::showHidden(bool v)
{
    m_showHidden = v;
}

/**
 * @brief Row to restaurant ID converter
 *
 * Converts a row in the list into a restaurant ID.
 *
 * @param row Row of the item to convert
 */
void RestaurantList::rowToIDConverter(int row) const
{
    QListWidgetItem* item = QListWidget::item(row);

    if(item != nullptr)
        emit currentRestaurantChanged(item->data(Qt::ItemDataRole::UserRole).toInt());
}
