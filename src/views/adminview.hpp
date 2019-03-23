#pragma once
#include <QWidget>
#include "src/widgets/navbar.hpp"
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
    void resetUi();

private slots:
    void on_pushButton_confirmRestChanges_clicked();
    void on_pushButton_addFromFile_clicked();
    void on_pushButton_editMenu_clicked();
    void on_pushButton_selectRest_clicked();

private:
    Ui::AdminView* m_ui;
    RestaurantDataStore* m_store;
    RestaurantList* m_restListAvailable;
    RestaurantList* m_restListDeleted;
};
