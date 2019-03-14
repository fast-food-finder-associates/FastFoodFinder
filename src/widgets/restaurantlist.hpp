#pragma once
#include <vector>
#include <QListWidget>

using ID = int;
using IDList = std::vector<ID>;

class RestaurantList : public QListWidget
{
    Q_OBJECT

public:
    /* Constructor */
    RestaurantList(QWidget* parent);

    /* Static getters */
    static QSize getItemSizeHint();

    /* List modifiers */
    void addItem(ID);
    void addItems(const IDList&);
    void removeItem(ID);
    void removeItems(const IDList&);
    void clearItems();

signals:
    void currentRestaurantChanged(ID) const;

private slots:
    void rowToIDConverter(int row) const;

private:
    static const QSize itemSizeHint;
};
