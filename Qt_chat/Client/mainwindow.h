#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "startscreen.h"
#include "login.h"
#include "registration.h"
#include "privatedialog.h"
#include "Mysql_API.h"
#include <QMainWindow>
#include <QTcpSocket>
#include <QTime>
#include <QtWidgets>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void anotherSendToServer(QString str);
    static MainWindow* createClient();
    void createConnect();
    void test();
signals:
    void callPd();
public slots:
    void slotReadyRead();

private slots:
    void on_pushButton_2_clicked();
    void on_lineEdit_returnPressed();
    void on_startDialog_clicked();
    void on_actionOpen_another_client_triggered();

private:
    Ui::MainWindow *ui;
    QTcpSocket *socket;
    QByteArray Data;
    void SendToServer(QString str);
    QString _userName;
    quint16 nextBlockSize;

    std::unique_ptr<PrivateDialog> _pd;
    std::shared_ptr<MYSQL_API> _msq;
};
#endif // MAINWINDOW_H
