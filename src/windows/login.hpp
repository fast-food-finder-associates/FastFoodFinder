#pragma once
#include <QDialog>

namespace Ui
{
class Login;
}

class Login : public QDialog
{
    Q_OBJECT

public:
    enum class Type{GUEST, USER, ADMIN};

    /* Singleton access */
    static Login* getInstance();

    /* Login usage */
    static void requestLogin();
    static Type getType();

private slots:
    void on_pushButton_registered_clicked();
    void on_pushButton_guest_clicked();
    void on_checkBox_showPW_stateChanged(int);

private:
    Login();

    /* Deleted members */
    Login(const Login&) = delete;
    void operator=(const Login&) = delete;

    /* Authentication handling */
    bool authenticate(QString username, QString password) const;
    void authSuccessful() const;
    void authFailed() const;

    /* Ui */
    void resetUi();

    /* Data members */
    Ui::Login* m_ui;
    static Type m_type;
    static Login* m_instance;
};
