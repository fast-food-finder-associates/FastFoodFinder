#pragma once
#include <QWidget>
#include "src/widgets/navbar.hpp"
#include "src/widgets/menulist.hpp"
#include "src/widgets/restaurantlist.hpp"
#include "src/datastore/RestaurantDataStore.hpp"

namespace Ui
{
class AdminView;
}

class AdminView : public QWidget
{
    Q_OBJECT

public:
    /* Constructor */
    AdminView(QWidget* parent, RestaurantDataStore*);

    /* Destructor */
    ~AdminView() override;

public slots:
    void resetView();
    void resetUi();

private slots:
    void loadMenuList(RestaurantID);
    void fillMenuItemEditFields(IDs);
    void on_pushButton_confirmRestChanges_clicked();
    void on_pushButton_addFromFile_clicked();
    void on_pushButton_editMenuView_clicked();
    void on_pushButton_selectRestView_clicked();
    void on_pushButton_hideMenuItem_clicked();
    void on_pushButton_restoreMenuItem_clicked();
    void on_pushButton_menuEdit_clicked();

private:
    Ui::AdminView* m_ui;
    RestaurantDataStore* m_store;
    RestaurantList* m_restListAvailable;
    RestaurantList* m_restListDeleted;
    MenuList* m_menuListAvailable;
    MenuList* m_menuListDeleted;
};
