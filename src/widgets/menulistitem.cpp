#include "menulistitem.hpp"
#include "ui_menulistitem.h"

/* Static variables */
const QSize MenuListItem::itemSizeHint(200, 80);

/* Constructor */
MenuListItem::MenuListItem(QWidget* parent, RestaurantID restID, MenuItem menuItem)
    : QWidget(parent), m_ids(restID, menuItem.GetNumber()), m_ui(new Ui::MenuListItem)
{
    m_ui->setupUi(this);

    setStyleSheet("QWidget { color: white; }"
                  "QSpinBox { color: black; }");

    QFont font("Font Awesome 5 Free");

    /* Icon */
    font.setPixelSize(30);
    m_ui->icon->setFont(font);
    m_ui->icon->setText("\uf805");

    /* Name */
    m_ui->name->setWordWrap(true);
    font.setPixelSize(14);
    m_ui->name->setFont(font);
    m_ui->name->setText(QString::fromStdString(menuItem.GetName()));

    /* Price */
    font.setPixelSize(12);
    m_ui->price->setFont(font);
    m_ui->price->setText("\uf155 " + QString::number(menuItem.GetPrice(), 'f', 2));

    /* Quantity */
    font.setPixelSize(12);
    m_ui->quantity->setFont(font);
    m_ui->quantity->setText("Qty");

    //Defaults the quantity widgets to hide
    showQty(false);

    /*
     * Converts the value change signal of the spin box
     * into a signal that emits an ID and quantity
     *
     * Note:
     * The old-style connect is being used because QSpinBox::valueChanged()
     * is overloaded with an int and QString parameter
     */
    connect(m_ui->spinBox_qty, SIGNAL(valueChanged(int)), this, SLOT(valueToIDAndValueConverter(int)));
}

/* Destructor */
MenuListItem::~MenuListItem()
{
    delete m_ui;
}

/* Getters */
Qty MenuListItem::getQty() const
{
    return m_ui->spinBox_qty->value();
}

IDs MenuListItem::getIDs() const
{
    return m_ids;
}

QSize MenuListItem::getItemSizeHint()
{
    return itemSizeHint;
}

/* Setters */
void MenuListItem::setQty(int v)
{
    m_ui->spinBox_qty->setValue(v);
}

/* Public slots */
void MenuListItem::showQty(bool v)
{
    if(v)
    {
        m_ui->quantity->show();
        m_ui->spinBox_qty->show();
    }
    else
    {
        m_ui->quantity->hide();
        m_ui->spinBox_qty->hide();
    }
}

void MenuListItem::resetQty()
{
    m_ui->spinBox_qty->setValue(0);
}

/* Private slots */
void MenuListItem::valueToIDAndValueConverter(int qty) const
{
    emit quantityChanged(m_ids, qty);
}
