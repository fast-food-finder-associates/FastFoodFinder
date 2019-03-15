#include "mainwindow.hpp"
#include "ui_mainwindow.h"
#include "login.hpp"
#include <vector>
#include <QString>
#include <QFont>
#include <QFontDatabase>
#include <QDebug>
#include <QResizeEvent>
#include <QTimer>
#include <QCursor>

const static std::vector<QString> restNames = {"MacDonalds","Chipotle","Dominos Pizza","KFC","Subway","In-N-Out Burger","Wendys","Jack in the Box","El Pollo Loco","Papa Johns Pizza","Pizza Hut","Sonic"};
const static std::vector<double> distance = {8,4.29,12.41,7.56,2.67,5.94,8.44,12.75,9.19,14.54,10.1,6.6};

/* Constructors */
MainWindow::MainWindow()
    : QMainWindow(nullptr), m_ui(new Ui::MainWindow)
{
    m_ui->setupUi(this);

    //Requests a login
    connect(Login::requestLogin(), &Login::accepted, this, &MainWindow::show);

    /* Load Font awesome - Font Icons */
    if( QFontDatabase::addApplicationFont(":/res/FontAwesome.ttf") == -1)
        qWarning() << "FontAwesome cannot be loaded !";

    /* Initialize navigation bar and items */
    m_navbar = new NavBar(m_ui->NavBarWidget, 90, 220);
    connect(m_navbar, &NavBar::currentItemChanged, this, &MainWindow::changeView);

    /* NavItems for main NavBar State */
    m_navbar->addItem("\uf0c9", "Dashboard");
    m_navbar->addItem("\uf5a0", "Plan\na Trip");
    m_navbar->addItem("\uf03A", "View\nRestaurants");
    m_navbar->addItem("\uf1c0", "Inventory\nManagement");


    /* NavItems for InvManagement NavBar State */
    m_navbar->addItem("\uf137", "Back");
    m_navbar->addItem("\uf002", "Search\nRestaurants");
    m_navbar->addItem("\uf0fe", "Add A\nRestaurant");
    m_navbar->addItem("\uf044", "Edit A\nRestaurant");
    m_navbar->addItem("\uf2ed", "Delete A\nRestaurant");

    // Toggle hide on the Top five NavItems "back" to -> "Delete A\nRestaurant"
    changeNavMain();

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
        changeNavInvManage();
        m_navbar->setDisabled(true);
        m_ui->mainViews->setCurrentWidget(m_ui->InvManageView);
        QTimer::singleShot(100, m_navbar, [&]()
        {
            m_navbar->setEnabled(!m_navbar->isEnabled());
            m_navbar->item(5)->setSelected(true);
            m_navbar->setCurrentRow(5);
        });
        break;
    case 4:
        changeNavMain();
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

/* Toggle NavItems for main NavBar State */
void MainWindow::changeNavInvManage()
{
    m_navbar->item(0)->setHidden(true);
    m_navbar->item(1)->setHidden(true);
    m_navbar->item(2)->setHidden(true);
    m_navbar->item(3)->setHidden(true);
    m_navbar->item(4)->setHidden(false);
    m_navbar->item(5)->setHidden(false);
    m_navbar->item(6)->setHidden(false);
    m_navbar->item(7)->setHidden(false);
    m_navbar->item(8)->setHidden(false);
}

/* Toggle NavItems for InvManagement NavBar State */
void MainWindow::changeNavMain()
{
    m_navbar->item(0)->setHidden(false);
    m_navbar->item(1)->setHidden(false);
    m_navbar->item(2)->setHidden(false);
    m_navbar->item(3)->setHidden(false);
    m_navbar->item(4)->setHidden(true);
    m_navbar->item(5)->setHidden(true);
    m_navbar->item(6)->setHidden(true);
    m_navbar->item(7)->setHidden(true);
    m_navbar->item(8)->setHidden(true);
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
