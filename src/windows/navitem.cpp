#include "navitem.hpp"
#include "mainwindow.hpp"
#include "ui_navitem.h"
//#include <QFontDatabase>
#include <QFont>
#include <QDebug>
#include <QWidget>
#include <QListWidget>

NavItem::NavItem(QWidget *parent) :
    QWidget(parent),
    m_nav_ui(new Ui::NavItem)
{
    m_nav_ui->setupUi(this);
    m_backButton = false;
    QFont navFont;
    navFont.setPixelSize(16);
    navFont.setBold(true);

    m_nav_ui->navLabel->setWordWrap(true);
    m_nav_ui->navLabel->setFont(navFont);
    navFont.setBold(false);
    navFont.setFamily("fontAwesome");
    navFont.setPixelSize(38);
    navFont.setStyle(QFont::StyleNormal);
    m_nav_ui->navIcon->setFont(navFont);
    m_nav_ui->navIcon->setFixedWidth(50);
    this->setFixedHeight(75);
}

NavItem::NavItem(QWidget *parent,QString icon, QString label, bool isBack) :
    QWidget(parent),
    m_nav_ui(new Ui::NavItem)
{
    m_nav_ui->setupUi(this);
    m_backButton = isBack;
    QFont navFont;
    navFont.setPixelSize(16);
    navFont.setBold(true);

    m_nav_ui->navLabel->setWordWrap(true);
    m_nav_ui->navLabel->setFont(navFont);

    navFont.setBold(false);
    navFont.setFamily("fontAwesome");

    navFont.setPixelSize(38);

    navFont.setStyle(QFont::StyleNormal);
    m_nav_ui->navIcon->setFont(navFont);
    m_nav_ui->navIcon->setFixedWidth(50);
    this->setFixedHeight(75);

    this->setIcon(icon);
    this->setLabel(label);

    if(m_backButton)
        this->hideLabel();
}

void NavItem::setLabel(QString str)
{
    m_nav_ui->navLabel->setText(str);
}

void NavItem::setIcon(QString str)
{
    m_nav_ui->navIcon->setText(str);
}

// When the NavBar becomes smaller the NavItem label hides
void NavItem::resizeEvent(QResizeEvent *event)
{
    if(this->width() < 180 && !this->m_backButton)
    {
        this->hideLabel();
    }
    else
    {
        if(!this->m_backButton)
             this->showLabel();
    }
}

NavItem::~NavItem()
{
    delete m_nav_ui;
}

// made signal for clicked for this class
void NavItem::mousePressEvent(QMouseEvent * event)
{
    QWidget::mousePressEvent(event);
    emit onClicked();
}

void NavItem::enterEvent(QEvent * event)
{
    //    qDebug() << this->objectName();
    QWidget::enterEvent(event);

    emit onHover();
    this->setStyleSheet("* {background-color:white;color:black}");

    if(m_backButton)
    {
        this->hideIcon();
        this->showLabel();
    }
}

void NavItem::leaveEvent(QEvent * event)
{
    //    qDebug() << Q_FUNC_INFO << this->objectName();
    QWidget::leaveEvent(event);
    emit onLeave();
    this->setStyleSheet("* {background-color:none;color:white}");

    if(m_backButton)
    {
        this->showIcon();
        this->hideLabel();
    }
}

void NavItem::hideLabel()
{
    this->m_nav_ui->navLabel->hide();
}

void NavItem::hideIcon()
{
    this->m_nav_ui->navIcon->hide();
}


void NavItem::showLabel()
{
    this->m_nav_ui->navLabel->show();
}

void NavItem::showIcon()
{
    this->m_nav_ui->navIcon->show();
}

