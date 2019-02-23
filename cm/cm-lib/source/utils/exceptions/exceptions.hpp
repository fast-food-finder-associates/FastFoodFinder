#pragma once
#include <QFile>
#include <QException>
#include <cm-lib_global.h>

namespace cm
{
namespace utils
{
class CMLIBSHARED_EXPORT GeneralException : public QException
{
public:
    /* Constructors */
    GeneralException();
    GeneralException(QString);

    /* Error message handlers */
    void errorWindow() const;
    QString errorMessage() const;

    /* QException overrides */
    void raise() const override;
    GeneralException* clone() const override;

protected:
    QString message;
};

class CMLIBSHARED_EXPORT BadFile : public GeneralException
{
public:
    BadFile(QString);
    BadFile(const QFile&);
};

class CMLIBSHARED_EXPORT BadFileFormat : public GeneralException
{
public:
    BadFileFormat(QString);
    BadFileFormat(QString expected, QString recieved);
};
}
}
