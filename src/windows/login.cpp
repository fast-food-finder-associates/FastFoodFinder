#include <QTextStream>
#include <QTimer>
#include <QCryptographicHash>
#include "login.hpp"
#include "ui_login.h"
#include "../utils/exceptions.hpp"

/* Static members */
Login::Type   Login::type         = Login::Type::GUEST;
Login*        Login::instance     = nullptr;
const QString Login::FILE_NAME    = "authFile.txt";

/* Login usage */
Login* Login::requestLogin()
{
    if(instance == nullptr)
    {
        instance = new Login;

        /* Initialize the credential file */
        QFile authFile(FILE_NAME);
        authFile.open(QIODevice::NewOnly);
    }

    instance->resetUi();
    instance->clearFields();
    instance->show();

    return instance;
}

Login::Type Login::getType()
{
    return type;
}

/* Private slots (Login page) */
void Login::on_pushButton_userLogin_clicked()
{
    resetUi();

    try
    {
        QString username = m_ui->lineEdit_username->text();
        QString password = m_ui->lineEdit_password->text();

        authenticate(username, password);
    }
    catch(fff::GeneralException& exception)
    {
        exception.errorWindow();
    }
}

void Login::on_pushButton_guestLogin_clicked()
{
    type = Type::GUEST;
    authSuccessful();
}

void Login::on_pushButton_register_clicked()
{
    resetUi();
    m_ui->stackedWidget->setCurrentWidget(m_ui->page_register);
}

void Login::on_checkBox_showPW_stateChanged(int state)
{
    m_ui->lineEdit_password->setEchoMode((state == Qt::CheckState::Checked ? QLineEdit::EchoMode::Normal
                                                                           : QLineEdit::EchoMode::Password));
}

/* Private slots (Registration page) */
void Login::on_pushButton_confirmReg_clicked()
{
    resetUi();

    try
    {
        QString username = m_ui->lineEdit_usernameReg->text();
        QString password = m_ui->lineEdit_passwordReg->text();
        QString pwConfirm = m_ui->lineEdit_confirmPassword->text();

        registration(username, password, pwConfirm);
    }
    catch(fff::GeneralException& exception)
    {
        exception.errorWindow();
    }
}

void Login::on_pushButton_cancelReg_clicked()
{
    resetUi();
    clearFields();
    m_ui->stackedWidget->setCurrentWidget(m_ui->page_login);
}

void Login::on_checkBox_showPWReg_stateChanged(int state)
{
    m_ui->lineEdit_passwordReg->setEchoMode((state == Qt::CheckState::Checked ? QLineEdit::EchoMode::Normal
                                                                              : QLineEdit::EchoMode::Password));

    m_ui->lineEdit_confirmPassword->setEchoMode((state == Qt::CheckState::Checked ? QLineEdit::EchoMode::Normal
                                                                                  : QLineEdit::EchoMode::Password));
}

/* Constructors */
Login::Login()
    : QDialog(nullptr), m_ui(new Ui::Login), FILE_ERR_MSG("Authentication failed, contact admin!")
{
    m_ui->setupUi(this);
    setModal(true);

    m_ui->stackedWidget->setCurrentWidget(m_ui->page_login);

    setWindowFlags(Qt::MSWindowsFixedSizeDialogHint |
                   Qt::WindowSystemMenuHint |
                   Qt::WindowMinimizeButtonHint |
                   Qt::WindowCloseButtonHint);

    QPixmap pix(":/res/missing.png"); //TODO change logo file path
    QSize labelLogoSize = m_ui->label_logo->size();
    m_ui->label_logo->setPixmap(pix.scaled(labelLogoSize, Qt::KeepAspectRatio));
}

/* Authentication handling */
void Login::authenticate(QString usernameInput, QString passwordInput) const
{
    QFile authFile(FILE_NAME);
    QTextStream qin(&authFile);

    if(!authFile.open(QIODevice::ReadOnly))
    {
        throw fff::BadFile(FILE_ERR_MSG);
    }

    QString usernameFile;
    QString hashedPWFile;
    QString typeFile;
    QString hashedPW = hashString(passwordInput);

    /* Search for correct username and password */
    while(!qin.atEnd())
    {
        usernameFile = qin.readLine();
        hashedPWFile = qin.readLine();
        typeFile = qin.readLine();

        if(usernameFile.isEmpty() || hashedPWFile.isEmpty() || typeFile.isEmpty() ||
          (typeFile != "admin" && typeFile != "user"))
        {
            throw fff::BadFileFormat(FILE_ERR_MSG);
        }
        else if(usernameFile == usernameInput && hashedPWFile == hashedPW)
        {
            type = (typeFile == "admin" ? Type::ADMIN : Type::USER);
            authSuccessful();
            return;
        }
    }

    authFailed();
}

void Login::authSuccessful() const
{
    m_ui->label_message->setStyleSheet("QLabel { background-color: green; color: white; }");
    m_ui->label_message->setText("Login successful");

    //Delays the closing of the window
    QTimer::singleShot(500, instance, SLOT(accept()));
}

void Login::authFailed() const
{
    m_ui->label_message->setStyleSheet("QLabel { background-color: red; color: white; }");
    m_ui->label_message->setText("Username/Password was incorrect");
}

/* Registration handling */
void Login::registration(QString usernameInput, QString passwordInput, QString pwConfirmed) const
{
    /* Check the validity of each input field */
    int flags = 0;

    if(passwordInput != pwConfirmed)
    {
        flags |= RegField::PW | RegField::CPW;
    }

    if(usernameInput.isEmpty())
    {
        flags |= RegField::UN;
    }

    if(passwordInput.isEmpty())
    {
        flags |= RegField::PW;
    }

    if(pwConfirmed.isEmpty())
    {
        flags |= RegField::CPW;
    }

    if(flags != 0)
    {
        regFailed(static_cast<RegField>(flags));
        return;
    }

    QFile authFile(FILE_NAME);
    QTextStream qin(&authFile);

    if(!authFile.open(QIODevice::ReadWrite))
    {
        throw fff::BadFile(FILE_ERR_MSG);
    }

    QString usernameFile;
    QByteArray hashedPW = hashString(passwordInput);

    /* Search for a matching username or data error in file */
    while(!qin.atEnd())
    {
        usernameFile = qin.readLine();

        if(qin.readLine().isEmpty() || qin.readLine().isEmpty()) //Skips the next 2 lines
        {
            throw fff::BadFileFormat(FILE_ERR_MSG);
        }
        else if(usernameInput == usernameFile)
        {
            regFailed(RegField::UN);
            return;
        }
    }

    //Write user's credentials to the end of file
    qin << usernameInput << endl
        << hashedPW << endl
        << "user" << endl;

    regSuccessful();
}

void Login::regSuccessful() const
{
    /* Grab the new user's username and store it into the login */
    QString newUserUsername = m_ui->lineEdit_usernameReg->text();
    clearFields();
    m_ui->lineEdit_username->setText(newUserUsername);

    m_ui->stackedWidget->setCurrentWidget(m_ui->page_login);
    m_ui->label_message->setStyleSheet("QLabel { background-color: green; color: white; }");
    m_ui->label_message->setText("Registration successful");
}

void Login::regFailed(RegField fieldFlags) const
{
    QString style = "QLabel { background-color: red; color: white; }";

    /* Bitwise operations to see if a flag is are set for each flag */
    if((fieldFlags & 1) == RegField::UN)
        m_ui->label_usernameReg->setStyleSheet(style);

    if((fieldFlags & 2) == RegField::PW)
        m_ui->label_passwordReg->setStyleSheet(style);

    if((fieldFlags & 4) == RegField::CPW)
        m_ui->label_confirmPassword->setStyleSheet(style);
}

/* Hash algorithm */
QByteArray Login::hashString(QString string) const
{
    return QCryptographicHash::hash(string.toStdString().data(), QCryptographicHash::Keccak_512).toHex();
}

/* Ui */
void Login::resetUi() const
{
    QString style = "QLabel { background-color: transparent; }";

    m_ui->label_message->setStyleSheet(style);
    m_ui->label_usernameReg->setStyleSheet(style);
    m_ui->label_passwordReg->setStyleSheet(style);
    m_ui->label_confirmPassword->setStyleSheet(style);
    m_ui->label_message->setText("");
}

void Login::clearFields() const
{
    m_ui->lineEdit_password->setText("");
    m_ui->lineEdit_usernameReg->setText("");
    m_ui->lineEdit_passwordReg->setText("");
    m_ui->lineEdit_confirmPassword->setText("");
}
