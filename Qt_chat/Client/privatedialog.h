#ifndef PRIVATEDIALOG_H
#define PRIVATEDIALOG_H

#include <QDialog>
#include <QListWidget>
#include <memory>
#include "Mysql_API.h"

namespace Ui {
class PrivateDialog;
}

class PrivateDialog : public QDialog
{
    Q_OBJECT

public:
    explicit PrivateDialog(std::shared_ptr<MYSQL_API> msq, QString login, QWidget *parent = nullptr);
    ~PrivateDialog();
    void fillBrowserWithMsgs();

private slots:
    void on_sendBtn_clicked();

private:
    Ui::PrivateDialog *ui;
    QVector<QString> _userListForWiget;
    QString _login;
    std::shared_ptr<MYSQL_API> _msq;
};

#endif // PRIVATEDIALOG_H
