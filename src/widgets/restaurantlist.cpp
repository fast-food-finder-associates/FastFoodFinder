#include "restaurantlist.hpp"

/* Static variables */
const QSize RestaurantList::itemSizeHint(190, 70);

/* Constructor */
RestaurantList::RestaurantList(QWidget* parent)
    : QListWidget(parent)
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

/* List modifiers */
void RestaurantList::addItem(ID id)
{
    QFont font("Font Awesome 5 Free", 12);
    QString content = "\uf2e7 " + QString::number(id) + "\n\uf3c5 " + QString::number(id); //TODO get name and distance from ID

    QListWidgetItem* listItem = new QListWidgetItem(content, this);
    listItem->setSizeHint(itemSizeHint);
    listItem->setFont(font);

    //Store the ID into the item to reference a restaurant later on
    listItem->setData(Qt::ItemDataRole::UserRole, id);
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

    if(item != nullptr)
        emit currentRestaurantChanged(item->data(Qt::ItemDataRole::UserRole).toInt());
}
