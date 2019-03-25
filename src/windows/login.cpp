#include "login.hpp"
#include "ui_login.h"
#include <QCryptographicHash>
#include <QTextStream>
#include <QTimer>
#include <QDir>
#include "src/utils/exceptions.hpp"

/* Static variables */
Login::Type   Login::type         = Login::Type::USER;
Login*        Login::instance     = nullptr;
const QString Login::FILE_NAME    = "authFile.txt";
const QString Login::FILE_PATH    = QDir::homePath() + '/';
const QString Login::FILE_ERR_MSG = "Authentication failed, contact admin!";

/**
 * @brief Getter
 *
 * If there isn't a current instance, one will be created as well as the credential file.
 *
 * @return Singleton instance
 */
Login* Login::getInstance()
{
    if(instance == nullptr)
    {
        instance = new Login;

        /* Initialize the credential file if it doesn't exist */
        QFile authFile(FILE_PATH + FILE_NAME);
        authFile.open(QIODevice::NewOnly);
    }

    return instance;
}

/**
 * @brief Getter
 *
 * Returns the login type of the last user that logged in
 *
 * @return Login type of the last user that logged in
 */
Login::Type Login::getType()
{
    return type;
}

/**
 * @brief Login usage
 *
 * Requests a login screen. Calls getInstance() in case it hasn't been called yet.
 */
void Login::requestLogin()
{
    //Initializes the singleton object just in case
    getInstance();

    instance->resetUi();
    instance->clearFields();
    instance->show();
}

/**
 * @brief Login request button
 *
 * Upon clicking the login button, obtain the login credential fields and validate them.
 * If any exception was throw, an error window will show with details.
 */
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

/**
 * @brief Registeration view button
 *
 * Upon clicking the register button, the current view will change.
 */
void Login::on_pushButton_register_clicked()
{
    resetUi();
    m_ui->stackedWidget->setCurrentWidget(m_ui->page_register);
}

/**
 * @brief Show password button
 *
 * Upon toggling the show password checkbox, the password field will toggle between asterisks and letters.
 */
void Login::on_checkBox_showPW_stateChanged(int state)
{
    m_ui->lineEdit_password->setEchoMode((state == Qt::CheckState::Checked ? QLineEdit::EchoMode::Normal
                                                                           : QLineEdit::EchoMode::Password));
}

/**
 * @brief Confirm registration button
 *
 * Upon clicking the "confirm register" button, obtain the registration credential fields and validate them.
 * If any exception was thrown, an error window will show with details.
 */
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

/**
 * @brief Cancel registration button
 *
 * Upon clicking the "cancel register" button, the current view will change to the login view.
 */
void Login::on_pushButton_cancelReg_clicked()
{
    resetUi();
    clearFields();
    m_ui->stackedWidget->setCurrentWidget(m_ui->page_login);
}

/**
 * @brief Login default constructor
 *
 * Instantiates the login UI. Current view will be set to the login view. Window flags are set.
 */
Login::Login()
    : QDialog(nullptr), m_ui(new Ui::Login)
{
    m_ui->setupUi(this);
    setModal(true);

    m_ui->stackedWidget->setCurrentWidget(m_ui->page_login);

    setWindowFlags(Qt::MSWindowsFixedSizeDialogHint |
                   Qt::WindowSystemMenuHint |
                   Qt::WindowMinimizeButtonHint |
                   Qt::WindowCloseButtonHint);
}

/**
 * @brief Login authenticator
 *
 * Validates the given credentials against the credentials file.
 * Exceptions are thrown if the file couldn't be opened in ReadOnly mode and the file format is wrong.
 * Sets the user type static variable if the credentials are correct.
 *
 * @param usernameInput The username to authenticate
 * @param passwordInput The password to authenticate
 */
void Login::authenticate(QString usernameInput, QString passwordInput) const
{
    QFile authFile(FILE_PATH + FILE_NAME);
    QTextStream qin(&authFile);

    /* Check if file is open */
    if(!authFile.open(QIODevice::ReadOnly))
        throw BadFile(FILE_ERR_MSG);

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

/**
 * @brief Successful login
 *
 * Displays to the user that the login was successful and accepts the dialog.
 */
void Login::authSuccessful() const
{
    m_ui->label_loginMsg->setStyleSheet("QLabel { background-color: green; color: white; }");
    m_ui->label_loginMsg->setText("Login successful");

    //Delays the closing of the window
    QTimer::singleShot(500, instance, &QDialog::accept);
}

/**
 * @brief Unsuccessful login
 *
 * Displays to the user that the login was unsuccessful.
 */
void Login::authFailed() const
{
    m_ui->label_loginMsg->setStyleSheet("QLabel { background-color: red; color: white; }");
    m_ui->label_loginMsg->setText("Invalid login");
}

/**
 * @brief Login registrator
 *
 * Checks if any of the fields are invalid; if they are, call regFailed() and return.
 * Exceptions are thrown if the file couldn't be opened in ReadWrite mode and the file format is wrong.
 * Checks against the file if the username given is unique, if it isn't call regFailed() and return.
 * If the registration is good, write to the file the given credentials.
 *
 * @param usernameInput The username to register
 * @param passwordInput The password to register
 * @param pwConfirmed The confirmation password
 */
void Login::registration(QString usernameInput, QString passwordInput, QString pwConfirmed) const
{
    /* Check the validity of each input field */
    int flags = 0;

    if(usernameInput.isEmpty())
        flags |= RegField::UN;

    if(passwordInput.isEmpty())
        flags |= RegField::PW;

    if(pwConfirmed.isEmpty() || passwordInput != pwConfirmed)
        flags |= RegField::CPW;

    if(flags != 0)
    {
        regFailed(static_cast<RegField>(flags));
        return;
    }

    QFile authFile(FILE_PATH + FILE_NAME);
    QTextStream qin(&authFile);

    /* Check if file is open */
    if(!authFile.open(QIODevice::ReadWrite))
        throw BadFile(FILE_ERR_MSG);

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

/**
 * @brief Registration successful
 *
 * Grabs the newly registered username and put it in the login username field.
 * Changes the view to the login view and displays that the registration was successful.
 */
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

/**
 * @brief Registration unsuccessful
 *
 * If no flags are set, return.
 * Sets the flag's respective field to red.
 *
 * @param fieldFlags The fields that were invalid
 */
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

/**
 * @brief Hash function
 *
 * Returns a hashed version of the given string with a cryptographic hash function.
 *
 * @param string The string to hash
 * @return Hashed string
 */
QByteArray Login::hashString(QString string) const
{
    return QCryptographicHash::hash(string.toStdString().data(), QCryptographicHash::Keccak_512).toHex();
}

/**
 * @brief UI reset
 *
 * Called whenever a view is changed to reset the UI.
 */
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

/**
 * @brief Clear fields
 *
 * Called whenever a view is changed to clear input fields.
 */
void Login::clearFields() const
{
    m_ui->lineEdit_password->setText("");
    m_ui->lineEdit_usernameReg->setText("");
    m_ui->lineEdit_passwordReg->setText("");
    m_ui->lineEdit_confirmPassword->setText("");
}
