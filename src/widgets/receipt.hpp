#pragma once

#include <QWidget>

namespace Ui {
class Receipt;
}

class Receipt : public QWidget
{
    Q_OBJECT
public:
    /* Enum class for each view state */
    enum class ReceiptStates { GrandTotalHeader, GrandTotalFooter, GrandTotalThanks, HeaderTitle, HeaderDateTime, FooterTotal,FooterCustomerService, FooterPhone, BodyHeader, Body, Top, Bottom };

    Receipt(QWidget *parent = nullptr, QString total_restName= "", ReceiptStates = ReceiptStates::HeaderTitle);
    Receipt(QWidget *parent = nullptr, int qty = 0, std::string itemName = "", double price = 0.0);

    ~Receipt();

private:
    Ui::Receipt *m_ui;
    ReceiptStates m_state;
    QFont m_defaultFontSyle;
};

