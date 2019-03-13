#pragma once
#include <QWidget>

using ID = int;

namespace Ui
{
class RestaurantItem;
}

class RestaurantItem : public QWidget
{
    Q_OBJECT

public:
    /* Constructor */
    RestaurantItem(QWidget*, ID);

    /* Destructor */
    ~RestaurantItem() override;

    /* Getters */
    ID getID() const;
    static QSize getSizeHint();

private:
    ID m_id;
    Ui::RestaurantItem* m_ui;
    static const QSize itemSizeHint;
};
