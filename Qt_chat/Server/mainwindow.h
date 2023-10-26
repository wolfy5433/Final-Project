#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDialog>
#include <QVBoxLayout>
#include <QDialogButtonBox>
#include <QListWidget>
#include "server.h"
#include "formusers.h"
#include "banusers.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void banUserMW(const std::string& login);
    void unbanUserMW(const std::string& login);

private slots:
    void on_connect_clicked();
    void on_conn_db_clicked();
    void on_showAllUsers_clicked();
    void on_showBanUsers_clicked();
    void on_closeServer_clicked();

signals:
    void vector(QVector<QString>);
    void bvector(QVector<QString>);

private:
    Ui::MainWindow *ui;
    Server *s;
    FormUsers *form;
    BanUsers *busers;
    QVector<QString> vec;

    const char* db_host = "127.0.0.1";
    const char* db_user = "root";
    const char* db_pass = "pass";
    const char* db_name = "chat";
};

#endif // MAINWINDOW_H
