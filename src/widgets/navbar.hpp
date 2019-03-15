#pragma once
#include <QListWidget>

class NavBar : public QListWidget
{
    Q_OBJECT

public:
    /* Constructor */
    NavBar(QWidget* parent, int minWidth, int maxWidth, bool expand);

    /* Setters */
    void setHeight(int);
    void setMinWidth(int);
    void setMaxWidth(int);

    void addItem(QString icon, QString label);

signals:
    void expand();
    void shrink();
    void currentItemChanged(int);

private:
    /* Events */
    void leaveEvent(QEvent*) override;
    void enterEvent(QEvent*) override;

    /* Data Members */
    int m_minWidth;
    int m_maxWidth;
};
