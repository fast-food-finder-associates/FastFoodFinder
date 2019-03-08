#pragma once
#include <QWidget>
#include <QString>
#include <QEvent>
#include <QListWidget>
#include <QMouseEvent>

namespace Ui {
class NavItem;
}

class NavItem : public QWidget
{
    Q_OBJECT

public:
    explicit NavItem(QWidget *parent = nullptr);
    NavItem(QWidget *parent = nullptr,QString icon = "",QString label = "", bool isBack = false);
    ~NavItem() override;
    void mousePressEvent(QMouseEvent * event) override;
    void setLabel(QString);
    void setIcon(QString);
    void hideLabel();
    void hideIcon();
    void showLabel();
    void showIcon();
    void resizeEvent(QResizeEvent *event) override;
    void enterEvent(QEvent * event) override;
    void leaveEvent(QEvent * event) override;
public slots:

signals:
    void onClicked();
    void onHover();
    void onLeave();
private:
    Ui::NavItem *m_nav_ui;
    bool m_backButton;
};

