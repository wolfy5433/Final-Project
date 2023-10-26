#include "formusers.h"
#include "ui_formusers.h"

FormUsers::FormUsers(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormUsers)
{
    ui->setupUi(this);
}

FormUsers::~FormUsers()
{
    delete ui;
}

void FormUsers::test(QVector<QString> vec)
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

    ui->textWithUsrs->setText(str);
    vec.clear();
}



void FormUsers::on_banBtn_clicked()
{
    QMessageBox qbox;
    emit banUsr(ui->banLn->text().toStdString());
    ui->banLn->clear();
    qbox.setText("The user has been banned.");
    qbox.exec();
}

