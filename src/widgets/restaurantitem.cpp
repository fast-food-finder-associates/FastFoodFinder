#include "restaurantitem.hpp"
#include "ui_restaurantitem.h"

/* Static variables */
const QSize RestaurantItem::itemSizeHint(190, 70);

/* Constructor */
RestaurantItem::RestaurantItem(QWidget* parent, const Restaurant& restaurant)
    : QWidget(parent), m_ui(new Ui::RestaurantItem)
{
    m_ui->setupUi(this);

    setStyleSheet("QLabel { color: white; }");
    QFont font("Font Awesome 5 Free");

    /* Name */
    font.setPixelSize(16);
    m_ui->label_name->setWordWrap(true);
    m_ui->label_name->setFont(font);
    m_ui->label_name->setText("\uf2e7 " + restaurant.first);

    /* Distance */
    font.setPixelSize(11);
    m_ui->label_distance->setFont(font);
    m_ui->label_distance->setText("\uf3c5 " + QString::number(restaurant.second) + " mi");
}

/* Destructor */
RestaurantItem::~RestaurantItem()
{
    delete m_ui;
}

/* Getters */
QSize RestaurantItem::getSizeHint()
{
    return itemSizeHint;
}
