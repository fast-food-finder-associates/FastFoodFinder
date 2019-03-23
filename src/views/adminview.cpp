#include "adminview.hpp"
#include "ui_adminview.h"
#include <QFileDialog>
#include <QDebug>

/* Constructor */
AdminView::AdminView(QWidget* parent, RestaurantDataStore* dataStore)
    : QWidget(parent), m_ui(new Ui::AdminView), m_store(dataStore)
{
    m_ui->setupUi(this);

    /* Stylesheets */
    m_ui->page_restSelect->setStyleSheet("QWidget#page_restSelect { background-color: lightgreen; }");
    m_ui->page_menuSelect->setStyleSheet("QWidget#page_menuSelect { background-color: lightblue; }");
    m_ui->label_restListAvailable->setStyleSheet("QLabel { font-size: 20px; }");
    m_ui->label_restListDeleted->setStyleSheet("QLabel { font-size: 20px; }");
    m_ui->label_menuAvailable->setStyleSheet("QLabel { font-size: 20px; }");
    m_ui->label_menuDeleted->setStyleSheet("QLabel { font-size: 20px; }");

    /* Available restaurant list */
    m_restListAvailable = new RestaurantList(m_ui->widget_restListAvailable);
    m_restListAvailable->setDragDropMode(QAbstractItemView::DragDrop);
    m_restListAvailable->setAcceptDrops(true);

    /* Deleted restaurant list */
    m_restListDeleted = new RestaurantList(m_ui->widget_restListDeleted);
    m_restListDeleted->setDragDropMode(QAbstractItemView::DragDrop);
    m_restListDeleted->setAcceptDrops(true);
    m_restListDeleted->allowDeleted(true);

    /*
     * These connections will unselect items of the other list.
     * This will be used for selecting what restaurant will be chosen
     * when editing a menu.
     */
    connect(m_restListAvailable, &RestaurantList::currentRestaurantChanged,
            [this] { m_restListDeleted->setCurrentRow(-1); });

    connect(m_restListDeleted, &RestaurantList::currentRestaurantChanged,
            [this] { m_restListAvailable->setCurrentRow(-1); });

    /* Menu lists */
    m_menuListAvailable = new MenuList(m_ui->widget_menuAvailable);
    m_menuListDeleted = new MenuList(m_ui->widget_menuDeleted);
    m_menuListDeleted->allowDeleted(true);

    /* These connections are the same as the connections for the restaurant lists above */
    connect(m_menuListAvailable, &MenuList::currentMenuItemChanged,
            [this] { m_menuListDeleted->setCurrentRow(-1); });

    connect(m_menuListDeleted, &MenuList::currentMenuItemChanged,
            [this] { m_menuListAvailable->setCurrentRow(-1); });

    //Instantiates the lists
    resetView();
}

/* Destructor */
AdminView::~AdminView()
{
    delete m_ui;
    delete m_restListAvailable;
    delete m_restListDeleted;
}

/* Public slots */
void AdminView::resetView()
{
    //Reset stack widget
    m_ui->stackedWidget->setCurrentIndex(0);

    /* Reset available restaurant list */
    m_restListAvailable->clear();
    m_restListAvailable->addItems(m_store->list.begin(), m_store->list.end());

    /* Reset deleted restaurant list */
    m_restListDeleted->clear();
    for(Restaurant& rest : m_store->list)
    {
        //Add the item if it is deleted
        if(rest.IsDeleted())
            m_restListDeleted->addItem(rest);
    }


    /* Push buttons */
    m_ui->pushButton_editMenu->setStyleSheet("QPushButton { color: black; }");
}

void AdminView::loadMenuList(RestaurantID id)
{
    /* Clear lists */
    m_menuListAvailable->clear();
    m_menuListDeleted->clear();

    Restaurant rest = m_store->FindbyNumber(id);

    /* Available menu list */
    m_menuListAvailable->addAllItems(rest);

    /* Deleted menu list */
    const std::vector<MenuItem> items = rest.GetMenu();
    for(MenuItem item : items)
    {
        if(item.IsDeleted())
            m_menuListDeleted->addItem(id, item);
    }
}

/* Private slots */
void AdminView::on_pushButton_confirmRestChanges_clicked()
{
    /* Get all the IDs in the list and mark them as available */
    std::vector<RestaurantID> available;
    m_restListAvailable->getRestaurantIDs(available);

    for(RestaurantID id : available)
    {
        if(id != -1)
            m_store->FindbyNumber(id).MarkDeleted(false);
    }

    /* Get all the IDs in the list and mark them as deleted */
    std::vector<RestaurantID> deleted;
    m_restListDeleted->getRestaurantIDs(deleted);

    for(RestaurantID id : deleted)
    {
        if(id != -1)
            m_store->FindbyNumber(id).MarkDeleted(true);
    }

    //Refills the lists
    resetView();
}

void AdminView::on_pushButton_addFromFile_clicked()
{
    QString folder = QFileDialog::getOpenFileName(this, "Add restaurants", QDir::homePath(), "Restaurants file (*.csv)");

    if(!folder.isEmpty())
        m_store->load(folder.toStdString());

    resetView();
}

void AdminView::on_pushButton_editMenu_clicked()
{
    RestaurantID id = m_restListAvailable->getSelected();

    /* If the available list isn't selected */
    if(id == -1)
        id = m_restListDeleted->getSelected();

    /* If the deleted list isn't selected, then none of them are */
    if(id == -1)
    {
        m_ui->pushButton_editMenu->setStyleSheet("QPushButton { color: red; } ");
        return;
    }

    loadMenuList(id);

    m_ui->stackedWidget->setCurrentIndex(1);
}

void AdminView::on_pushButton_selectRest_clicked()
{
    m_ui->stackedWidget->setCurrentIndex(0);
    resetView();
}

void AdminView::on_pushButton_deleteMenuItem_clicked()
{
    IDs id = m_menuListAvailable->getSelected();

    Restaurant& rest = m_store->FindbyNumber(id.first);
    rest.FindMenuItembyNumber(id.second).MarkDeleted(true);

    loadMenuList(id.first);
}

void AdminView::on_pushButton_restoreMenuItem_clicked()
{
    IDs id = m_menuListDeleted->getSelected();

    Restaurant& rest = m_store->FindbyNumber(id.first);
    rest.FindMenuItembyNumber(id.second).MarkDeleted(false);

    loadMenuList(id.first);
}
