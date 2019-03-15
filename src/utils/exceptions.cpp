#include "exceptions.hpp"
#include <QMessageBox>
#include <QIcon>

namespace fff
{
/* Constructors */
GeneralException::GeneralException()
{}

GeneralException::GeneralException(QString m)
                : message(m)
{}

void GeneralException::errorWindow() const
{
    QMessageBox error(QMessageBox::Critical, "Error", message);
    error.setWindowIcon(QIcon(":/res/fff128.png"));
    error.exec();
}

QString GeneralException::errorMessage() const
{
    return message;
}

void GeneralException::raise() const
{
    throw *this;
}

GeneralException* GeneralException::clone() const
{
    return new GeneralException(*this);
}

/* Constructors */
BadFile::BadFile(QString m)
       : GeneralException(m)
{}

BadFile::BadFile(const QFile& file)
{
    message = "Failed to use file!\r\n\r\n" + file.fileName();
}

/* Constructors */
BadFileFormat::BadFileFormat(QString m)
             : GeneralException(m)
{}

BadFileFormat::BadFileFormat(QString expected, QString recieved)
{
    message = "Expected: "   + expected + "\r\n\r\n" +
              "Recieved: \"" + recieved + "\"";
}
}
