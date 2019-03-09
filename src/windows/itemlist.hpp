#pragma once

#include <QWidget>
#include "item.hpp"

namespace Ui {
class ItemList;
}

class ItemList : public QWidget
{
    Q_OBJECT

public:
    explicit ItemList(QWidget *parent = nullptr);
    Item* addItem(std::string = "", std::string = "", std::string = ":/missing", bool = false);
    ~ItemList() override;

private:
    Ui::ItemList *m_ui;
};

