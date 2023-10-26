#include "server.h"

Server::Server()
{
    if(this->listen(QHostAddress::Any, 2323))
    {
        qDebug() << "Server successfully started";
    }
    else
    {
        qDebug() << "Error occuried";
    }
    nextBlockSize = 0;
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

Server::~Server()
{
    mysql_close(&_mysql);
}


void Server::incomingConnection(qintptr socketDescriptor)
{
    socket = new QTcpSocket;
    socket->setSocketDescriptor(socketDescriptor);
    connect(socket, &QTcpSocket::readyRead, this, &Server::slotReadyRead);
    connect(socket, &QTcpSocket::disconnected, socket, &QTcpSocket::deleteLater);

    Sockets.push_back(socket);
    qDebug() << "client connected" << socketDescriptor;

}

void Server::slotReadyRead()
{
    socket = (QTcpSocket*)sender();
    QDataStream in(socket);
    in.setVersion(QDataStream::Qt_6_5);
    if(in.status() == QDataStream::Ok)
    {
        for(;;)
        {
            if(nextBlockSize == 0)
            {
                if(socket->bytesAvailable() < 2)
                {
                    break;
                }
                in >> nextBlockSize;
            }
            if(socket->bytesAvailable() < nextBlockSize)
            {
                break;
            }

            QString str;
            QTime time;
            in >> time >> str;
            nextBlockSize = 0;
            SendToClient(str);
            break;
        }
    }
    else
    {
        qDebug() << "DataStream error";
    }
}

void Server::connectDatabase(const std::string& host, const std::string& userName, const std::string& userPass, const std::string& dbName)
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
            qDebug() << "Server successfully connected to database";
        }
        mysql_free_result(_res);
    }
    else
    {
        qDebug() << "Error occured";
        return;
    }
}

bool Server::checkUser(const std::string& login, const std::string& password)
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

void Server::showAllUsers()
{
    std::string query = "SELECT user_name, login FROM users";
    mysql_query(&_mysql, query.c_str());
    if (_res = mysql_store_result(&_mysql))
    {
        while (_row = mysql_fetch_row(_res))
        {
            for (int j = 0; j < mysql_num_fields(_res); ++j)
            {
                vectorQuery.push_back(_row[j]);
            }
        }
    }
    else
    {
        qDebug() << "Error " << mysql_error(&_mysql);
    }
    mysql_free_result(_res);
}

void Server::banUser(const std::string& login)
{
    _query = "UPDATE users SET ban_status = '1' WHERE login = \'" + login + "\'";
    mysql_query(&_mysql, _query.c_str());
    _query.clear();
}

void Server::showBanUsers()
{
    _query = "SELECT user_name, login FROM users WHERE ban_status = '1'";
    mysql_query(&_mysql, _query.c_str());
    if (_res = mysql_store_result(&_mysql))
    {
        while (_row = mysql_fetch_row(_res))
        {
            for (int j = 0; j < mysql_num_fields(_res); ++j)
            {
                vectorQuery.push_back(_row[j]);
            }
        }
    }
    else
    {
        qDebug() << "Error " << mysql_error(&_mysql);
    }
    mysql_free_result(_res);
    _query.clear();
}

void Server::unbanUser(const std::string& login)
{
    _query = "UPDATE users SET ban_status = '0' WHERE login = \'" + login + "\'";
    mysql_query(&_mysql, _query.c_str());
    _query.clear();
}

void Server::SendToClient(QString str)
{
    Data.clear();
    QDataStream out(&Data, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_5);
    out << quint16(0) << QTime::currentTime() << str;
    out.device()->seek(0);
    out << quint16(Data.size() - sizeof(quint16));

    for(int i = 0; i < Sockets.size(); ++i)
    {
        Sockets[i]->write(Data);
    }
}
