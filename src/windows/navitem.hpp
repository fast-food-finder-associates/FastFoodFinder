#ifndef NAVITEM_HPP
#define NAVITEM_HPP

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
    ~NavItem() override;
    void mousePressEvent(QMouseEvent * event) override;
    void setText(QString);
    void setIcon(QString);
    void resizeEvent(QResizeEvent *e) override;

public slots:

signals:
    void onClicked();
private:
    Ui::NavItem *m_nav_ui;
};

#endif // NAVITEM_HPP
