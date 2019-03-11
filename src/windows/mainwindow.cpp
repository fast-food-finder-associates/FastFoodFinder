#include "mainwindow.hpp"
#include "ui_mainwindow.h"
#include "login.hpp"
#include <vector>
#include <QString>
#include <QFont>
#include <QFontDatabase>
#include <QDebug>
#include <QResizeEvent>

const static std::vector<QString> restNames = {"MacDonalds","Chipotle","Dominos Pizza","KFC","Subway","In-N-Out Burger","Wendys","Jack in the Box","El Pollo Loco","Papa Johns Pizza","Pizza Hut","Sonic"};
const static std::vector<double> distance = {8,4.29,12.41,7.56,2.67,5.94,8.44,12.75,9.19,14.54,10.1,6.6};

/* Constructors */
MainWindow::MainWindow()
    : QMainWindow(nullptr), m_ui(new Ui::MainWindow)
{
    m_ui->setupUi(this);

    //Requests a login
    connect(Login::requestLogin(), &Login::accepted, this, &MainWindow::show);

    qDebug() << QFontDatabase::addApplicationFont(":/res/FontAwesome.ttf");
//    qDebug() << QFontDatabase::applicationFontFamilies(0);
//        qWarning() << "FontAwesome cannot be loaded !";


    /* Initialize navigation bar and items */
    m_navbar = new NavBar(m_ui->NavBarWidget, 90, 220);
    connect(m_navbar, &NavBar::currentItemChanged, this, &MainWindow::changeView);
    m_navbar->addItem("\uf0c9", "Dashboard");
    m_navbar->addItem("\uf5a0", "Plan\na Trip");
    m_navbar->addItem("\uf03A", "View\nRestaurants");
    m_navbar->addItem("\uf1c0", "Inventory\nManagement");

    m_navbar_admin = new NavBar(m_ui->NavBarInvManageWidget, 90, 220);
    connect(m_navbar_admin, &NavBar::currentItemChanged, this, &MainWindow::changeViewInvManage);
    m_navbar_admin->addItem("\uf137", "Back");
    m_navbar_admin->addItem("\uf002", "Search\nRestaurants");
    m_navbar_admin->addItem("\uf0fe", "Add A\nRestaurant");
    m_navbar_admin->addItem("\uf044", "Edit A\nRestaurant");
    m_navbar_admin->addItem("\uf2ed", "Delete A\nRestaurant");

    //Initial view for mainView
    m_ui->centralStack->setCurrentWidget(m_ui->mainWindow);

    //Initial view for dashboard
    m_navbar->setCurrentRow(0);
}

/* Destructor */
MainWindow::~MainWindow()
{
    delete m_ui;
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
        m_ui->centralStack->setCurrentWidget(m_ui->InvManageWindow);
        m_navbar_admin->setCurrentRow(1);
     break;
    }
}

/*Swich views for stacks in inventoryViews within the invManageWindow page (page 2) in centralStack*/
void MainWindow::changeViewInvManage(int rowView)
{
    switch(rowView)
    {
    case 0:
        m_ui->centralStack->setCurrentWidget(m_ui->mainWindow);
        m_navbar->setCurrentRow(0);
        break;
    case 1:
        m_ui->inventoryViews->setCurrentWidget(m_ui->searchView);
        break;
    case 2:
        m_ui->inventoryViews->setCurrentWidget(m_ui->addView);
        break;
    case 3:
        m_ui->inventoryViews->setCurrentWidget(m_ui->editView);
        break;
    case 4:
        m_ui->inventoryViews->setCurrentWidget(m_ui->deleteView);
        break;
    }
}

/* Events */
void MainWindow::resizeEvent(QResizeEvent*)
{
    /* Stacked widget */
    m_ui->mainViews->setFixedSize(size());

    /* Navigation bar */
    m_ui->NavBarWidget->setFixedHeight(height());
    m_navbar->setHeight(height());
}
