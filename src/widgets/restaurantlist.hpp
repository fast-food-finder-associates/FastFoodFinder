#pragma once
#include <QListWidget>
#include <vector>

using Restaurant = std::pair<QString, double>;
using Restaurants = std::vector<Restaurant>;

class RestaurantList : public QObject
{
    Q_OBJECT

public:
    /* Constructors */
    RestaurantList(QWidget* parent);
    RestaurantList(QWidget* parent, const Restaurants&);

    /* Destructor */
    ~RestaurantList() override;

    /* Setters */
    void setWidth(int);
    void setHeight(int);
    void setSize(QSize);

    /* List modifiers */
    void addItem(const Restaurant&);
    void addItems(const Restaurants&);
    void removeItem(const Restaurant&);
    void removeItems(const Restaurants&);

signals:
    void currentRestaurantChanged(int restaurantID);

private:
    QListWidget* m_listWidget;
    const QFont m_font;
};
