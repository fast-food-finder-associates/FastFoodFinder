#include "navitem.hpp"
#include "mainwindow.hpp"
#include "ui_navitem.h"
#include <QFontDatabase>
#include <QFont>
#include <QDebug>
#include <QWidget>
#include <QListWidget>

NavItem::NavItem(QWidget *parent) :
    QWidget(parent),
    m_nav_ui(new Ui::NavItem)
{
    m_nav_ui->setupUi(this);

    QFont navFont;
    navFont.setPixelSize(10);
    navFont.setBold(true);
    m_nav_ui->navLabel->setWordWrap(true);
    m_nav_ui->navLabel->setFont(navFont);

    if (QFontDatabase::addApplicationFont(":/assets/FontAwesome.ttf") == -1)
        qWarning() << "FontAwesome cannot be loaded !";

    navFont.setBold(false);
    navFont.setFamily("fontAwesome");
    navFont.setWeight(900);

    navFont.setPixelSize(38);

    navFont.setStyle(QFont::StyleNormal);
    m_nav_ui->navIcon->setFont(navFont);
    m_nav_ui->navIcon->setFixedWidth(40);

}


void NavItem::setText(QString str)
{
      m_nav_ui->navLabel->setText(str);
}

void NavItem::setIcon(QString str)
{
      m_nav_ui->navIcon->setText(str);
}

// When the NavBar becomes smaller the NavItem label hides
void NavItem::resizeEvent(QResizeEvent *e)
{
    if(this->width() < 100)
    {
        m_nav_ui->navLabel->hide();
        m_nav_ui->navIcon->setFixedWidth(50);
    }
    else
    {
        m_nav_ui->navLabel->show();
        m_nav_ui->navIcon->setFixedWidth(40);
    }
}

NavItem::~NavItem()
{
    delete m_nav_ui;
}

// made signal for clicked for this class
void NavItem::mousePressEvent(QMouseEvent * event)
{
    emit onClicked();
}
