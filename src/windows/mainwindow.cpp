#include "mainwindow.hpp"
#include "ui_mainwindow.h"
#include "login.hpp"
#include <vector>
#include <QString>
#include <QFont>
#include <QFontDatabase>
#include <QDebug>

const static std::vector<QString> restNames = {"MacDonalds","Chipotle","Dominos Pizza","KFC","Subway","In-N-Out Burger","Wendys","Jack in the Box","El Pollo Loco","Papa Johns Pizza","Pizza Hut","Sonic"};
const static std::vector<double> distance = {8,4.29,12.41,7.56,2.67,5.94,8.44,12.75,9.19,14.54,10.1,6.6};

/* Constructors */
MainWindow::MainWindow()
    : QMainWindow(nullptr), m_ui(new Ui::MainWindow)
{
    m_ui->setupUi(this);

    //Doesn't allow window resizing
    setWindowFlags(Qt::MSWindowsFixedSizeDialogHint);

    //Requests a login
    connect(Login::requestLogin(), &Login::accepted, this, &MainWindow::show);

    if(QFontDatabase::addApplicationFont(":/res/fontAwesome.otf") == -1)
        qWarning() << "FontAwesome cannot be loaded !";

    /* Initialize navigation bar and items */
    m_navbar = new NavBar(m_ui->NavBarWidget, 90, 220);
    connect(m_navbar, &NavBar::currentItemChanged, this, &MainWindow::changeView);
    m_navbar->addItem("\uf0c9", "Dashboard");
    m_navbar->addItem("\uf124", "Plan\na Trip");
    m_navbar->addItem("\uf0ca", "View\nRestaurants");
    m_navbar->addItem("\uf1c0", "Inventory\nManagement");

    //Initial view for dashboard
    changeView(0);

    /* Restaurant list */
    QSize itemSize1(m_ui->restaurantList->width(), 50);
    m_restaurantList = new RestaurantList(m_ui->restaurantList, itemSize1);
    m_restaurantList->setDragDropMode(QAbstractItemView::DragOnly);
    m_restaurantList->addItems(restNames);

    /* TODO Temporary item list for demonstration */
    QSize itemSize2(m_ui->restaurantList_2->width() / 2 - 15, 50); //30 for the scroll bar
    m_restaurantList2 = new RestaurantList(m_ui->restaurantList_2, itemSize2);
    m_restaurantList2->setDragDropMode(QAbstractItemView::DropOnly);
    m_restaurantList2->addItems(restNames);

    //Connects the current row to the distance
    connect(m_restaurantList, &RestaurantList::currentRestaurantChanged,
            [&](int row){m_ui->restaurant_distance->setText(QString::number(distance[row]));});
}

/* Destructor */
MainWindow::~MainWindow()
{
    delete m_ui;
    delete m_navbar;
    delete m_restaurantList;
    delete m_restaurantList2;
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
