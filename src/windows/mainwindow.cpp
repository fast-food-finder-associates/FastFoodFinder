#include "mainwindow.hpp"
#include "ui_mainwindow.h"
#include "login.hpp"
#include "navitem.hpp"
#include <vector>
#include <QString>
#include <QFont>
#include <QFontDatabase>
#include <QDebug>
#include "navbar.hpp"


const static std::vector<QString> restNames = {"MacDonalds","Chipotle","Dominos Pizza","KFC","Subway","In-N-Out Burger","Wendys","Jack in the Box","El Pollo Loco","Papa Johns Pizza","Pizza Hut","Sonic"};
const static std::vector<double> distance = {8,4.29,12.41,7.56,2.67,5.94,8.44,12.75,9.19,14.54,10.1,6.6};
/* Constructors */
MainWindow::MainWindow()
    : QMainWindow(nullptr), m_ui(new Ui::MainWindow)
{
    m_ui->setupUi(this);
    connect(Login::requestLogin(), &Login::accepted, this, &MainWindow::show);

    if (QFontDatabase::addApplicationFont(":/assets/FontAwesome.ttf") == -1)
        qWarning() << "FontAwesome cannot be loaded !";

    NavBar *navigationButtonList = new NavBar(m_ui->NavBarWidget);

    connect(this, SIGNAL(changing(const int)), navigationButtonList, SLOT(resize(const int)));
    connect(navigationButtonList,SIGNAL(newChoice(const int)), this, SLOT(changeView(const int)));
    connect(this,&MainWindow::inventoryView, navigationButtonList, &NavBar::changeToInventoryView);
    connect(this,&MainWindow::mainView, navigationButtonList, &NavBar::changeToMainView);
}


// Navbar height resizes to window height when window height changes
void MainWindow::resizeEvent(QResizeEvent *e)
{
    QWidget::resizeEvent(e);
    m_ui->NavBarWidget->setFixedHeight(this->height());
    m_ui->mainViews->setFixedHeight(this->height());
    m_ui->mainViews->setFixedWidth(this->width());
    emit changing(this->height());
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


void MainWindow::changeView(const int rowView)
{
    qDebug() << rowView;

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
        emit inventoryView();
        break;
    case 4:
        m_ui->mainViews->setCurrentWidget(m_ui->dashboardView);
        emit mainView();
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
