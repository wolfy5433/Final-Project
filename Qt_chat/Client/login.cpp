#include "login.h"
#include "ui_login.h"

Login::Login(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);
}

Login::~Login()
{
    delete ui;
}

void Login::setDatabase(std::shared_ptr<MYSQL_API> msq)
{
    _msq = msq;
}

void Login::on_regBtn_clicked()
{
    emit regSignal();
}


void Login::on_loginBtn_clicked()
{
    if(_msq->checkUser(ui->loginLn->text().toStdString(), ui->passLn->text().toStdString()) == false)
    {
        QMessageBox::critical(this, tr("Error"), tr("Login or password is wrong"));
        return;
    }
    else if(_msq->checkBanStatus(ui->loginLn->text().toStdString()) == true)
    {
        QMessageBox::critical(this, tr("Error"), tr("You are in ban list."));
        return;
    }
    emit lgnBtn(_msq->getUsername(ui->loginLn->text().toStdString()), ui->loginLn->text());
}

