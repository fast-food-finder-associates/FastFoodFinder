#include "restaurantlist.hpp"
#include "src/widgets/restaurantitem.hpp"

/* Constructor */
RestaurantList::RestaurantList(QWidget* parent)
    : QWidget(parent)
{
    /* List widget settings */
    m_listWidget = new QListWidget(this);
    m_listWidget->setStyleSheet("QListWidget { background-color: #303030; color: white; }");
    m_listWidget->resize(parent->size());
    m_listWidget->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
    m_listWidget->setFlow(QListView::LeftToRight);
    m_listWidget->setWrapping(true);
    m_listWidget->setUniformItemSizes(true);
    m_listWidget->setDefaultDropAction(Qt::DropAction::CopyAction); //TODO make function for this

    //Rebroadcasts the QListWidget's signal
    connect(m_listWidget, &QListWidget::currentRowChanged, this, &RestaurantList::currentRestaurantChanged);
}

/* Destructor */
RestaurantList::~RestaurantList()
{
    delete m_listWidget;
}

/* Drag and drop */
void RestaurantList::setDragDropMode(QAbstractItemView::DragDropMode v)
{
    m_listWidget->setDragDropMode(v);
}

/* List modifiers */
void RestaurantList::addItem(const Restaurant& restaurant)
{
    QListWidgetItem* listItem = new QListWidgetItem(m_listWidget);
    RestaurantItem* restItem = new RestaurantItem(m_listWidget, restaurant);
    listItem->setSizeHint(RestaurantItem::getSizeHint());
    m_listWidget->setItemWidget(listItem, restItem);
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
    m_listWidget->clear();
}
