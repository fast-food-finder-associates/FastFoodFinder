#include "mainwindow.hpp"
#include "ui_mainwindow.h"
#include <QFontDatabase>
#include <QDebug>
#include <QMessageBox>
#include "src/datastore/RestaurantDataStore.hpp"
#include "src/windows/login.hpp"

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
    m_navbar->addItem("\uf0c9", "Dashboard");
    m_navbar->addItem("\uf5a0", "Plan\na Trip");
    m_navbar->addItem("\uf0ca", "View\nRestaurants");
    if(Login::getType() == Login::Type::ADMIN)
        m_navbar->addItem("\uf1c0", "Inventory\nManagement");
    m_navbar->addItem("\uf2f5", "Logout");

    //Load the restaurant database from the file
    m_store.load("D:/Projects/FastFoodFinder/src/datastore/RestaurantData.csv"); //WARNING Put database filepath here

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

    /* Admin view */
    m_adminView = new AdminView(m_ui->adminView, &m_store);

    //Triggers changeView() and changes the navbar item
    m_navbar->setCurrentRow(0);
}

/* Destructor */
MainWindow::~MainWindow()
{
    delete m_ui;
    delete m_navbar;
    delete m_restaurantList;
    delete m_adminView;
}

/* Private slots */
void MainWindow::changeView(int view)
{
    resetUi();

    Login::Type type = Login::getType();

    /* Change view */
    if((view == 3 && type == Login::Type::USER) || //Logout
       (view == 4 && type == Login::Type::ADMIN))
    {
        QMessageBox::StandardButton reply = QMessageBox::question(this, "Logout", "Are you sure you want to logout?", QMessageBox::Yes | QMessageBox::No);
        if(reply == QMessageBox::Yes)
            emit logout();
    }
    else if(view == 3 && type == Login::Type::ADMIN) //Admin view
    {
        m_ui->mainViews->setCurrentIndex(view);
    }
    else
    {
        m_ui->mainViews->setCurrentIndex(view);
    }
}

void MainWindow::resetUi()
{
    /* Restaurant list */
    m_restaurantList->clear();
    m_restaurantList->addItems(m_store.list.begin(), m_store.list.end());

    /* Admin view */
    m_adminView->resetView();
}

void MainWindow::menuListChange(int id)
{
    Restaurant restaurant = m_store.FindbyNumber(id);
    m_ui->currentRestaurantName->setText(QString::fromStdString(restaurant.GetName()));
    m_menuList->addAllItems(restaurant);
}
