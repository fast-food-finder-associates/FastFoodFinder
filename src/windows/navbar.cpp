#include "navbar.hpp"
#include "mainwindow.hpp"
#include "ui_navbar.h"
#include <QString>
#include <QDebug>
#include <QSize>

NavBar::NavBar(QWidget *parent) :
    QWidget(parent),
    m_ui(new Ui::NavBar)
{
    m_ui->setupUi(this);
    m_ui->listWidget->raise();

    connect(this, &NavBar::navHover, this, &NavBar::navExpand);
    connect(this, &NavBar::navLeave, this, &NavBar::navShrink);

    this->addItem("\uf0c9","Dashboard");
    this->addItem("\uf124","Plan\nA Trip");
    this->addItem("\uf03A","View\nRestaurants");
    this->addItem("\uf1c0","Inventory\nManagement");
    this->addItem("\uf03B","Back", true);
    this->addItem("\uf002","Search\nRestaurants");
    this->addItem("\uf0fe","Add\nRestaurants");
    this->addItem("\uf044","Edit\nRestaurants");
    this->addItem("\uf1f8","Delete\nRestaurants");

    m_ui->listWidget->item(4)->setHidden(true);
    m_ui->listWidget->item(5)->setHidden(true);
    m_ui->listWidget->item(6)->setHidden(true);
    m_ui->listWidget->item(7)->setHidden(true);
    m_ui->listWidget->item(8)->setHidden(true);

}

NavBar::~NavBar()
{
    delete m_ui;
}

NavItem* NavBar::addItem(std::string icon, std::string label, bool isBack)
{
    QListWidgetItem *listWidgetItem = new QListWidgetItem(m_ui->listWidget);
    m_ui->listWidget->addItem(listWidgetItem);
    NavItem *navItemTemp = new NavItem(m_ui->listWidget,QString::fromStdString(icon), QString::fromStdString(label), isBack);
    QSize setSize(70,80);
    listWidgetItem->setSizeHint(setSize);
    //    qDebug() << listWidgetItem->sizeHint().rheight();
    //    qDebug() << listWidgetItem->sizeHint().rwidth();
    //    qDebug() << navItemTemp->height();
    m_ui->listWidget->setItemWidget(listWidgetItem,navItemTemp);
    m_ui->listWidget->setObjectName(QString::fromStdString(label));
    navItemTemp->setMouseTracking(true);
    return navItemTemp;
}



void NavBar::navExpand()
{
    m_animation_navBar = new QPropertyAnimation(m_ui->listWidget,"size");
    m_animation_navBar->setDuration(150);
    m_animation_navBar->setStartValue(QSize(90, m_ui->listWidget->height()));
    m_animation_navBar->setEndValue(QSize(220, m_ui->listWidget->height()));
    m_animation_navBar->start();
}

void NavBar::navShrink()
{
    m_animation_navBar = new QPropertyAnimation(m_ui->listWidget,"size");
    m_animation_navBar->setDuration(150);
    m_animation_navBar->setStartValue(QSize(220,m_ui->listWidget->height()));
    m_animation_navBar->setEndValue(QSize(90,m_ui->listWidget->height()));
    m_animation_navBar->start();
}

void NavBar::resize(const int resizeHeight)
{
    //   qDebug() << resizeHeight;
    this->setFixedHeight(resizeHeight);
}

void NavBar::enterEvent(QEvent * event)
{
    //    qDebug() << this->objectName();
    QWidget::enterEvent(event);
    emit navHover();
}

void NavBar::leaveEvent(QEvent * event)
{
    //    qDebug() << this->objectName();
    QWidget::leaveEvent(event);
    emit navLeave();
}

void NavBar::on_listWidget_currentRowChanged(int currentRow)
{
    emit newChoice(currentRow);
}

void NavBar::changeToInventoryView()
{
    m_ui->listWidget->item(0)->setHidden(true);
    m_ui->listWidget->item(1)->setHidden(true);
    m_ui->listWidget->item(2)->setHidden(true);
    m_ui->listWidget->item(3)->setHidden(true);
    m_ui->listWidget->item(4)->setHidden(false);
    m_ui->listWidget->item(5)->setHidden(false);
    m_ui->listWidget->setCurrentRow(5);
    m_ui->listWidget->item(5)->setSelected(true);
    m_ui->listWidget->item(6)->setHidden(false);
    m_ui->listWidget->item(7)->setHidden(false);
    m_ui->listWidget->item(8)->setHidden(false);
}

void NavBar::changeToMainView()
{
    m_ui->listWidget->item(0)->setHidden(false);
    m_ui->listWidget->item(1)->setHidden(false);
    m_ui->listWidget->item(2)->setHidden(false);
    m_ui->listWidget->item(3)->setHidden(false);
    m_ui->listWidget->item(4)->setHidden(true);
    m_ui->listWidget->item(5)->setHidden(true);
    m_ui->listWidget->item(6)->setHidden(true);
    m_ui->listWidget->item(7)->setHidden(true);
    m_ui->listWidget->item(8)->setHidden(true);
}
