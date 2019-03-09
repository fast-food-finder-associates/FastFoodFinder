#pragma once
#include <QListWidget>

namespace Ui
{
class NavBar;
}

class NavBar : public QListWidget
{
    Q_OBJECT

public:
    /* Constructor */
    explicit NavBar(QWidget* parent, int minWidth, int maxWidth);

    /* Destructor */
    ~NavBar() override;

    void addItem(QString icon, QString label);
    void setHeight(int);

signals:
    void expand();
    void shrink();
    void currentItemChanged(int);

private:
    void leaveEvent(QEvent*) override;
    void enterEvent(QEvent*) override;

    Ui::NavBar* m_ui;
    const int m_minWidth;
    const int m_maxWidth;
};
