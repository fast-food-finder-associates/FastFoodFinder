#include "navbar.hpp"
#include "navitem.hpp"
#include <QPropertyAnimation>

/* Constructor */
NavBar::NavBar(QWidget* parent, int minWidth, int maxWidth, bool expand)
    : QListWidget(parent), m_minWidth(minWidth), m_maxWidth(maxWidth)
{
    parent->raise();
    setStyleSheet("QListWidget { background-color: #303030; }");

    //Initial size
    if(!expand)
    {
        resize(m_minWidth, parent->height());
    }
    else
    {
        resize(m_maxWidth, parent->height());
    }
    connect(this, &QListWidget::currentRowChanged, this, &NavBar::currentItemChanged);
}

/* Setters */
void NavBar::setHeight(int height)
{
    resize(width(), height);
}

void NavBar::setMinWidth(int width)
{
    m_minWidth = width;
}

void NavBar::setMaxWidth(int width)
{
    m_maxWidth = width;
}

void NavBar::addItem(QString icon, QString label)
{
    const QSize itemSize(70, 80);

    QListWidgetItem* listWidgetItem = new QListWidgetItem(this);
    listWidgetItem->setSizeHint(itemSize);
    QListWidget::addItem(listWidgetItem);

    /* Set the QListWidgetItem to hold a NavItem */
    NavItem* navItem = new NavItem(this, icon, label);
    setItemWidget(listWidgetItem, navItem);

    /* Allows the NavBar and NavItem to expand and shrink simultaneously */
    connect(this, &NavBar::expand, navItem, &NavItem::expand);
    connect(this, &NavBar::shrink, navItem, &NavItem::shrink);
}

/* Events */
void NavBar::leaveEvent(QEvent*)
{
    /* Shrinking animation */
    QPropertyAnimation* animation = new QPropertyAnimation(this, "size");
    animation->setDuration(75);
    animation->setStartValue(size());
    animation->setEndValue(QSize(m_minWidth, height()));
    animation->start(QAbstractAnimation::DeleteWhenStopped);

    //Tells each NavItem to shrink
    emit shrink();
}

void NavBar::enterEvent(QEvent*)
{
    /* Expanding animation */
    QPropertyAnimation* animation = new QPropertyAnimation(this, "size");
    animation->setDuration(75);
    animation->setStartValue(size());
    animation->setEndValue(QSize(m_maxWidth, height()));
    animation->start(QAbstractAnimation::DeleteWhenStopped);

    //Tells each NavItem to expand
    emit expand();
}
