#include <QCryptographicHash>
#include <QTextStream>
#include <QTimer>
#include <QDir>
#include "login.hpp"
#include "ui_login.h"
#include "../utils/exceptions.hpp"

/* Static members */
Login::Type   Login::type      = Login::Type::USER;
Login*        Login::instance  = nullptr;
const QString Login::FILE_NAME = "authFile.txt";
const QString Login::FILE_PATH = QDir::homePath() + '/';

/* Login usage */
Login* Login::requestLogin()
{
    if(instance == nullptr)
    {
        instance = new Login;

        /* Initialize the credential file */
        QFile authFile(FILE_PATH + FILE_NAME);
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
void Login::on_pushButton_login_clicked()
{
    resetUi();

    try
    {
        QString username = m_ui->lineEdit_username->text();
        QString password = m_ui->lineEdit_password->text();

        authenticate(username, password);
    }
    catch(GeneralException& exception)
    {
        exception.errorWindow();
    }
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
    catch(GeneralException& exception)
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
}

/* Authentication handling */
void Login::authenticate(QString usernameInput, QString passwordInput) const
{
    QFile authFile(FILE_PATH + FILE_NAME);
    QTextStream qin(&authFile);

    if(!authFile.open(QIODevice::ReadOnly))
    {
        throw BadFile(FILE_ERR_MSG);
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
            throw BadFileFormat(FILE_ERR_MSG);
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
    m_ui->label_loginMsg->setStyleSheet("QLabel { background-color: green; color: white; }");
    m_ui->label_loginMsg->setText("Login successful");

    //Delays the closing of the window
    QTimer::singleShot(500, instance, SLOT(accept()));
}

void Login::authFailed() const
{
    m_ui->label_loginMsg->setStyleSheet("QLabel { background-color: red; color: white; }");
    m_ui->label_loginMsg->setText("Invalid login");
}

/* Registration handling */
void Login::registration(QString usernameInput, QString passwordInput, QString pwConfirmed) const
{
    /* Check the validity of each input field */
    int flags = 0;

    if(usernameInput.isEmpty())
    {
        flags |= RegField::UN;
    }

    if(passwordInput.isEmpty())
    {
        flags |= RegField::PW;
    }

    if(pwConfirmed.isEmpty() || passwordInput != pwConfirmed)
    {
        flags |= RegField::CPW;
    }

    if(flags != 0)
    {
        regFailed(static_cast<RegField>(flags));
        return;
    }

    QFile authFile(FILE_PATH + FILE_NAME);
    QTextStream qin(&authFile);

    if(!authFile.open(QIODevice::ReadWrite))
    {
        throw BadFile(FILE_ERR_MSG);
    }

    QString usernameFile;
    QByteArray hashedPW = hashString(passwordInput);

    /* Search for a matching username or data error in file */
    while(!qin.atEnd())
    {
        usernameFile = qin.readLine();

        if(qin.readLine().isEmpty() || qin.readLine().isEmpty()) //Skips the next 2 lines
        {
            throw BadFileFormat(FILE_ERR_MSG);
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
    m_ui->label_loginMsg->setStyleSheet("QLabel { background-color: green; color: white; }");
    m_ui->label_loginMsg->setText("Registration successful");
}

void Login::regFailed(RegField fieldFlags) const
{
    if(fieldFlags == 0)
        return;

    QString txtStyle = "QLabel { color: red; }";

    /* Initializing the labels with the error marker */
    m_ui->label_regMsg->setText("Invalid fields (*)");
    m_ui->label_regMsg->setStyleSheet(txtStyle);
    m_ui->label_usernameReg->setText("*");
    m_ui->label_passwordReg->setText("*");
    m_ui->label_confirmPassword->setText("*");


    /* Bitwise operations to see if a flag is are set for each flag */
    if((fieldFlags & 1) == RegField::UN)
        m_ui->label_usernameReg->setStyleSheet(txtStyle);

    if((fieldFlags & 2) == RegField::PW)
        m_ui->label_passwordReg->setStyleSheet(txtStyle);

    if((fieldFlags & 4) == RegField::CPW)
        m_ui->label_confirmPassword->setStyleSheet(txtStyle);
}

/* Hash algorithm */
QByteArray Login::hashString(QString string) const
{
    return QCryptographicHash::hash(string.toStdString().data(), QCryptographicHash::Keccak_512).toHex();
}

/* Ui */
void Login::resetUi() const
{
    QString bgStyle = "QLabel { background-color: transparent; }";
    QString txtStyle = "QLabel { color: transparent; }";

    m_ui->label_regMsg->setStyleSheet(bgStyle);
    m_ui->label_loginMsg->setStyleSheet(bgStyle);
    m_ui->label_usernameReg->setStyleSheet(txtStyle);
    m_ui->label_passwordReg->setStyleSheet(txtStyle);
    m_ui->label_confirmPassword->setStyleSheet(txtStyle);
    m_ui->label_loginMsg->setText("");
    m_ui->label_regMsg->setText("");
    m_ui->lineEdit_username->setFocus();
}

void Login::clearFields() const
{
    m_ui->lineEdit_password->setText("");
    m_ui->lineEdit_usernameReg->setText("");
    m_ui->lineEdit_passwordReg->setText("");
    m_ui->lineEdit_confirmPassword->setText("");
}
