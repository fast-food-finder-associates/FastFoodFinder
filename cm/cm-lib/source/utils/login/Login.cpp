#include <utils/login/Login.hpp>
#include <utils/exceptions/exceptions.hpp>
#include <QCryptographicHash>
#include <QTextStream>
#include <QFile>
#include <QDir>

namespace cm
{
namespace utils
{
/* Static members */
Login*          Login::instance       = nullptr;
Login::Type     Login::type           = Login::Type::USER;
Login::RegField Login::failedRegField = static_cast<Login::RegField>(0);

/* Type */
Login::Type Login::getType()
{
    return type;
}

/* Failed registration fields */
Login::RegField Login::getFailedRegFields()
{
    return failedRegField;
}

void Login::resetFailedRegFields()
{
    failedRegField = static_cast<RegField>(0);
}

/* Attempts */
void Login::loginAttempt(QString username, QString password) const
{
    if(instance == nullptr)
        instance = new Login;

    try
    {
        authenticate(username, password);
    }
    catch(cm::utils::GeneralException& exception)
    {
        exception.errorWindow();
    }
}

void Login::regAttempt(QString username, QString password, QString confirmedPW) const
{
    if(instance == nullptr)
        instance = new Login;

    try
    {
        registration(username, password, confirmedPW);
    }
    catch(cm::utils::GeneralException& exception)
    {
        exception.errorWindow();
    }
}

/* Constructor */
Login::Login()
    : m_FILE_NAME("authFile.txt"), m_FILE_PATH(QDir::homePath()),
      m_FILE_ERR_MSG("Authentication failed, contact admin!")
{
    /* Initialize the authentication file */
    QFile authFile(m_FILE_PATH + m_FILE_NAME);
    authFile.open(QIODevice::NewOnly);
}

/* Authentication process */
void Login::authenticate(QString usernameInput, QString passwordInput) const
{
    QFile authFile(m_FILE_PATH + m_FILE_NAME);
    QTextStream qin(&authFile);

    if(!authFile.open(QIODevice::ReadOnly))
        throw cm::utils::BadFile(m_FILE_ERR_MSG);

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
            throw cm::utils::BadFileFormat(m_FILE_ERR_MSG);
        }
        else if(usernameFile == usernameInput && hashedPWFile == hashedPW)
        {
            type = (typeFile == "admin" ? Type::ADMIN : Type::USER);
            loginSuccessful();
            return;
        }
    }

    loginFailed();
}

/* Registration process */
void Login::registration(QString usernameInput, QString passwordInput, QString pwConfirmed) const
{
    /* Check the validity of each input field */
    int flags = 0;

    if(passwordInput != pwConfirmed)
        flags |= RegField::PW | RegField::CPW;

    if(usernameInput.isEmpty())
        flags |= RegField::UN;

    if(passwordInput.isEmpty())
        flags |= RegField::PW;

    if(pwConfirmed.isEmpty())
        flags |= RegField::CPW;

    if(flags != 0)
    {
        failedRegField = static_cast<RegField>(flags);
        return;
    }

    QFile authFile(m_FILE_PATH + m_FILE_NAME);
    QTextStream qin(&authFile);

    if(!authFile.open(QIODevice::ReadWrite))
        throw cm::utils::BadFile(m_FILE_ERR_MSG);

    QString usernameFile;
    QByteArray hashedPW = hashString(passwordInput);

    /* Search for a matching username or data error in file */
    while(!qin.atEnd())
    {
        usernameFile = qin.readLine();

        if(qin.readLine().isEmpty() || qin.readLine().isEmpty()) //Skips the next 2 lines
        {
            throw cm::utils::BadFileFormat(m_FILE_ERR_MSG);
        }
        else if(usernameInput == usernameFile)
        {
            failedRegField = RegField::UN;
            return;
        }
    }

    //Write user's credentials to the end of file
    qin << usernameInput << endl
        << hashedPW << endl
        << "user" << endl;

    regSuccessful();
}

/* Hash algorithm */
QByteArray Login::hashString(QString string) const
{
    return QCryptographicHash::hash(string.toStdString().data(), QCryptographicHash::Keccak_512).toHex();
}
}
}
