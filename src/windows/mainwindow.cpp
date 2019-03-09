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
    connect(Login::requestLogin(), &Login::accepted, this, &MainWindow::show);

    if(QFontDatabase::addApplicationFont(":/assets/FontAwesome.ttf") == -1)
        qWarning() << "FontAwesome cannot be loaded !";

    /* Initialize navigation bar */
    m_navbar = new NavBar(m_ui->NavBarWidget, 90, 220);
    connect(m_navbar, &NavBar::currentItemChanged, this, &MainWindow::changeView);
    m_navbar->addItem("\uf0c9", "Dashboard");
    m_navbar->addItem("\uf124", "Plan\na Trip");
    m_navbar->addItem("\uf03A", "View\nRestaurants");
    m_navbar->addItem("\uf1c0", "Inventory\nManagement");

    //Initial view for dashboard
    changeView(0);
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

void MainWindow::resizeEvent(QResizeEvent*)
{
    /* Stacked widget */
    m_ui->mainViews->setFixedSize(size());

    /* NavBar */
    m_ui->NavBarWidget->setFixedHeight(height());
    m_navbar->setHeight(height());
}
