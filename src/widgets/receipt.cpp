#include "receipt.hpp"
#include "ui_receipt.h"
#include <QDateTime>

Receipt::Receipt(QWidget *parent, QString total_restName,  ReceiptStates thisTemplate)
    : QWidget(parent),
      m_ui(new Ui::Receipt)
{
    m_ui->setupUi(this);
    m_defaultFontSyle.setFamily("IBM Plex Mono");

    switch(thisTemplate)
    {
    case ReceiptStates::GrandTotalHeader:
        m_ui->receiptStack->setCurrentWidget(m_ui->grandTotalHeader);
        m_ui->GrandTotalHeaderLabel->setFont(m_defaultFontSyle);
        break;
    case ReceiptStates::GrandTotalFooter:
        m_ui->receiptStack->setCurrentWidget(m_ui->grandTotalFooter);
        m_ui->GrandTotalFooterLabel->setFont(m_defaultFontSyle);
        m_ui->GrandTotalFooterLabel_2->setText("$"+total_restName);
        m_ui->GrandTotalFooterLabel_2->setFont(m_defaultFontSyle);
        break;
    case ReceiptStates::GrandTotalThanks:
        m_ui->receiptStack->setCurrentWidget(m_ui->grandTotalThanks);
        m_ui->GrandTotalThanksLabel->setFont(m_defaultFontSyle);
        break;
    case ReceiptStates::GrandTotalDistance:
        m_ui->receiptStack->setCurrentWidget(m_ui->grandTotalDistance);
        m_ui->GrandTotalDistanceLabel_2->setText(total_restName+" mi.");
        m_ui->GrandTotalDistanceLabel->setFont(m_defaultFontSyle);
        m_ui->GrandTotalDistanceLabel_2->setFont(m_defaultFontSyle);
        break;
    case ReceiptStates::HeaderTitle:
        m_ui->receiptStack->setCurrentWidget(m_ui->headerTitle);
        m_ui->restaurantName->setText(total_restName);
        m_ui->restaurantName->setFont(m_defaultFontSyle);
        break;
    case ReceiptStates::HeaderDateTime:
        m_ui->receiptStack->setCurrentWidget(m_ui->headerDateTime);
        m_ui->date->setText(QDate::currentDate().toString());
        m_ui->date->setFont(m_defaultFontSyle);
        m_ui->time->setText(QTime::currentTime().toString());
        m_ui->time->setFont(m_defaultFontSyle);
        break;
    case ReceiptStates::FooterTotal:
        m_ui->receiptStack->setCurrentWidget(m_ui->footerTotal);
        m_ui->total->setText("$"+total_restName);
        m_ui->total->setFont(m_defaultFontSyle);
        m_ui->totalLabel->setFont(m_defaultFontSyle);
        break;
    case ReceiptStates::FooterCustomerService:
        m_ui->receiptStack->setCurrentWidget(m_ui->footerCustomerService);
        m_ui->customerServiceLabel->setFont(m_defaultFontSyle);
        break;
    case ReceiptStates::FooterPhone:
        m_ui->receiptStack->setCurrentWidget(m_ui->footerPhone);
        m_ui->customerServiceLabel_2->setFont(m_defaultFontSyle);
        break;
    case ReceiptStates::BodyHeader:
        m_ui->receiptStack->setCurrentWidget(m_ui->bodyHeader);
        m_ui->qty_2->setFont(m_defaultFontSyle);
        m_ui->item_2->setFont(m_defaultFontSyle);
        m_ui->price_2->setFont(m_defaultFontSyle);
        break;
    case ReceiptStates::Body:
        // Use the other constructor
        break;
    case ReceiptStates::Top:
        m_ui->receiptStack->setCurrentWidget(m_ui->top);
        break;
    case ReceiptStates::Bottom:
        m_ui->receiptStack->setCurrentWidget(m_ui->bottom);
        break;
    }
}

Receipt::Receipt(QWidget *parent, int qty, std::string itemName, double price) :
    QWidget(parent),
    m_ui(new Ui::Receipt)
{
    m_ui->setupUi(this);
    m_defaultFontSyle.setFamily("IBM Plex Mono");
    // Flip stack widget to "body" page
    m_ui->receiptStack->setCurrentWidget(m_ui->body);

    // set label fields
    m_ui->qty->setText(QString::number(qty));
    m_ui->item->setText(QString::fromStdString(itemName));
    m_ui->price->setText("$"+QString::number(price,'f',2));

    m_ui->qty_2->setFont(m_defaultFontSyle);
    m_ui->item_2->setFont(m_defaultFontSyle);
    m_ui->price_2->setFont(m_defaultFontSyle);

    // Sales tax doesn't need qty, if 0 hide qty
    if(qty == 0)
    {
        m_ui->qty->setHidden(true);
        m_ui->item->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    }
}

Receipt::~Receipt()
{
    delete m_ui;
}
