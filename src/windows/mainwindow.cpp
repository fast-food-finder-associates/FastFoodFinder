#include "mainwindow.hpp"
#include "ui_mainwindow.h"
#include "login.hpp"
#include <vector>
#include <QString>
#include <QFont>
#include <QFontDatabase>
#include <QDebug>
#include <QTimer>
#include "src/datastore/RestaurantDataStore.hpp"

/* Constructors */
MainWindow::MainWindow()
    : QMainWindow(nullptr), m_ui(new Ui::MainWindow)
{
    m_ui->setupUi(this);

    //Doesn't allow window resizing
    setWindowFlags(Qt::MSWindowsFixedSizeDialogHint);

    //Requests a login
    connect(Login::requestLogin(), &Login::accepted, this, &MainWindow::show);

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

    RestaurantDataStore store;
    store.load(""); //TODO add your database directory here (include '/' at the end)

    /* Restaurant list */
    m_restaurantList = new RestaurantList(m_ui->restaurantList);
    m_restaurantList->setDragDropMode(QAbstractItemView::DragDrop);
    m_restaurantList->setAcceptDrops(true);
    m_restaurantList->addItems(store.list.begin(), store.list.end());
}

/* Destructor */
MainWindow::~MainWindow()
{
    delete m_ui;
    delete m_navbar;
    delete m_restaurantList;
}

void MainWindow::on_actionLogout_triggered()
{
    //TODO reset data members here
    hide();
    Login::requestLogin();
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
            m_navbar->item(5)->setSelected(true);
            m_navbar->setCurrentRow(5);
        });
        break;
    case 4:
        changeNavState(ViewStates::MAIN);
        m_navbar->setCurrentRow(0);
        m_ui->mainViews->setCurrentWidget(m_ui->dashboardView);
        break;
    case 5:
        m_ui->inventoryViews->setCurrentWidget(m_ui->searchView);
        break;
    case 6:
        m_ui->inventoryViews->setCurrentWidget(m_ui->addView);
        break;
    case 7:
        m_ui->inventoryViews->setCurrentWidget(m_ui->editView);
        break;
    case 8:
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
        m_navbar->item(4)->setHidden(true);
        m_navbar->item(5)->setHidden(true);
        m_navbar->item(6)->setHidden(true);
        m_navbar->item(7)->setHidden(true);
        m_navbar->item(8)->setHidden(true);
        break;
    case ViewStates::ADMIN:
        m_navbar->item(0)->setHidden(true);
        m_navbar->item(1)->setHidden(true);
        m_navbar->item(2)->setHidden(true);
        m_navbar->item(3)->setHidden(true);
        m_navbar->item(4)->setHidden(false);
        m_navbar->item(5)->setHidden(false);
        m_navbar->item(6)->setHidden(false);
        m_navbar->item(7)->setHidden(false);
        m_navbar->item(8)->setHidden(false);
        break;
    }
}
