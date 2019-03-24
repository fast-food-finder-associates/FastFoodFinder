#pragma once
#include <QWidget>
#include "src/datastore/Restaurant.hpp"

using Qty = int;
using MenuID = int;
using RestaurantID = int;
using IDs = std::pair<RestaurantID,MenuID>;

namespace Ui
{
class MenuListItem;
}

class MenuListItem : public QWidget
{
    Q_OBJECT

public:
    /* Constructor */
    MenuListItem(QWidget* parent, RestaurantID, MenuItem);

    /* Destructor */
    ~MenuListItem();

    /* Getters */
    Qty getQty() const;
    IDs getIDs() const;
    static QSize getItemSizeHint();

    /* Setters */
    void setQty(int);

public slots:
    void showQty(bool);
    void resetQty();

signals:
    void quantityChanged(IDs, Qty) const;

private slots:
    void valueToIDAndValueConverter(int) const;

private:
    IDs m_ids;
    Ui::MenuListItem* m_ui;
    static const QSize itemSizeHint;
};
