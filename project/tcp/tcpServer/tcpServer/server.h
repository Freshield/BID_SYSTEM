#ifndef SERVER_H
#define SERVER_H

#include <QDialog>
//#include <QAbstractSocket>
#include <QTcpServer>
#include <QList>
#include <QtNetwork>
#include <QStringList>
#include "clientjobs.h"
#include "items.h"
#include <QFile>

class QTcpServer;

//---------------UID-----------------------//
struct UID
{
    QString name;
    QString number;
    QTcpSocket *sockets_value;
    QString registed;
    QString strIPandPort;

};


//---------------/UID-----------------------//


namespace Ui {
    class Server;
}

class Server : public QDialog
{
    Q_OBJECT

public:
    explicit Server(QWidget *parent = 0);
    ~Server();

private:
    Ui::Server *ui;
    //server private member

    QTcpServer *m_server;//the server itself
    QList<clientjobs*> m_ClientList;//client class to save socket
    QStringList m_IPandPortList;//IPPort list
    int UID_NUM;
    int ITEM_NUM;
    QList<UID> uidlist;//
    QList<items*> itemlist;

    QByteArray pickup_data(QString data);
    void send_to_client(QTcpSocket *socket, QString data);

private slots:
    //response the slot
    void on_pushButton_clicked();//send the message
    void readMessage(QString strIPandPort,QString data);//read slot
    void itemtimeout(QString itemcode);

    void onNewConnection();//new connect
    void DeleteOneClient(QString strIPandPort);//delete client
    void on_setButton_clicked();//set the port num
    void on_send_all_pushButton_clicked();

};

#endif // SERVER_H
