#pragma once
#include <QWidget>

namespace Ui
{
class NavBar;
}

class NavBar : public QWidget
{
    Q_OBJECT

public:
    /* Constructor */
    explicit NavBar(QWidget* parent);

    /* Destructor */
    ~NavBar() override;

    void addItem(QString icon, QString label);

signals:
    void expand() const;
    void shrink() const;
    void currentItemChanged(int) const;

private:
    void leaveEvent(QEvent*) override;
    void mouseMoveEvent(QMouseEvent*) override;

    Ui::NavBar* m_ui;
    bool m_expanded;
    const int m_minWidth;
    const int m_maxWidth;
};
