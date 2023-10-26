#include "privatedialog.h"
#include "ui_privatedialog.h"

PrivateDialog::PrivateDialog(std::shared_ptr<MYSQL_API> msq, QString login, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PrivateDialog)
{
    ui->setupUi(this);
    _msq = msq;
    _login = login;
    _userListForWiget = _msq->getUSerList();
    for(auto& user : _userListForWiget)
    {
        ui->listWidget->addItem(user);
    }
    fillBrowserWithMsgs();
}

PrivateDialog::~PrivateDialog()
{
    delete ui;
}

void PrivateDialog::fillBrowserWithMsgs()
{
    QVector<QString> messages;
    messages = _msq->getMsgList(_login.toStdString());
    int j = 0;
    QString str;
    for (int i = 0; i < messages.size(); ++i)
    {
        if (j == 0)
        {
            str += "From: " + messages[i];
            ++j;
        }
        else if (j == 1)
        {
            str += " To: " + messages[i];
            ++j;
        }
        else
        {
            str += " \"" + messages[i] + "\"" + '\n';
            j = 0;
        }
    }

    ui->msgsBrowser->setText(str);
}

void PrivateDialog::on_sendBtn_clicked()
{
    QString login_of_receiver = _msq->getLogin(ui->listWidget->currentItem()->text().toStdString());
    _msq->addMessage(_login.toStdString(), login_of_receiver.toStdString(), ui->msgLn->text().toStdString());
    ui->msgLn->clear();
    ui->msgsBrowser->clear();
    fillBrowserWithMsgs();
}

