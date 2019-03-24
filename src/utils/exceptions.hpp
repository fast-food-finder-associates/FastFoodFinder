#pragma once
#include <QFile>
#include <QException>

class GeneralException : public QException
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

class BadFile : public GeneralException
{
public:
    /* Constructors */
    BadFile(QString);
    BadFile(const QFile&);
};

class BadFileFormat : public GeneralException
{
public:
    /* Constructors */
    BadFileFormat(QString);
    BadFileFormat(QString expected, QString recieved);
};
