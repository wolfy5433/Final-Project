#include <QApplication>
#include "server.h"
#include "mainwindow.h"

constexpr const char* db_host = "127.0.0.1";
constexpr const char* db_user = "root";
constexpr const char* db_pass = "pass";
constexpr const char* db_name = "chat";

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
