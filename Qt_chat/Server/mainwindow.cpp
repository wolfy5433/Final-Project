#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    form = new FormUsers;
    busers = new BanUsers;
    connect(form, &FormUsers::banUsr, this, &MainWindow::banUserMW);
    connect(busers, &BanUsers::unbanUsr, this, &MainWindow::unbanUserMW);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_connect_clicked()
{
    s = new Server;
}


void MainWindow::on_conn_db_clicked()
{
    s->connectDatabase(db_host, db_user, db_pass, db_name);
}


void MainWindow::on_showAllUsers_clicked()
{
    form->show();
    connect(this, &MainWindow::vector, form, &FormUsers::test);
    s->showAllUsers();
    for(int i = 0; i < s->vectorQuery.size(); ++i)
    {
        vec.push_back(s->vectorQuery[i]);
    }
    s->vectorQuery.clear();
    emit vector(vec);
    vec.clear();
}

void MainWindow::banUserMW(const std::string& login)
{
    s->banUser(login);
}

void MainWindow::unbanUserMW(const std::string& login)
{
    s->unbanUser(login);
}

void MainWindow::on_showBanUsers_clicked()
{
    busers->show();
    connect(this, &MainWindow::bvector, busers, &BanUsers::test);
    s->showBanUsers();
    for(int i = 0; i < s->vectorQuery.size(); ++i)
    {
        vec.push_back(s->vectorQuery[i]);
    }
    s->vectorQuery.clear();
    emit bvector(vec);
    vec.clear();
}


void MainWindow::on_closeServer_clicked()
{
    this->close();
}

