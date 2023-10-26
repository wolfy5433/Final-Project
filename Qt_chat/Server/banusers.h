#ifndef BANUSERS_H
#define BANUSERS_H

#include <QWidget>
#include <QMessageBox>
#include <string>

namespace Ui {
class BanUsers;
}

class BanUsers : public QWidget
{
    Q_OBJECT

public:
    explicit BanUsers(QWidget *parent = nullptr);
    ~BanUsers();
public slots:
    void test(QVector<QString> vec);

private slots:
    void on_unbanBtn_clicked();
signals:
    void unbanUsr(std::string);
private:
    Ui::BanUsers *ui;
};

#endif // BANUSERS_H
