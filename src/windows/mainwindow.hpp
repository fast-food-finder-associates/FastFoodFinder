#pragma once
#include <QMainWindow>
#include <QWidget>
#include <QListWidgetItem>
#include <QEvent>
#include "navitem.hpp"

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
    void resizeEvent(QResizeEvent *e) override;
    /* Destructor */
    ~MainWindow() override;
public slots:
    void navToggle();
private slots:
    void on_actionLogout_triggered();
    void goToPlanTripView();
    void goToRestaurantView();
    void goToInventoryManageView();
signals:

private:
    Ui::MainWindow* m_ui;
    bool m_toggle;
};
