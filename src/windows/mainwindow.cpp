#include "mainwindow.hpp"
#include "ui_mainwindow.h"
#include "login.hpp"

/* Constructors */
MainWindow::MainWindow()
    : QMainWindow(nullptr), m_ui(new Ui::MainWindow)
{
    m_ui->setupUi(this);
    connect(Login::requestLogin(), &Login::accepted, this, &MainWindow::show);
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
