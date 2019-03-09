#pragma once
#include <QListWidget>
#include <QString>
#include <QEvent>

namespace Ui
{
class NavItem;
}

class NavItem : public QWidget
{
    Q_OBJECT

public:
    /* Constructor */
    NavItem(QWidget* parent, QString icon, QString label);

    /* Destructor */
    ~NavItem() override;

public slots:
    void expand() const;
    void shrink() const;

private:
    /* Events */
    void enterEvent(QEvent*) override;
    void leaveEvent(QEvent*) override;

    Ui::NavItem* m_ui;
};
