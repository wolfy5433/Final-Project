#include "banusers.h"
#include "ui_banusers.h"

BanUsers::BanUsers(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BanUsers)
{
    ui->setupUi(this);
}

BanUsers::~BanUsers()
{
    delete ui;
}

void BanUsers::test(QVector<QString> vec)
{
    int j = 0;
    QString str;
    for (int i = 0; i < vec.size(); ++i)
    {
        if (j % 2 == 0)
        {
            str +=  "----\n- User's name: " + vec[i] + '\n';
            ++j;
        }
        else
        {
            str += "- Login: " + vec[i] + '\n';
            ++j;
        }
    }

    ui->listOfBannedUsrs->setText(str);
    vec.clear();
}

void BanUsers::on_unbanBtn_clicked()
{
    QMessageBox qbox;
    emit unbanUsr(ui->unBanLn->text().toStdString());
    ui->unBanLn->clear();
    qbox.setText("The user has been unbanned.");
    qbox.exec();
}

