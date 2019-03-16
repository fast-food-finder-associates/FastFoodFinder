#include "mainwindow.hpp"
#include "ui_mainwindow.h"
#include "login.hpp"
#include <vector>
#include <QString>
#include <QFont>
#include <QFontDatabase>
#include <QDebug>

const static IDList ids = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

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
    m_navbar->addItem("\uf0c9", "Dashboard");
    m_navbar->addItem("\uf5a0", "Plan\na Trip");
    m_navbar->addItem("\uf0ca", "View\nRestaurants");
    m_navbar->addItem("\uf1c0", "Inventory\nManagement");

    //Initial view for dashboard
    changeView(0);

    /* Restaurant list */
    m_restaurantList = new RestaurantList(m_ui->restaurantList);
    m_restaurantList->setDragDropMode(QAbstractItemView::DragDrop);
    m_restaurantList->setAcceptDrops(true);
    m_restaurantList->addItems(ids);
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
        m_ui->mainViews->setCurrentWidget(m_ui->inventoryManageView);
        break;
    }
}
