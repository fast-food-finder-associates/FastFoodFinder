#pragma once
#include <QMainWindow>
#include "src/widgets/navbar.hpp"
#include "src/widgets/restaurantlist.hpp"

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

    /* Enum class for each view state */
    enum class ViewStates { MAIN, ADMIN };

signals:
    void logout() const;

private slots:
    void changeView(int);
    void changeNavState(ViewStates);

private:
    Ui::MainWindow* m_ui;
    NavBar* m_navbar;
    RestaurantList* m_restaurantList;
};
