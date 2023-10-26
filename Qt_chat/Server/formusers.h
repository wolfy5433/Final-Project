#ifndef FORMUSERS_H
#define FORMUSERS_H

#include <QWidget>
#include <QMessageBox>
#include <string>

namespace Ui {
class FormUsers;
}

class FormUsers : public QWidget
{
    Q_OBJECT

public:
    explicit FormUsers(QWidget *parent = nullptr);
    ~FormUsers();
public slots:
    void test(QVector<QString> vec);
private slots:
    void on_banBtn_clicked();
signals:
    void banUsr(std::string);

private:
    Ui::FormUsers *ui;
};

#endif // FORMUSERS_H
