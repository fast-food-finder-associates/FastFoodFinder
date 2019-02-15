#include <QTextStream>
#include <QTimer>
#include "login.hpp"
#include "ui_login.h"
#include "../utils/exceptions.hpp"

/* Static members */
Login::Type Login::m_type     = Login::Type::GUEST;
Login*      Login::m_instance = nullptr;

/* Singleton access */
Login* Login::getInstance()
{
    return m_instance;
}

/* Login usage */
void Login::requestLogin()
{
    if(m_instance == nullptr)
        m_instance = new Login;

    m_instance->resetUi();
    m_instance->show();
}

Login::Type Login::getType()
{
    return m_type;
}

/* Private slots */
void Login::on_pushButton_registered_clicked()
{
    try
    {
        QString usernameInput = m_ui->lineEdit_username->text();
        QString passwordInput = m_ui->lineEdit_password->text();

        if(authenticate(usernameInput, passwordInput))
        {
            authSuccessful();
        }
        else
        {
            authFailed();
        }
    }
    catch(fff::GeneralException& exception)
    {
        exception.errorWindow();
    }
}

void Login::on_pushButton_guest_clicked()
{
    m_type = Type::GUEST;
    authSuccessful();
}

void Login::on_checkBox_showPW_stateChanged(int state)
{
    m_ui->lineEdit_password->setEchoMode((state == Qt::CheckState::Checked ? QLineEdit::EchoMode::Normal
                                                                           : QLineEdit::EchoMode::Password));
}

/* Authentication handling */
bool Login::authenticate(QString usernameInput, QString passwordInput) const
{
    QString fileErrMsg = "Authentication failed, contact admin!";
    QFile authFile(":/res/login/auth.txt"); //TODO change auth file path
    QTextStream qin(&authFile);

    if(!authFile.open(QIODevice::ReadOnly))
    {
        throw fff::BadFile(fileErrMsg);
    }

    QString usernameFile;
    QString passwordFile;
    QString accTypeFile;
    bool authValid = false;

    /* Search for correct username and password */
    while(!authValid && !qin.atEnd())
    {
        usernameFile = qin.readLine();
        passwordFile = qin.readLine();
        accTypeFile  = qin.readLine();

        if(usernameFile.isEmpty() || passwordFile.isEmpty() || accTypeFile.isEmpty())
        {
            throw fff::BadFileFormat(fileErrMsg);
        }
        else if(usernameFile == usernameInput && passwordFile == passwordInput)
        {
            authValid = true;

            if(accTypeFile == "admin")
            {
                m_type = Type::ADMIN;
            }
            else if(accTypeFile == "user")
            {
                m_type = Type::USER;
            }
            else
            {
                throw fff::BadFileFormat(fileErrMsg);
            }
        }
    }

    authFile.close();

    return authValid;
}

/* Constructors */
Login::Login()
    : QDialog(nullptr), m_ui(new Ui::Login)
{
    m_ui->setupUi(this);
    setModal(true);

    setWindowFlags(Qt::MSWindowsFixedSizeDialogHint |
                   Qt::WindowSystemMenuHint |
                   Qt::WindowMinimizeButtonHint |
                   Qt::WindowCloseButtonHint);

    QPixmap pix(":/res/missing.png"); //TODO change logo file path
    m_ui->label_logo->setPixmap(pix.scaled(150, 150, Qt::KeepAspectRatio));
}

void Login::authSuccessful() const
{
    m_ui->label_message->setStyleSheet(" QLabel { background-color: green; color: white; } ");
    m_ui->label_message->setText("Login successful");

    QTimer::singleShot(500, m_instance, SLOT(accept()));
}

void Login::authFailed() const
{
    m_ui->label_message->setStyleSheet(" QLabel { background-color: red; color: white; }");
    m_ui->label_message->setText("Username/Password was incorrect");
}

/* Ui */
void Login::resetUi()
{
    m_ui->label_message->setStyleSheet(" QLabel { background-color: transparent; color: white; }");
    m_ui->label_message->setText("");
}
