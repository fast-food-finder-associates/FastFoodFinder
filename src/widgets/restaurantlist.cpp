#include "restaurantlist.hpp"
#include "restaurantitem.hpp"

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
    connect(this, &QListWidget::currentRowChanged, this, &RestaurantList::currentRestaurantChanged);
    connect(this->model(), &QAbstractItemModel::rowsInserted, this, &RestaurantList::rowsInsertedHandler);
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
void RestaurantList::addItem(const Restaurant& restaurant)
{
    QListWidgetItem* listItem = new QListWidgetItem();
    listItem->setData(Qt::ItemDataRole::UserRole, restaurant.first);
    listItem->setSizeHint(RestaurantItem::getSizeHint());

//    RestaurantItem* restWidget = new RestaurantItem(this, restaurant);

        QListWidget::addItem(listItem);
//    QListWidget::setItemWidget(listItem, restWidget);
}

void RestaurantList::addItems(const Restaurants& restaurants)
{
    /* Fill the QListWidget with items */
    for(const Restaurant& restaurant : restaurants)
        addItem(restaurant);
}

void RestaurantList::removeItem(const Restaurant& restaurant)
{
    //TODO finish functionality
}

void RestaurantList::removeItems(const Restaurants& restaurants)
{
    //TODO finish functionality
}

void RestaurantList::clearItems()
{
    QListWidget::clear();
}

void RestaurantList::rowsInsertedHandler(const QModelIndex&, int start, int end)
{
    for(int i = start; i <= end; i++)
    {
        //Get the QListWidgetItem at the given row in the dropped QListWidget
        QListWidgetItem* item = QListWidget::item(i);

        //True if the item isn't nullptr and if it's item QWidget is empty (so we can store something there)
        if(item != nullptr && QListWidget::itemWidget(item) == nullptr)
        {
            //Get the item's QVariant
            QVariant restData = item->data(Qt::ItemDataRole::UserRole);

            //Create a new restaurant item QWidget using the data from the QVariant
            RestaurantItem* restWidget = new RestaurantItem(this, Restaurant(restData.toString(), 0));

            //Store the restaurant item into the QListWidgetItem
            QListWidget::setItemWidget(item, restWidget);
        }
    }
}
