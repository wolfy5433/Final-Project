#ifndef REGISTRATION_H
#define REGISTRATION_H

#include "mainwindow.h"
#include "Mysql_API.h"
#include <QWidget>
#include <memory>

namespace Ui {
class Registration;
}

class Registration : public QWidget
{
    Q_OBJECT

public:
    explicit Registration(QWidget *parent = nullptr);
    ~Registration();

    void setDatabase(std::shared_ptr<MYSQL_API> msq);

signals:
    void logSignal();

private slots:
    void on_createAccBtn_clicked();
    void on_backBtn_clicked();

private:
    Ui::Registration *ui;
    std::shared_ptr<MYSQL_API> _msq;
};

#endif // REGISTRATION_H
