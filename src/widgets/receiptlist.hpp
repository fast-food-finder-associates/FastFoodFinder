#pragma once

#include <QObject>
#include <QListWidget>
#include <QListWidgetItem>
#include "src/widgets/menulistitem.hpp"
#include "src/widgets/menulist.hpp"
#include "src/datastore/RestaurantDataStore.hpp"
#include "src/widgets/receipt.hpp"

class ReceiptList : public QListWidget
{
public:
    ReceiptList(QWidget* parent, RestaurantDataStore*);
    double makeReciept(IDQtys menuData, bool = false);
    void grandTotal(vector<IDQtys>&, double);
private:
    static const QSize receiptSizeHint;
    RestaurantDataStore *m_store;
};

