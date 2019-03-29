#include "mainwindow.hpp"
#include "ui_mainwindow.h"
#include <QFontDatabase>
#include <QDebug>
#include <QMessageBox>
#include "src/datastore/RestaurantDataStore.hpp"
#include "src/windows/login.hpp"
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


    if(QFontDatabase::addApplicationFont(":/res/IBMPlexMono-Regular.ttf") == -1)
        qWarning() << "IBMPlexMono-Regular cannot be loaded !";

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
    m_store.load("/Users/RogerChavez/Desktop/Group-docs/FastFoodFinder/src/datastore/RestaurantData.csv"); //WARNING Put database filepath here

    /* Initialize views */
    m_restView = new RestaurantsView(m_ui->restaurantsView, &m_store);
    m_adminView = new AdminView(m_ui->adminView, &m_store);
    m_planTrip = new PlanTrip(m_ui->planTripView, &m_store, m_navbar);

    //Triggers changeView() and changes the navbar item
    m_navbar->setCurrentRow(0);
}

/* Destructor */
MainWindow::~MainWindow()
{
    delete m_ui;
    delete m_navbar;
    delete m_restView;
    delete m_adminView;

    //Save data to database file
    m_store.save("/Users/RogerChavez/Desktop/Group-docs/FastFoodFinder/src/datastore/RestaurantData.csv");
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
    /* Reset views */
    m_restView->resetView();
    m_adminView->resetView();
    m_planTrip->resetPlanTripView();
}


void MainWindow::on_pushButton_clicked()
{
    m_navbar->setCurrentRow(1);
}
