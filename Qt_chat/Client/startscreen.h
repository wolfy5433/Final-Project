#ifndef STARTSCREEN_H
#define STARTSCREEN_H

#include "mainwindow.h"
#include "login.h"
#include "registration.h"
#include "Mysql_API.h"
#include <QDialog>
#include <memory>

namespace Ui {
class StartScreen;
}

class StartScreen : public QDialog
{
    Q_OBJECT

public:
    explicit StartScreen(std::shared_ptr<MYSQL_API> msq, QWidget *parent = nullptr);
    ~StartScreen();

    void setLoginForm();
    void setRegForm();
    void onLogBtn(QString userName, QString login);
    QString getUserName() const;
    QString getLogin() const;

private:
    Ui::StartScreen *ui;
    QString _userName;
    QString _login;
    std::shared_ptr<MYSQL_API> _msq;
};

#endif // STARTSCREEN_H
