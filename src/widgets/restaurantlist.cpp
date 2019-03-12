#include "restaurantlist.hpp"

/* Constructor */
RestaurantList::RestaurantList(QWidget* parent, QSize size)
    : QWidget(parent), m_itemSize(size)
{
    /* List widget settings */
    m_listWidget = new QListWidget(this);
    m_listWidget->setStyleSheet("QListWidget { background-color: #303030; color: white; }");
    m_listWidget->resize(parent->size());
    m_listWidget->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
    m_listWidget->setFlow(QListView::LeftToRight);
    m_listWidget->setWrapping(true);
    m_listWidget->setUniformItemSizes(true);

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

/* Font */
QFont RestaurantList::getFont() const
{
    //All the items should have the same font
    return m_listWidget->item(0)->font();
}

void RestaurantList::setFont(QFont font)
{
    for(int i = 0; i < m_listWidget->count(); i++)
        m_listWidget->item(i)->setFont(font);
}

/* List modifiers */
void RestaurantList::addItem(const Restaurant& restaurant)
{
    QListWidgetItem* item = new QListWidgetItem("\uf2e7 " + restaurant, m_listWidget);
    item->setSizeHint(m_itemSize);
    item->setFont(QFont("Font Awesome 5 Free", 13));

    m_listWidget->addItem(item);
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
