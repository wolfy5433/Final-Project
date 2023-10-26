#include "registration.h"
#include "ui_registration.h"

Registration::Registration(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Registration)
{
    ui->setupUi(this);
}

Registration::~Registration()
{
    delete ui;
}

void Registration::setDatabase(std::shared_ptr<MYSQL_API> msq)
{
    _msq = msq;
}

void Registration::on_createAccBtn_clicked()
{
    QMessageBox qbox;
    if(_msq->checkLoginExist(ui->loginLn->text().toStdString()) == true)
    {
        QMessageBox::critical(this, tr("Error"), tr("Login is exists. Enter another login"));
        return;
    }
    else
    {
        _msq->addUser(ui->nameLn->text().toStdString(), ui->loginLn->text().toStdString(), ui->passLn->text().toStdString());
        qbox.setText("The account has been created.");
        qbox.exec();
        ui->nameLn->clear();
        ui->loginLn->clear();
        ui->passLn->clear();
        return;
    }
}


void Registration::on_backBtn_clicked()
{
    emit logSignal();
}

