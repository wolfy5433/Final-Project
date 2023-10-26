#ifndef LOGIN_H
#define LOGIN_H

#include "mainwindow.h"
#include "Mysql_API.h"
#include <QWidget>
#include <QMessageBox>
#include <memory>

namespace Ui {
class Login;
}

class Login : public QWidget
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = nullptr);
    ~Login();

    void setDatabase(std::shared_ptr<MYSQL_API> msq);
signals:
    void regSignal();
    void lgnBtn(QString userName, QString login);

private slots:
    void on_regBtn_clicked();
    void on_loginBtn_clicked();

private:
    Ui::Login *ui;
    std::shared_ptr<MYSQL_API> _msq;
};

#endif // LOGIN_H
