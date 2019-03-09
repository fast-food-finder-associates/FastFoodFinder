#pragma once
#include <QMainWindow>
#include "navbar.hpp"

namespace Ui
{
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    /* Constructors */
    MainWindow();

    /* Destructor */
    ~MainWindow() override;

private slots:
    void on_actionLogout_triggered();
    void changeView(int);

private:
    Ui::MainWindow* m_ui;
    NavBar* m_navbar;
};
