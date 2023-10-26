#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    socket = new QTcpSocket(this);
    connect(socket, &QTcpSocket::readyRead, this, &MainWindow::slotReadyRead);
    connect(socket, &QTcpSocket::disconnected, socket, &QTcpSocket::deleteLater);
    nextBlockSize = 0;    
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::createConnect()
{
    socket->connectToHost("127.0.0.1", 2323);
}

void MainWindow::test()
{
    _pd->show();
}

MainWindow *MainWindow::createClient()
{
    const char* db_host = "127.0.0.1";
    const char* db_user = "root";
    const char* db_pass = "pass";
    const char* db_name = "chat";

    MainWindow* w = new MainWindow();

    w->createConnect();
    w->_msq = std::make_shared<MYSQL_API>();
    w->_msq->connectDatabase(db_host, db_user, db_pass, db_name);
    w->setAttribute(Qt::WA_DeleteOnClose);

    StartScreen s(w->_msq);
    if(s.exec() == QDialog::Rejected)
    {
        return nullptr;
    }
    w->_userName = s.getUserName();
    w->_pd = std::make_unique<PrivateDialog>(w->_msq, s.getLogin());
    connect(w, &MainWindow::callPd, w, &MainWindow::test);
    return w;
}

void MainWindow::SendToServer(QString str)
{
    Data.clear();
    QDataStream out(&Data, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_5);
    out << quint16(0) << QTime::currentTime() << str;
    out.device()->seek(0);
    out << quint16(Data.size() - sizeof(quint16));
    socket->write(Data);
    ui->lineEdit->clear();
}

void MainWindow::slotReadyRead()
{
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
            ui->textBrowser->append(time.toString() + " " + str);
        }
    }
    else
    {
        ui->textBrowser->append("read error");
    }
}


void MainWindow::on_pushButton_2_clicked()
{
    QString str = "(" + _userName + ")" + " " + ui->lineEdit->text();
    SendToServer(str);
}


void MainWindow::on_lineEdit_returnPressed()
{
    QString str = "(" + _userName + ")" + " " + ui->lineEdit->text();
    SendToServer(str);
}

void MainWindow::on_startDialog_clicked()
{
    emit callPd();
}


void MainWindow::on_actionOpen_another_client_triggered()
{
    auto w = createClient();
    if(w)
    {
        w->show();
    }
}

