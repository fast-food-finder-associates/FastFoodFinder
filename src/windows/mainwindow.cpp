#include "mainwindow.hpp"
#include "ui_mainwindow.h"
#include "login.hpp"
#include <QDebug>

/* Constructors */
MainWindow::MainWindow()
    : QMainWindow(nullptr), m_ui(new Ui::MainWindow)
{
    m_ui->setupUi(this);
    Login::requestLogin();
    connect(Login::getInstance(), &Login::accepted, this, &MainWindow::show);
}

/* Destructor */
MainWindow::~MainWindow()
{
    delete m_ui;
}

void MainWindow::on_pushButton_clicked()
{
    Login::requestLogin();
}
