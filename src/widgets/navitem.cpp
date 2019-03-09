#include "navitem.hpp"
#include "ui_navitem.h"
#include <QFont>

/* Constructor */
NavItem::NavItem(QListWidget* parent, QString icon, QString label)
    : QWidget(parent), m_ui(new Ui::NavItem)
{
    m_ui->setupUi(this);

    /* fontAwesome has built-in icons */
    QFont font;
    font.setFamily("fontAwesome");

    /* Label */
    m_ui->navLabel->setWordWrap(true);
    font.setPixelSize(16);
    m_ui->navLabel->setFont(font);
    m_ui->navLabel->setText(label);
    m_ui->navLabel->hide(); //starts off hidden

    /* Icon */
    font.setPixelSize(38);
    m_ui->navIcon->setFont(font);
    m_ui->navIcon->setText(icon);

    setStyleSheet("* { background-color: none; color: white}");
}

/* Destructor */
NavItem::~NavItem()
{
    delete m_ui;
}

/* Public slots */
void NavItem::expand() const
{
    m_ui->navLabel->show();
}

void NavItem::shrink() const
{
    m_ui->navLabel->hide();
}

/* Events */
void NavItem::enterEvent(QEvent*)
{
    setStyleSheet("* { background-color: white; color: black }");
}

void NavItem::leaveEvent(QEvent*)
{
    setStyleSheet("* { background-color: none; color: white }");
}
