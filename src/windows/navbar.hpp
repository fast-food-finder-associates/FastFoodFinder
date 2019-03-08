#pragma once


#include <QWidget>
#include <QEvent>
#include <QPropertyAnimation>
#include "navitem.hpp"
#include <vector>

namespace Ui {
class NavBar;
}

class NavBar : public QWidget
{
    Q_OBJECT

public:
    explicit NavBar(QWidget *parent = nullptr);
    ~NavBar() override;
    NavItem* addItem(std::string = "", std::string = "", bool = false);
    void enterEvent(QEvent * event) override;
    void leaveEvent(QEvent * event) override;

public slots:
    void navExpand();
    void navShrink();
    void resize(const int);
    void changeToInventoryView();
    void changeToMainView();

signals:
    void navHover();
    void navLeave();
    void newChoice(const int);

private slots:
    void on_listWidget_currentRowChanged(int currentRow);

private:
    Ui::NavBar *m_ui;
    QPropertyAnimation *m_animation_navBar;
};

