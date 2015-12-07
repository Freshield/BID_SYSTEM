#ifndef CLIENT_H
#define CLIENT_H

#include <QDialog>

#include <QAbstractSocket>

class QTcpSocket;



namespace Ui {
    class Client;
}

class Client : public QDialog
{
    Q_OBJECT

public:
    explicit Client(QWidget *parent = 0);
    ~Client();

private:
    Ui::Client *ui;
    QTcpSocket *tcpSocket;
    QString message;
    quint16 blockSize;
    QString uidnum;
    QString name;
    QString format_message(QString header,QString data);
    QByteArray pickup_data(QString data);

private slots:
    void newConnect();
    void readMessage();
    void displayError(QAbstractSocket::SocketError);
    void on_connectButton_clicked();
    void on_pushButton_clicked();
    void ifconnected();
    void submititems(QString itemname);
    void getbiditem(QString itemscode,QString itemprice);
    void withdrawiteminfo(QString itemscode);
    void serverdisconnect();



    void on_regist_pushButton_clicked();
    void on_see_all_bid_pushButton_clicked();
    void on_submit_pushButton_clicked();
    void on_bid_pushButton_clicked();

    void on_see_all_your_bid_pushButton_clicked();

    void on_withdraw_pushButton_clicked();

    void on_see_all_your_item_pushButton_clicked();



    void on_deregist_pushButton_clicked();

signals:
    void allbidinfo(QString data);
};

#endif // CLIENT_H
