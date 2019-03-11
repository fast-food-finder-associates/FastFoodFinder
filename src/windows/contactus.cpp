#include "contactus.h"
#include "ui_contactus.h"

//ContactUs::ContactUs(){
//    setWindowFlags(Qt::MSWindowsFixedSizeDialogHint |
//                      Qt::WindowSystemMenuHint |
//                      Qt::WindowMinimizeButtonHint |
//                      Qt::WindowCloseButtonHint);
//}

ContactUs::ContactUs(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ContactUs)
{
    ui->setupUi(this);
}

ContactUs::~ContactUs()
{
    delete ui;
}
