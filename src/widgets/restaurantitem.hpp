#pragma once
#include <QWidget>

using Restaurant = std::pair<QString, double>;

namespace Ui
{
class RestaurantItem;
}

class RestaurantItem : public QWidget
{
    Q_OBJECT

public:
    /* Constructor */
    RestaurantItem(QWidget*, const Restaurant&);

    /* Destructor */
    ~RestaurantItem() override;

    /* Getters */
    static QSize getSizeHint();

private:
    Ui::RestaurantItem* m_ui;
    static const QSize itemSizeHint;
};
