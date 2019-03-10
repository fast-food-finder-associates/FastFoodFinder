#include "restaurantlist.hpp"

/* Constructor */
RestaurantList::RestaurantList(QWidget* parent)
    : m_listWidget(new QListWidget(parent)), m_font("fontAwesome", 10)
{
    m_listWidget->setStyleSheet("QListWidget { background-color: #303030; color: white; }");

    //Initial size
    m_listWidget->resize(parent->size());

    //Rebroadcasts the QListWidget's signal
    connect(m_listWidget, &QListWidget::currentRowChanged, this, &RestaurantList::currentRestaurantChanged);
}

RestaurantList::RestaurantList(QWidget* parent, const Restaurants& restaurants)
    : m_listWidget(new QListWidget(parent))
{
    m_listWidget->setStyleSheet("QListWidget { background-color: #303030; color: white; }");

    //Initial size
    m_listWidget->resize(parent->size());

    addItems(restaurants);

    //Rebroadcasts the QListWidget's signal
    connect(m_listWidget, &QListWidget::currentRowChanged, this, &RestaurantList::currentRestaurantChanged);
}

/* Destructor */
RestaurantList::~RestaurantList()
{
    delete m_listWidget;
}

/* Setters */
void RestaurantList::setWidth(int width)
{
    m_listWidget->resize(width, m_listWidget->height());
}

void RestaurantList::setHeight(int height)
{
    m_listWidget->resize(m_listWidget->width(), height);
}

void RestaurantList::setSize(QSize size)
{
    m_listWidget->resize(size);
}

/* List modifiers */
void RestaurantList::addItem(const Restaurant& restaurant)
{
    QListWidgetItem* item = new QListWidgetItem(restaurant.first, m_listWidget);
    item->setFont(m_font);

    m_listWidget->addItem(item);
}

void RestaurantList::addItems(const Restaurants& restaurants)
{
    /* Fill the QListWidget with items */
    for(const Restaurant& restaurant : restaurants)
    {
        QListWidgetItem* item = new QListWidgetItem(m_listWidget);
        item->setText(restaurant.first);
        item->setFont(m_font);
        m_listWidget->addItem(item);
    }
}

void RestaurantList::removeItem(const Restaurant& restaurant)
{
    //TODO finish functionality
}

void RestaurantList::removeItems(const Restaurants& restaurants)
{
    //TODO finish functionality
}
