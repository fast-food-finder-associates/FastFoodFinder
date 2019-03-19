#pragma once
#include <QListWidget>
#include "src/widgets/menulistitem.hpp"

using IDQtys = std::map<IDs,Qty>;

class MenuList : public QListWidget
{
    Q_OBJECT

public:
    /* Constructor */
    MenuList(QWidget* parent);

    /* Getters */
    IDQtys getIDQty() const;
    IDs getSelected() const;

    /* List modifiers */
    void addItem(RestaurantID, const MenuItem&);
    void addAllItems(const Restaurant&);
    void removeItem(IDs);

    /* Quantity */
    void showQty(bool) const;
    void resetQty();

signals:
    void currentMenuItemChanged(IDs) const;
    void showQtyEmitter(bool) const;
    void resetQtyEmitter() const;

private slots:
    void currentMenuItemHandler(int row) const;
    void quantityChangedHandler(IDs, Qty);

private:
    IDQtys m_IDQtys;
};
