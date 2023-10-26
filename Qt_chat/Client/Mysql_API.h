#ifndef MYSQL_API_H
#define MYSQL_API_H
#include "mysql.h"
#include <string>
#include <QDebug>
#include <QVector>

class MYSQL_API
{
    //Q_OBJECT

public:
    MYSQL_API();
    void connectDatabase(const std::string& host, const std::string& userName, const std::string& userPass, const std::string& dbName);
    bool checkUser(const std::string& login, const std::string& password);
    bool checkLoginExist(const std::string& login);
    bool checkBanStatus(const std::string& login);
    bool addUser(const std::string& userName, const std::string& login, const std::string& password);
    QString getUsername(const std::string& login);
    QString getLogin(const std::string& userName);
    QVector<QString> getUSerList();
    QVector<QString> getMsgList(const std::string& login);
    void addMessage(const std::string& login, const std::string& receiverLogin, const std::string& message);

private:
    MYSQL _mysql;
    MYSQL_RES* _res;
    MYSQL_ROW _row;
    std::string _query;
};
#endif // MYSQL_API_H
