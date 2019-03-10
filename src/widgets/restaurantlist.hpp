#pragma once
#include <QListWidget>
#include <vector>

using Restaurant = QString;
using Restaurants = std::vector<Restaurant>;

class RestaurantList : public QObject
{
    Q_OBJECT

public:
    /* Constructor */
    RestaurantList(QWidget* parent);

    /* Destructor */
    ~RestaurantList() override;

    /* Getters */
    int getWidth() const;
    int getHeight() const;
    QSize getSize() const;
    QFont getFont() const;

    /* Setters */
    void setWidth(int);
    void setHeight(int);
    void setSize(QSize);
    void setFont(QFont);

    /* List modifiers */
    void addItem(const Restaurant&);
    void addItems(const Restaurants&);
    void removeItem(const Restaurant&);
    void removeItems(const Restaurants&);

signals:
    void currentRestaurantChanged(int restaurantID);

private:
    QListWidget* m_listWidget;
};
