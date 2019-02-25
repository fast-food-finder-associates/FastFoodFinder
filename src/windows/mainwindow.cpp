#include "mainwindow.hpp"
#include "ui_mainwindow.h"
#include "login.hpp"
#include <vector>
#include <QString>
#include <QFont>
#include <QFontDatabase>
const static std::vector<QString> restNames = {"MacDonalds","Chipotle","Dominos Pizza","KFC","Subway","In-N-Out Burger","Wendys","Jack in the Box","El Pollo Loco","Papa Johns Pizza","Pizza Hut","Sonic"};
const static std::vector<double> distance = {8,4.29,12.41,7.56,2.67,5.94,8.44,12.75,9.19,14.54,10.1,6.6};
/* Constructors */
MainWindow::MainWindow()
    : QMainWindow(nullptr), m_ui(new Ui::MainWindow)
{
    m_ui->setupUi(this);
    connect(Login::requestLogin(), &Login::accepted, this, &MainWindow::show);

    for(size_t i = 0; i < restNames.size(); ++i)
    {
       QFont fixed = QFontDatabase::systemFont(QFontDatabase::FixedFont);
       fixed.setWeight(2);
       fixed.setPixelSize(12);
       QListWidgetItem *myItem = new QListWidgetItem(m_ui->listWidget);
       myItem->setText(restNames[i] + ": Distance: "+QString::number(distance[i]));
       myItem->setTextColor(Qt::white);
       myItem->setFont(fixed);
    }
    QFont lblFont;
    lblFont.setBold(true);
    lblFont.setItalic(true);
    lblFont.setPixelSize(20);
    m_ui->restaurantMenuLabel->setFont(lblFont);


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

void MainWindow::on_listWidget_currentRowChanged(int currentRow)
{
    m_selected = static_cast<unsigned int>(currentRow);
    QString msg = restNames[m_selected]+ " restaurants menu items";
    m_ui->restaurantMenuLabel->setText(msg);
}
