#include "navbar.hpp"
#include "ui_navbar.h"
#include "navitem.hpp"
#include <QPropertyAnimation>
#include <QMouseEvent>

/* Constructor */
NavBar::NavBar(QWidget* parent)
    : QWidget(parent), m_ui(new Ui::NavBar), m_expanded(false), m_minWidth(90), m_maxWidth(220)
{
    m_ui->setupUi(this);
    m_ui->listWidget->raise();
    setMouseTracking(true); //Allows mouse move event to toggle without button events

    connect(m_ui->listWidget, &QListWidget::currentRowChanged, this, &NavBar::currentItemChanged);
}

/* Destructor */
NavBar::~NavBar()
{
    delete m_ui;
}

void NavBar::addItem(QString icon, QString label)
{
    const QSize itemSize(70, 80);

    QListWidgetItem* listWidgetItem = new QListWidgetItem(m_ui->listWidget);
    listWidgetItem->setSizeHint(itemSize);
    m_ui->listWidget->addItem(listWidgetItem);

    /* Set the QListWidgetItem to hold a NavItem */
    NavItem* navItem = new NavItem(m_ui->listWidget, icon, label);
    m_ui->listWidget->setItemWidget(listWidgetItem, navItem);

    /* Allows the NavBar and NavItem to expand and shrink simultaneously */
    connect(this, &NavBar::expand, navItem, &NavItem::expand);
    connect(this, &NavBar::shrink, navItem, &NavItem::shrink);
}

/* Events */
void NavBar::leaveEvent(QEvent*)
{
    m_expanded = false;

    /* Shrinking animation */
    QPropertyAnimation* animation = new QPropertyAnimation(m_ui->listWidget, "size");
    animation->setDuration(75);
    animation->setStartValue(m_ui->listWidget->size());
    animation->setEndValue(QSize(m_minWidth, m_ui->listWidget->height()));
    animation->start();

    //Tells each NavItem to shrink
    emit shrink();
}

void NavBar::mouseMoveEvent(QMouseEvent* event)
{
    if(event->pos().x() <= m_minWidth && !m_expanded)
    {
        m_expanded = true;

        /* Expanding animation */
        QPropertyAnimation* animation = new QPropertyAnimation(m_ui->listWidget, "size");
        animation->setDuration(75);
        animation->setStartValue(m_ui->listWidget->size());
        animation->setEndValue(QSize(m_maxWidth, m_ui->listWidget->height()));
        animation->start();

        //Tells each NavItem to expand
        emit expand();
    }
}
