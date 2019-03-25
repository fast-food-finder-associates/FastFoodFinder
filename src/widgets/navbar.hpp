#pragma once
#include <QListWidget>

/**
 * @brief NavBar class
 *
 * Provides an easy way to list clickable buttons.
 * Currently, the class uses "Font Awesome 5 Free" for its icons.
 *
 * To use:
 * @code{.cpp}
 * NavBar* navbar = new NavBar(widget, 50, 100);
 * navbar->addItems("\uf0ca", "Button");
 * @endcode
 *
 * This will instantiate the bar under the widget with a
 * minimum width of 50 and maximum width of 100.
 * Then it will add a button called "Button".
 */
class NavBar : public QListWidget
{
    Q_OBJECT

public:
    /* Constructor */
    NavBar(QWidget* parent, int minWidth, int maxWidth);

    /* Setters */
    void setHeight(int);
    void setMinWidth(int);
    void setMaxWidth(int);

    /* List modifiers */
    void addItem(QString icon, QString label);

signals:
    void expand();
    void shrink();

private:
    /* Events */
    void leaveEvent(QEvent*) override;
    void enterEvent(QEvent*) override;

    /* Data Members */
    int m_minWidth;
    int m_maxWidth;
};
