#pragma once
#include <QMainWindow>
#include "src/widgets/navbar.hpp"

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
    void changeViewInvManage(int);

signals:
    void changeCentralStack(QWidget *);
private:
    /* Events */
    void resizeEvent(QResizeEvent*) override;

    Ui::MainWindow* m_ui;
    NavBar* m_navbar;
    NavBar* m_navbar_admin;
};
