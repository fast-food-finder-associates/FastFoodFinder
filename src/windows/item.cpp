#include "item.hpp"
#include "ui_item.h"

Item::Item(QWidget *parent) :
    QWidget(parent),
    m_ui(new Ui::Item)
{
    m_ui->setupUi(this);
    m_ui->itemName->setFixedHeight(40);
    m_ui->itemInfo->setFixedHeight(20);
}

Item::~Item()
{
    delete m_ui;
}

void Item::setPixmap(const QPixmap & size)
{
    m_ui->itemPic->setPixmap(size);
}

void Item::setName(QString itemName)
{
    m_ui->itemName->setText(itemName);
}

void Item::setInfo(QString itemInfo)
{
     m_ui->itemInfo->setText(itemInfo);
}
