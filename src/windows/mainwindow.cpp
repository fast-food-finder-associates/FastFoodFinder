#include "mainwindow.hpp"
#include "ui_mainwindow.h"
#include "login.hpp"
#include "navitem.hpp"
#include <vector>
#include <QString>
#include <QFont>
#include <QFontDatabase>
#include <iostream>
#include <QDebug>
#include <QWidget>
#include <QListWidgetItem>


const int WINDOW_RESIZE = 130;
const static std::vector<QString> restNames = {"MacDonalds","Chipotle","Dominos Pizza","KFC","Subway","In-N-Out Burger","Wendys","Jack in the Box","El Pollo Loco","Papa Johns Pizza","Pizza Hut","Sonic"};
const static std::vector<double> distance = {8,4.29,12.41,7.56,2.67,5.94,8.44,12.75,9.19,14.54,10.1,6.6};
/* Constructors */
MainWindow::MainWindow()
    : QMainWindow(nullptr), m_ui(new Ui::MainWindow)
{
    m_ui->setupUi(this);
    connect(Login::requestLogin(), &Login::accepted, this, &MainWindow::show);

      QListWidgetItem *listWidgetItem = new QListWidgetItem(m_ui->navigationButtonList);
      m_ui->navigationButtonList->addItem(listWidgetItem);

      NavItem *dashboard = new NavItem;
      NavItem *planTrip = new NavItem;
      NavItem *viewRestaurants = new NavItem;
      NavItem *inventoryManagement = new NavItem;

      listWidgetItem->setSizeHint(dashboard->sizeHint());
      m_ui->navigationButtonList->setItemWidget(listWidgetItem,dashboard);
      dashboard->setText(QString::fromUtf8("Dashboard"));
      dashboard->setIcon(QString::fromUtf8("\uf0c9"));
      dashboard->setObjectName("dashboard");
      dashboard->setMouseTracking(true);

      listWidgetItem = new QListWidgetItem(m_ui->navigationButtonList);
      m_ui->navigationButtonList->addItem(listWidgetItem);
      listWidgetItem->setSizeHint(planTrip->sizeHint());
      m_ui->navigationButtonList->setItemWidget(listWidgetItem,planTrip);
      planTrip->setText(QString::fromUtf8("Plan\nA Trip"));
      planTrip->setIcon(QString::fromUtf8("\uf1b9"));
      planTrip->setObjectName("planTrip");

      listWidgetItem = new QListWidgetItem(m_ui->navigationButtonList);
      m_ui->navigationButtonList->addItem(listWidgetItem);
      listWidgetItem->setSizeHint(viewRestaurants->sizeHint());
      m_ui->navigationButtonList->setItemWidget(listWidgetItem,viewRestaurants);
      viewRestaurants->setText(QString::fromUtf8("View\nRestaurants"));
      viewRestaurants->setIcon(QString::fromUtf8("\uf03A"));

      listWidgetItem = new QListWidgetItem(m_ui->navigationButtonList);
      m_ui->navigationButtonList->addItem(listWidgetItem);
      listWidgetItem->setSizeHint(inventoryManagement->sizeHint());
      m_ui->navigationButtonList->setItemWidget(listWidgetItem,inventoryManagement);
      inventoryManagement->setText(QString::fromUtf8("Inventory\nManagement"));
      inventoryManagement->setIcon(QString::fromUtf8("\uf1c0"));

      connect(dashboard, &NavItem::onClicked,this, &MainWindow::navToggle);
      connect(planTrip, &NavItem::onClicked,this, &MainWindow::goToPlanTripView);
      connect(viewRestaurants, &NavItem::onClicked,this, &MainWindow::goToRestaurantView);
      connect(inventoryManagement, &NavItem::onClicked,this, &MainWindow::goToInventoryManageView);
}


// Navbar height resizes to window height when window height changes
void MainWindow::resizeEvent(QResizeEvent *e)
{
    m_ui->navigationButtonList->setFixedHeight(this->height());
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

// Resizes NavBar
void MainWindow::navToggle()
{
    m_toggle ^=1;
    if(m_toggle)
    {
        m_ui->navigationButtonList->setFixedWidth(m_ui->navigationButtonList->width()-WINDOW_RESIZE);
        m_ui->mainViews->setFixedWidth(m_ui->mainViews->width()+WINDOW_RESIZE);
        m_ui->mainViews->move(m_ui->navigationButtonList->width(),0);
    }
    else
    {
        m_ui->navigationButtonList->setFixedWidth(m_ui->navigationButtonList->width()+WINDOW_RESIZE);
        m_ui->mainViews->setFixedWidth(m_ui->mainViews->width()-WINDOW_RESIZE);
        m_ui->mainViews->move(m_ui->navigationButtonList->width(),0);
    }

}

void MainWindow::goToPlanTripView()
{
     m_ui->mainViews->setCurrentWidget(m_ui->planTripView);
}

void MainWindow::goToRestaurantView()
{
    m_ui->mainViews->setCurrentWidget(m_ui->viewRestaurantView);
}

void MainWindow::goToInventoryManageView()
{
    m_ui->mainViews->setCurrentWidget(m_ui->inventoryManageView);
}


