#pragma once

#include <QWidget>

namespace Ui {
class Item;
}

class Item : public QWidget
{
    Q_OBJECT

public:
    explicit Item(QWidget *parent = nullptr);
    ~Item();
    void setPixmap(const QPixmap &);
    void setName(QString);
    void setInfo(QString);
private:
    Ui::Item *m_ui;
};

