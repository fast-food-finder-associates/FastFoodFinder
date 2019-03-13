#include "restaurantlist.hpp"

/* Constructor */
RestaurantList::RestaurantList(QWidget* parent)
    : QListWidget(parent)
{
    /* List widget settings */
    QListWidget::setStyleSheet("QListWidget { background-color: #303030; color: white; }");
    QListWidget::resize(parent->size());
    QListWidget::setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
    QListWidget::setFlow(QListView::LeftToRight);
    QListWidget::setWrapping(true);
    QListWidget::setUniformItemSizes(true);
    QListWidget::setDefaultDropAction(Qt::DropAction::MoveAction);

    //Rebroadcasts the QListWidget's signal
    connect(this, &QListWidget::currentRowChanged, this, &RestaurantList::rowToIDConverter);
}

/* Drag and drop */
void RestaurantList::setDragDropMode(QAbstractItemView::DragDropMode v)
{
    QListWidget::setDragDropMode(v);
}

void RestaurantList::setDropActionMode(Qt::DropAction v)
{
    QListWidget::setDefaultDropAction(v);
}

/* List modifiers */
void RestaurantList::addItem(ID id)
{
    QListWidgetItem* listItem = new QListWidgetItem(this);
    listItem->setData(Qt::ItemDataRole::UserRole, id);
    listItem->setSizeHint(RestaurantItem::getSizeHint());

    RestaurantItem* restWidget = new RestaurantItem(this, id);

    QListWidget::setItemWidget(listItem, restWidget);
}

void RestaurantList::addItems(const IDList& idList)
{
    for(ID id : idList)
        addItem(id);
}

void RestaurantList::removeItem(ID id)
{
    for(int i = 0; i < QListWidget::count(); i++)
    {
        QListWidgetItem* item = QListWidget::item(i);
        QVariant data = item->data(Qt::ItemDataRole::UserRole);

        if(data.toInt() == id)
        {
            QListWidget::removeItemWidget(item);
            QListWidget::model()->removeRow(i);
            return;
        }
    }
}

void RestaurantList::removeItems(const IDList& idList)
{
    for(ID id : idList)
        removeItem(id);
}

void RestaurantList::clearItems()
{
    QListWidget::clear();
}

/* Private slots */
void RestaurantList::rowToIDConverter(int row) const
{
    QListWidgetItem* item = QListWidget::item(row);
    emit currentRestaurantChanged(item->data(Qt::ItemDataRole::UserRole).toInt());
}
