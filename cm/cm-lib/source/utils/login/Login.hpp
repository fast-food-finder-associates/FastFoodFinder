#pragma once
#include <QObject>
#include <QString>
#include <QByteArray>
#include <cm-lib_global.h>

namespace cm
{
namespace utils
{
class Login : public QObject
{
    Q_OBJECT

public:
    enum class Type{USER, ADMIN};
    enum RegField{UN = 0b1, PW = 0b10, CPW = 0b100};

    /* Type */
    static Type getType();
    static RegField getFailedRegFields();

public slots:
    /* Attempts */
    void loginAttempt(QString username, QString password) const;
    void regAttempt(QString username, QString password, QString confirmedPW) const;

signals:
    /* Login signal */
    void loginSuccessful() const;
    void loginFailed() const;

    /* Registration signal */
    void regSuccessful() const;
    void regFailed() const;

private:
	/* Constructor */
    Login();

    /* Destructor */
    ~Login(){}

    /* Authentication process */
    void authenticate(QString username, QString password) const;

    /* Registration process */
    void registration(QString username, QString password, QString pwConfirmed) const;

    /* Hash algorithm */
    QByteArray hashString(QString string) const;

    /* Static data */
    static Type type;
    static Login* instance;
    static RegField failedRegField;

    /* Data members */
    const QString m_FILE_NAME;
    const QString m_FILE_PATH;
    const QString m_FILE_ERR_MSG;
};
}
}
