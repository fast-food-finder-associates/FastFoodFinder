#include "itemlist.hpp"
#include "ui_itemlist.h"

ItemList::ItemList(QWidget *parent) :
    QWidget(parent),
    m_ui(new Ui::ItemList)
{
    m_ui->setupUi(this);
    m_ui->listWidget->raise();
    this->addItem("Grilled Breakfast Burrito","$1.00 | 340 CAL",":/one");
    this->addItem("Grilled Breakfast Burrito\nFiesta Potato","$1.00 | 340 CAL",":/one");
    this->addItem("Bean Burrito","$1.25 | 380 CAL",":/two");
    this->addItem("Quesarito","$2.99 | 650 CAL",":/four");
    this->addItem("Beefy Fritos® Burrito","$1.00 | 440 CAL",":/five");
    this->addItem("Steak Rattlesnake Fries\nBurrito","$2.99 | 470 CAL",":/six");
}

ItemList::~ItemList()
{
    delete m_ui;
}

Item* ItemList::addItem(std::string itemName, std::string itemInfo, std::string itemPic, bool isBack)
{
    QListWidgetItem *listWidgetItem = new QListWidgetItem(m_ui->listWidget);
    m_ui->listWidget->addItem(listWidgetItem);
    Item *tempItem = new Item(m_ui->listWidget);
    QPixmap pic(QString::fromStdString(itemPic));
    QSize picSize(150,99);
    QSize itemSize(160,151);
    listWidgetItem->setSizeHint(itemSize);
    tempItem->setPixmap(pic.scaled(picSize,Qt::KeepAspectRatio));
    tempItem->setName(QString::fromStdString(itemName));
    tempItem->setInfo(QString::fromStdString(itemInfo));
    m_ui->listWidget->setItemWidget(listWidgetItem,tempItem);
    return tempItem;
}


