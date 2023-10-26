#include "Mysql_API.h"

MYSQL_API::MYSQL_API()
{
    mysql_init(&_mysql);
    if (&_mysql == NULL)
    {
        qDebug() << "Error: can't creat MySQL - descriptor";
        return;
    }
    else
    {
        qDebug() << "MySQL descriptor successfully initialized";
    }
}

void MYSQL_API::connectDatabase(const std::string& host, const std::string& userName, const std::string& userPass, const std::string& dbName)
{
    if (mysql_real_connect(&_mysql, host.c_str(), userName.c_str(), userPass.c_str(), NULL, 0, NULL, 0))
    {
        _query = "SELECT SCHEMA_NAME FROM INFORMATION_SCHEMA.SCHEMATA WHERE SCHEMA_NAME = \'" + dbName + "\'";
        mysql_query(&_mysql, _query.c_str());
        _query.clear();
        _res = mysql_store_result(&_mysql);
        if (!(_row = mysql_fetch_row(_res)))
        {
            _query = "CREATE DATABASE IF NOT EXISTS " + dbName;
            mysql_query(&_mysql, _query.c_str());
            _query.clear();
            qDebug() << "Database was created";

            _query = "USE " + dbName;
            mysql_query(&_mysql, _query.c_str());
            _query.clear();

            _query = "CREATE TABLE users (login VARCHAR(20) PRIMARY KEY CHECK (login <> ''), pass VARCHAR(40), user_name VARCHAR(30) CHECK (user_name <> ''), ban_status boolean)";
            mysql_query(&_mysql, _query.c_str());
            _query.clear();
            qDebug() << "Table \'users\' was created";

            _query = "CREATE TABLE messages (id INT PRIMARY KEY AUTO_INCREMENT, login_of_sender VARCHAR(20), login_of_receiver VARCHAR(20), message TEXT(200) CHECK (message <> ''), FOREIGN KEY(login_of_sender) REFERENCES users(login), FOREIGN KEY(login_of_receiver) REFERENCES users(login))";
            mysql_query(&_mysql, _query.c_str());
            _query.clear();
            qDebug() << "Table \'messages\' was created";
        }
        else
        {
            _query = "USE " + dbName;
            mysql_query(&_mysql, _query.c_str());
            _query.clear();
            qDebug() << "Client successfully connected to database";
        }
        mysql_free_result(_res);
    }
    else
    {
        qDebug() << "Error occured";
        return;
    }
}

bool MYSQL_API::checkUser(const std::string& login, const std::string& password)
{
    _query = "SELECT login, pass FROM users WHERE login = \'" + login + "\' and pass = \'" + password + "\'";
    mysql_query(&_mysql, _query.c_str());
    _res = mysql_store_result(&_mysql);
    if (_row = mysql_fetch_row(_res))
    {
        _query.clear();
        mysql_free_result(_res);
        return true;
    }
    else
    {
        _query.clear();
        mysql_free_result(_res);
        return false;
    }
}

bool MYSQL_API::checkLoginExist(const std::string& login)
{
    _query = "SELECT login FROM users WHERE login = \'" + login + "\'";
    mysql_query(&_mysql, _query.c_str());
    _res = mysql_store_result(&_mysql);
    if (_row = mysql_fetch_row(_res))
    {
        _query.clear();
        mysql_free_result(_res);
        return true;
    }
    else
    {
        _query.clear();
        mysql_free_result(_res);
        return false;
    }
}

bool MYSQL_API::checkBanStatus(const std::string& login)
{
    _query = "SELECT ban_status FROM users WHERE login = \'" + login + "\' and ban_status = '1'";
    mysql_query(&_mysql, _query.c_str());
    _res = mysql_store_result(&_mysql);
    if (_row = mysql_fetch_row(_res))
    {
        _query.clear();
        mysql_free_result(_res);
        return true;
    }
    else
    {
        _query.clear();
        mysql_free_result(_res);
        return false;
    }
}

bool MYSQL_API::addUser(const std::string& userName, const std::string& login, const std::string& password)
{
    _query = "INSERT INTO users (login, pass, user_name, ban_status) VALUES (\'" + login + "\', \'" + password + "\', \'" + userName + "\', false)";
    if (mysql_query(&_mysql, _query.c_str()) == 0)
    {
        _query.clear();
        return true;
    }
    else
    {
        _query.clear();
        return false;
    }
}

QString MYSQL_API::getUsername(const std::string& login)
{
    _query = "SELECT user_name FROM users WHERE login = \'" + login + "\'";
    mysql_query(&_mysql, _query.c_str());
    _res = mysql_store_result(&_mysql);
    _row = mysql_fetch_row(_res);
    mysql_free_result(_res);
    return _row[0];
}

QString MYSQL_API::getLogin(const std::string& userName)
{
    _query = "SELECT login FROM users WHERE user_name = \'" + userName + "\'";
    mysql_query(&_mysql, _query.c_str());
    _res = mysql_store_result(&_mysql);
    _row = mysql_fetch_row(_res);
    mysql_free_result(_res);
    return _row[0];
}

QVector<QString> MYSQL_API::getUSerList()
{
    QVector<QString> userList;
    _query = "SELECT user_name FROM users";
    mysql_query(&_mysql, _query.c_str());
    if (_res = mysql_store_result(&_mysql))
    {
        while (_row = mysql_fetch_row(_res))
        {
            for (int j = 0; j < mysql_num_fields(_res); ++j)
            {
                userList.push_back(_row[j]);
            }
        }
    }
    else
    {
        qDebug() << "Error " << mysql_error(&_mysql);
    }
    mysql_free_result(_res);
    _query.clear();

    return userList;
}

QVector<QString> MYSQL_API::getMsgList(const std::string& login)
{
    QVector<QString> msgList;
    _query = "SELECT login_of_sender, login_of_receiver, message FROM messages WHERE login_of_sender = \'" + login + "\' OR login_of_receiver = \'" + login + "\'";
    mysql_query(&_mysql, _query.c_str());
    if (_res = mysql_store_result(&_mysql))
    {
        while (_row = mysql_fetch_row(_res))
        {
            for (int j = 0; j < mysql_num_fields(_res); ++j)
            {
                msgList.push_back(_row[j]);
            }
        }
    }
    else
    {
        qDebug() << "Error " << mysql_error(&_mysql);
    }
    mysql_free_result(_res);
    _query.clear();

    return msgList;
}

void MYSQL_API::addMessage(const std::string& login, const std::string& receiverLogin, const std::string& message)
{
    _query = "INSERT INTO messages (login_of_sender, login_of_receiver, message) VALUES (\'" + login + "\', \'" + receiverLogin + "\', \'" + message + "\')";
    mysql_query(&_mysql, _query.c_str());
    _query.clear();
}
