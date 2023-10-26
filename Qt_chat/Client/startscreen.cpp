#include "startscreen.h"
#include "ui_startscreen.h"

StartScreen::StartScreen(std::shared_ptr<MYSQL_API> msq, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::StartScreen)
{
    ui->setupUi(this);
    _msq = msq;
    ui->loginPage->setDatabase(_msq);
    ui->regPage->setDatabase(_msq);
    connect(ui->loginPage, &Login::regSignal, this, &StartScreen::setRegForm);
    connect(ui->loginPage, &Login::lgnBtn, this, &StartScreen::onLogBtn);
    connect(ui->regPage, &Registration::logSignal, this, &StartScreen::setLoginForm);
}

StartScreen::~StartScreen()
{
    delete ui;
}

void StartScreen::onLogBtn(QString userName, QString login)
{
    _userName = userName;
    _login = login;
    accept();
}

QString StartScreen::getUserName() const
{
    return _userName;
}

QString StartScreen::getLogin() const
{
    return _login;
}

void StartScreen::setLoginForm()
{
    ui->lgnAndRegForms->setCurrentIndex(0);
}

void StartScreen::setRegForm()
{
    ui->lgnAndRegForms->setCurrentIndex(1);
}
