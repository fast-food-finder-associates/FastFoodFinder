#include "mainwindow.hpp"
#include "ui_mainwindow.h"
#include <vector>
#include <QString>
#include <QFont>
#include <QFontDatabase>
#include <QDebug>
#include <QTimer>
#include <QMessageBox>
#include "src/datastore/RestaurantDataStore.hpp"
#include "src/datastore/TripDataStore.hpp"

/* Constructors */
MainWindow::MainWindow()
    : QMainWindow(nullptr), m_ui(new Ui::MainWindow)
{
    m_ui->setupUi(this);

    //Doesn't allow window resizing
    setWindowFlags(Qt::MSWindowsFixedSizeDialogHint);

    if(QFontDatabase::addApplicationFont(":/res/fontAwesome.ttf") == -1)
        qWarning() << "FontAwesome cannot be loaded !";

    /* Initialize navigation bar and items */
    m_navbar = new NavBar(m_ui->NavBarWidget, 90, 220);
    connect(m_navbar, &NavBar::currentRowChanged, this, &MainWindow::changeView);

    /* NavItems for main NavBar State */
    m_navbar->addItem("\uf0c9", "Dashboard");
    m_navbar->addItem("\uf5a0", "Plan\na Trip");
    m_navbar->addItem("\uf0ca", "View\nRestaurants");
    m_navbar->addItem("\uf1c0", "Inventory\nManagement");
    m_navbar->addItem("\uf2f5", "Logout");


    /* NavItems for InvManagement NavBar State */
    m_navbar->addItem("\uf137", "Back");
    m_navbar->addItem("\uf002", "Search\nRestaurants");
    m_navbar->addItem("\uf0fe", "Add A\nRestaurant");
    m_navbar->addItem("\uf044", "Edit A\nRestaurant");
    m_navbar->addItem("\uf2ed", "Delete A\nRestaurant");

    // Set's MAIN NavItems to show and ADMIN NavItems to hide
    changeNavState(ViewStates::MAIN);

    //Initial view for dashboard
    changeView(0);

    //Load the restaurant database from the file
    m_store.load(""); //WARNING Put database filepath here

    /* Restaurant list */
    m_restaurantList = new RestaurantList(m_ui->restaurantList);
    m_restaurantList->addItems(m_store.list.begin(), m_store.list.end());

    /* Menu list */
    m_menuList = new MenuList(m_ui->menuList);
    m_menuList->setWrapping(true);
    m_menuList->setFlow(QListView::LeftToRight);

    //On current restaurant change, display its menu items
    connect(m_restaurantList, &RestaurantList::currentRestaurantChanged,
            this, &MainWindow::menuListChange);

    /* planTrip object - takes care of planning and taking trips */
    m_planTrip = new PlanTrip(m_ui->planTripView, &m_store, m_navbar);

}

/* Destructor */
MainWindow::~MainWindow()
{
    delete m_ui;
    delete m_navbar;
    delete m_restaurantList;
}

/*Swich views for stacks in mainView within the mainWindow page (page 1) in centralStack*/
void MainWindow::changeView(int rowView)
{
    switch(rowView)
    {
    case 0:
        m_ui->mainViews->setCurrentWidget(m_ui->dashboardView);
        break;
    case 1:
        m_planTrip->resetPlanTripView();
        m_ui->mainViews->setCurrentWidget(m_ui->planTripView);
        break;
    case 2:
        m_ui->mainViews->setCurrentWidget(m_ui->viewRestaurantView);
        break;
    case 3:
        changeNavState(ViewStates::ADMIN);
        m_navbar->setDisabled(true);
        m_ui->mainViews->setCurrentWidget(m_ui->InvManageView);
        QTimer::singleShot(15, m_navbar, [&]()
        {
            m_navbar->setEnabled(true);
            m_navbar->item(6)->setSelected(true);
            m_navbar->setCurrentRow(6);
        });
        break;
    case 4:
    {
        QMessageBox::StandardButton reply = QMessageBox::question(this, "Logout", "Are you sure you want to logout?", QMessageBox::Yes | QMessageBox::No);
        if(reply == QMessageBox::Yes)
            emit logout();
    }
        break;
    case 5:
        changeNavState(ViewStates::MAIN);
        m_navbar->setCurrentRow(0);
        m_ui->mainViews->setCurrentWidget(m_ui->dashboardView);
        break;
    case 6:
        m_ui->inventoryViews->setCurrentWidget(m_ui->searchView);
        break;
    case 7:
        m_ui->inventoryViews->setCurrentWidget(m_ui->addView);
        break;
    case 8:
        m_ui->inventoryViews->setCurrentWidget(m_ui->editView);
        break;
    case 9:
        m_ui->inventoryViews->setCurrentWidget(m_ui->deleteView);
        break;
    }
}

/* Switches between MAIN and ADMIN NavBar State */
void MainWindow::changeNavState(ViewStates state)
{
    switch(state)
    {
    case ViewStates::MAIN:
        m_navbar->item(0)->setHidden(false);
        m_navbar->item(1)->setHidden(false);
        m_navbar->item(2)->setHidden(false);
        m_navbar->item(3)->setHidden(false);
        m_navbar->item(4)->setHidden(false);
        m_navbar->item(5)->setHidden(true);
        m_navbar->item(6)->setHidden(true);
        m_navbar->item(7)->setHidden(true);
        m_navbar->item(8)->setHidden(true);
        m_navbar->item(9)->setHidden(true);
        break;
    case ViewStates::ADMIN:
        m_navbar->item(0)->setHidden(true);
        m_navbar->item(1)->setHidden(true);
        m_navbar->item(2)->setHidden(true);
        m_navbar->item(3)->setHidden(true);
        m_navbar->item(4)->setHidden(true);
        m_navbar->item(5)->setHidden(false);
        m_navbar->item(6)->setHidden(false);
        m_navbar->item(7)->setHidden(false);
        m_navbar->item(8)->setHidden(false);
        m_navbar->item(9)->setHidden(false);
        break;
    }
}

void MainWindow::menuListChange(int id)
{
    Restaurant restaurant = m_store.FindbyNumber(id);
    m_ui->currentRestaurantName->setText(QString::fromStdString(restaurant.GetName()));
    m_menuList->addAllItems(restaurant);
}

