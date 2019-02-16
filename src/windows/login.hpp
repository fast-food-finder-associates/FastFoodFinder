#pragma once
#include <QDialog>
#include <QByteArray>

namespace Ui
{
class Login;
}

class Login : public QDialog
{
    Q_OBJECT

public:
    enum class Type{GUEST, USER, ADMIN};

    /* Login usage */
    static Login* requestLogin();
    static Type getType();

private slots:
    /* Login page */
    void on_pushButton_userLogin_clicked();
    void on_pushButton_guestLogin_clicked();
    void on_pushButton_register_clicked();
    void on_checkBox_showPW_stateChanged(int);

    /* Registration page */
    void on_pushButton_confirmReg_clicked();
    void on_pushButton_cancelReg_clicked();
    void on_checkBox_showPWReg_stateChanged(int);

private:
    enum RegField{UN = 1, PW = 2, CPW = 4}; //Each value gets its own bit

    Login();

    /* Deleted members */
    Login(const Login&) = delete;
    void operator=(const Login&) = delete;

    /* Authentication handling */
    void authenticate(QString username, QString password) const;
    void authSuccessful() const;
    void authFailed() const;

    /* Registration handling */
    void registration(QString username, QString password, QString pwConfirmed) const;
    void regSuccessful() const;
    void regFailed(RegField) const;

    /* Hash algorithm */
    QByteArray hashString(QString string) const;

    /* Ui */
    void resetUi() const;
    void clearFields() const;

    /* Data members */
    Ui::Login* m_ui;
    static Type type;
    static Login* instance;
    static const QString FILE_NAME;
    const QString FILE_ERR_MSG;
};
