#include "navbar.hpp"
#include "ui_navbar.h"
#include "navitem.hpp"
#include <QPropertyAnimation>

/* Constructor */
NavBar::NavBar(QWidget* parent, int minWidth, int maxWidth)
    : QListWidget(parent), m_ui(new Ui::NavBar), m_minWidth(minWidth), m_maxWidth(maxWidth)
{
    m_ui->setupUi(this);
    setStyleSheet("QListWidget { background-color: #303030; }");

    //Initial size
    resize(m_minWidth, parent->height());

    //Rebroadcasts the QListWidget's signal
    connect(this, &QListWidget::currentRowChanged, this, &NavBar::currentItemChanged);
}

/* Destructor */
NavBar::~NavBar()
{
    delete m_ui;
}

void NavBar::setHeight(int height)
{
    resize(width(), height);
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

void NavBar::leaveEvent(QEvent*)
{
    /* Shrinking animation */
    QPropertyAnimation* animation = new QPropertyAnimation(this, "size");
    animation->setDuration(75);
    animation->setStartValue(size());
    animation->setEndValue(QSize(m_minWidth, height()));
    animation->start();

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
    animation->start();

    //Tells each NavItem to expand
    emit expand();
}
