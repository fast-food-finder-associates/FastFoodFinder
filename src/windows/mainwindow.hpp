#pragma once
#include <QMainWindow>

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
    void changeView(const int);
signals:
    void changing(const int);
    void inventoryView();
    void mainView();

private slots:
    void on_actionLogout_triggered();
    void goToPlanTripView();
    void goToRestaurantView();
    void goToInventoryManageView();
signals:

private:
    Ui::MainWindow* m_ui;
};
