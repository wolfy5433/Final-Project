#ifndef SERVER_H
#define SERVER_H
#include "mysql.h"
#include <QTcpServer>
#include <QTcpSocket>
#include <QVector>
#include <QTime>

class Server : public QTcpServer
{
    Q_OBJECT
public:
    Server();
    ~Server();
    QVector<QString> vectorQuery;

public slots:
    void incomingConnection(qintptr socketDescriptor);
    void slotReadyRead();
    void connectDatabase(const std::string& host, const std::string& userName, const std::string& userPass, const std::string& dbName);
    bool checkUser(const std::string& login, const std::string& password);
    void showAllUsers();
    void banUser(const std::string& login);
    void showBanUsers();
    void unbanUser(const std::string& login);

private:
    QTcpSocket *socket;
    QVector<QTcpSocket*> Sockets;
    QByteArray Data;
    void SendToClient(QString str);
    quint16 nextBlockSize;

    QString login;
    QString pass;


    MYSQL _mysql;
    MYSQL_RES* _res;
    MYSQL_ROW _row;
    std::string _query;
};

#endif // SERVER_H
