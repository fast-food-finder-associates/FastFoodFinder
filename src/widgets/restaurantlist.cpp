#include "restaurantlist.hpp"

/* Constructor */
RestaurantList::RestaurantList(QWidget* parent)
    : m_listWidget(new QListWidget(parent))
{
    m_listWidget->setStyleSheet("QListWidget { background-color: #303030; color: white; }"
                                "QListWidget::item { border-color: grey; border-width: 2px; border-style: outset; }");

    //Initial size
    m_listWidget->resize(parent->size());
    m_listWidget->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);

    //Rebroadcasts the QListWidget's signal
    connect(m_listWidget, &QListWidget::currentRowChanged, this, &RestaurantList::currentRestaurantChanged);
}

/* Destructor */
RestaurantList::~RestaurantList()
{
    delete m_listWidget;
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
    const QSize itemSize(0, 50);

    QListWidgetItem* item = new QListWidgetItem(restaurant, m_listWidget);
    item->setSizeHint(itemSize);
    item->setFont(QFont("fontAwesome", 13));

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
