#include "client.h"
#include "ui_client.h"

#include <QtNetwork>
#include <QMessageBox>
#include "submitdialog.h"
#include "seeallbiddialog.h"
#include "biditemdialog.h"
#include "withdrawitemdialog.h"

Client::Client(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Client)
{
    ui->setupUi(this);
    ui->portLineEdit->setValidator(new QIntValidator(0, 65535, this));
    /*
    tcpSocket = new QTcpSocket(this);
    uidnum = "NULL";
    connect(tcpSocket,SIGNAL(readyRead()),this,SLOT(readMessage()));
    connect(tcpSocket,SIGNAL(error(QAbstractSocket::SocketError)),this,SLOT(displayError(QAbstractSocket::SocketError)));

    connect(tcpSocket,SIGNAL(connected()),this,SLOT(ifconnected()));
    */
}

Client::~Client()
{
    delete ui;
}

void Client::newConnect()
{
    blockSize = 0;
    tcpSocket = new QTcpSocket(this);
    uidnum = "NULL";
    connect(tcpSocket,SIGNAL(readyRead()),this,SLOT(readMessage()));
    connect(tcpSocket,SIGNAL(error(QAbstractSocket::SocketError)),this,SLOT(displayError(QAbstractSocket::SocketError)));

    connect(tcpSocket,SIGNAL(connected()),this,SLOT(ifconnected()));

    tcpSocket->abort();
    tcpSocket->connectToHost(ui->hostLineEdit->text(),ui->portLineEdit->text().toInt());
    connect(tcpSocket,SIGNAL(disconnected()),this,SLOT(serverdisconnect()));

}

void Client::readMessage()
{
    QDataStream in(tcpSocket);
    in.setVersion(QDataStream::Qt_4_0);

    if(blockSize == 0)
    {
        if(tcpSocket->bytesAvailable() < (int)sizeof(quint16))
        {
            return;
        }
        in >> blockSize;
    }

    if(tcpSocket->bytesAvailable() < blockSize)
    {
        return;
    }

    in >> message;

    //--------------------------------------------------------------//
    //----------------FIGURE OUT THE MESSAGE------------------------//
    //--------------------------------------------------------------//
    //first connect
    if(message[0] == '0' && message[1] == '-')
    {
        int place = message.indexOf("<uidnum>");
        QString getter = message.mid(place+8,message.size()-place-8);
        uidnum = getter;
        ui->uidnum_label->setText(getter);
    }
    else if(message == tr("SERVER SEND:YOUR REGISTED SUCCESS"))
    {
        name = ui->sendLineEdit->text();
        ui->sendLineEdit->setText("");
        ui->sendLineEdit->setEnabled(false);
        ui->regist_pushButton->setEnabled(false);
        ui->bid_pushButton->setEnabled(true);
        ui->see_all_bid_pushButton->setEnabled(true);
        ui->see_all_your_bid_pushButton->setEnabled(true);
        ui->submit_pushButton->setEnabled(true);
        ui->deregist_pushButton->setEnabled(true);
        ui->withdraw_pushButton->setEnabled(true);
        ui->see_all_your_item_pushButton->setEnabled(true);
        ui->namelabel->setText(name);

        ui->messageLabel->setText(message+tr("\n")+tr("Now you can try to play the game"));

    }
    //see all bid
    else if(message.contains("SERVER SEND:ALL BID IS BELOW\n"))
    {
        SeeAllBidDialog *newseeallbid = new SeeAllBidDialog(this,message);
        newseeallbid->show();
        ui->messageLabel->setText("SERVER SEND:ALL BID IS BELOW");

    }
    //want a bid
    else if(message.contains("SERVER SEND:ALL ITEM YOU CAN BID IS BELOW\n"))
    {
        BidItemDialog *newbiditem = new BidItemDialog(this,message,uidnum);
        connect(newbiditem,SIGNAL(biditemsinfo(QString,QString)),this,SLOT(getbiditem(QString,QString)),Qt::QueuedConnection);
        newbiditem->show();
        ui->messageLabel->setText("SERVER SEND:GET BID ITEM");
    }
    //see client's bid
    else if(message.contains("SERVER SEND:ALL ITEM YOUR BID IS BELOW\n"))
    {
        SeeAllBidDialog *newseeallbid = new SeeAllBidDialog(this,message);
        newseeallbid->show();
        ui->messageLabel->setText("SERVER SEND:ALL BID IS BELOW");

    }
    //see client's item
    else if(message.contains("SERVER SEND:ALL ITEM BELONG TO YOU IS BELOW\n"))
    {
        SeeAllBidDialog *newseeallbid = new SeeAllBidDialog(this,message);
        newseeallbid->show();
        ui->messageLabel->setText("SERVER SEND:ALL ITEM IS BELOW");

    }
    //withdraw client's item
    else if(message.contains("SERVER SEND:ALL YOUR ITEM IS BELOW\n"))
    {
        WithdrawItemDialog *newwithdrawitem = new WithdrawItemDialog(this,message,uidnum);
        connect(newwithdrawitem,SIGNAL(biditemsinfo(QString)),this,SLOT(withdrawiteminfo(QString)));
        newwithdrawitem->show();
        ui->messageLabel->setText("SERVER SEND:ALL ITEM BELONG TO YOU IS BELOW\n");

    }
    //deregist
    else if(message.contains("SERVER SEND:YOUR DEREGIST SUCCESS"))
    {
        name = "";
        uidnum = "NULL";
        ui->sendLineEdit->setText("");
        ui->uidnum_label->setText("");
        ui->namelabel->setText("");
        ui->sendLineEdit->setEnabled(false);
        ui->regist_pushButton->setEnabled(false);
        ui->bid_pushButton->setEnabled(false);
        ui->see_all_bid_pushButton->setEnabled(false);
        ui->see_all_your_bid_pushButton->setEnabled(false);
        ui->submit_pushButton->setEnabled(false);
        ui->deregist_pushButton->setEnabled(false);
        ui->withdraw_pushButton->setEnabled(false);
        ui->see_all_your_item_pushButton->setEnabled(false);
        ui->connectButton->setEnabled(true);
        ui->hostLineEdit->setEnabled(true);
        ui->portLineEdit->setEnabled(true);
        ui->messageLabel->setText("SERVER SEND:YOUR DEREGIST SUCCESS\n");

    }
    //someone bid client's item
    else if(message.contains("SERVER SEND:YOUR ITEM HAVE BID"))
    {
        QString iteminfo = tr("The bid item infomation is below\n")+message.mid(message.indexOf("\n")+1,message.size()-message.indexOf("\n")-1);

        ui->messageLabel->setText("SERVER SEND:YOUR ITEM HAVE BID\n");
        QMessageBox::information(this,tr("Bid have"),iteminfo);

    }
    //one item sale success
    else if(message.contains("TRADE SUCCESS\n"))
    {
        QString iteminfo = tr("The item infomation is below\n")+message.mid(message.indexOf("\n")+1,message.size()-message.indexOf("\n")-1);

        ui->messageLabel->setText("SERVER SEND:YOUR ITEM TRADE SUCCESS\n");
        QMessageBox::information(this,tr("Trade success"),iteminfo);
    }
    //one item bid success
    else if(message.contains("BID SUCCESS\n"))
    {
        QString iteminfo = tr("The item infomation is below\n")+message.mid(message.indexOf("\n")+1,message.size()-message.indexOf("\n")-1);

        ui->messageLabel->setText("SERVER SEND:YOUR ITEM BID SUCCESS\n");
        QMessageBox::information(this,tr("Bid success"),iteminfo);
    }
    //one item buyer is you but canceled cause owner shutdown
    else if(message.contains("WAS CANCELLED CAUSE THE CLIENT SHUTDOWN\n"))
    {
        QString iteminfo = tr("The item infomation is below\n")+message.mid(message.indexOf("\n")+1,message.size()-message.indexOf("\n")-1);

        ui->messageLabel->setText("SERVER SEND:YOUR BID WAS CANCELLED CAUSE THE CLIENT SHUTDOWN\n");
        QMessageBox::warning(this,tr("Item cancelled"),iteminfo);
    }
    //one item owner is you but refresh cause buyer shutdown
    else if(message.contains("WAS REFRESH CAUSE THE BUYER SHUTDOWN\n"))
    {
        QString iteminfo = tr("The item infomation is below\n")+message.mid(message.indexOf("\n")+1,message.size()-message.indexOf("\n")-1);

        ui->messageLabel->setText("SERVER SEND:YOUR ITEM WAS REFRESH CAUSE THE BUYER SHUTDOWN\n");
        QMessageBox::warning(this,tr("Item refersh"),iteminfo);
    }
    //someone submit an item
    else if(message.contains("SERVER SEND:AN ITEM SUBMIT\n"))
    {
        QString iteminfo = tr("The item infomation is below\n")+message.mid(message.indexOf("\n")+1,message.size()-message.indexOf("\n")-1);

        ui->messageLabel->setText("SERVER SEND:AN ITEM SUBMIT\n");
        QMessageBox::warning(this,tr("Item submit"),iteminfo);
    }
    //someitem price changed
    else if(message.contains("SERVER SEND:AN ITEM PRICE CHANGED\n"))
    {
        QString iteminfo = tr("The item infomation is below\n")+message.mid(message.indexOf("\n")+1,message.size()-message.indexOf("\n")-1);

        ui->messageLabel->setText("SERVER SEND:AN ITEM PRICE CHANGED\n");
        QMessageBox::warning(this,tr("Item price changed"),iteminfo);
    }
    else
    {
        ui->messageLabel->setText(message);
    }

    blockSize = 0;


}

void Client::displayError(QAbstractSocket::SocketError)
{
    qDebug() << tcpSocket->errorString();
    if(tcpSocket->errorString() == "Connection refused")
    {
        QMessageBox::warning(this,tr("Server error"),tr("Can not find the server"));
    }
}


void Client::on_connectButton_clicked()
{
    newConnect();
}

void Client::on_pushButton_clicked()
{

    QByteArray block = pickup_data(ui->sendLineEdit->text());
    tcpSocket->write(block);
}

void Client::ifconnected()
{
    QMessageBox::information(this,tr("Connected"),tr("Connected successed"));
    ui->connectButton->setEnabled(false);
    ui->hostLineEdit->setEnabled(false);
    ui->portLineEdit->setEnabled(false);
    ui->regist_pushButton->setEnabled(true);
    ui->sendLineEdit->setEnabled(true);
    ui->messageLabel->setText(tr("Connect success,\nthen entre your name \nand press regist to regist first"));
    return;
}

QString Client::format_message(QString header, QString data)
{

    QString message ="CLIENT UID "+uidnum+" send: "+"<uidnum>"+uidnum+"</uidnu>"+"<header>"+header+"</heade>"+"<messag>"+data+"</messa>";
    return message;
}

void Client::on_regist_pushButton_clicked()
{
    if(ui->sendLineEdit->text() == tr(""))
    {
        QMessageBox::warning(this,tr("Regist"),tr("Name can not be empty"));
        return;
    }
    else
    {
        QString message = format_message("0",ui->sendLineEdit->text());
        QByteArray block = pickup_data(message);
        tcpSocket->write(block);
    }


}


QByteArray Client::pickup_data(QString data)
{
    QByteArray block;
    QDataStream out(&block,QIODevice::WriteOnly);

    out.setVersion(QDataStream::Qt_4_0);
    out<<(quint16)0;
    out<<data;//here is the true string data
    out.device()->seek(0);
    out<<(quint16)(block.size() - sizeof(quint16));

    return block;
}


void Client::on_see_all_bid_pushButton_clicked()
{
    QString message = format_message("1",tr("I WANT TO SEE ALL BID"));
    QByteArray block = pickup_data(message);
    tcpSocket->write(block);
}

void Client::on_submit_pushButton_clicked()
{
    SubmitDialog *newsubmit = new SubmitDialog(this);
    connect(newsubmit,SIGNAL(CallMainWindowItemName(QString)),this,SLOT(submititems(QString)));
    newsubmit->show();
}

void Client::submititems(QString itemname)
{
    QString message = format_message("2",itemname);
    QByteArray block = pickup_data(message);
    tcpSocket->write(block);
    ui->messageLabel->setText(tr("SUBMIT AN ITEM\nNAME IS")+itemname);
}

void Client::on_bid_pushButton_clicked()
{
    QString message = format_message("3",tr("I WANT TO BID AN ITEM"));
    QByteArray block = pickup_data(message);
    tcpSocket->write(block);
}


void Client::getbiditem(QString itemscode, QString itemprice)
{
    //ui->messageLabel->setText(itemscode+itemprice);

    QString messagetemp = tr("<itecod>")+itemscode+tr("</iteco>")+tr("<itepri>")+itemprice+tr("</itepr>");
    QString message = format_message("31",messagetemp);
    QByteArray block = pickup_data(message);
    tcpSocket->write(block);

}

void Client::on_see_all_your_bid_pushButton_clicked()
{
    QString message = format_message("4",tr("I WANT TO SEE ALL MY BID"));
    QByteArray block = pickup_data(message);
    tcpSocket->write(block);
}


void Client::on_see_all_your_item_pushButton_clicked()
{
    QString message = format_message("5",tr("I WANT TO SEE ALL MY SALE"));
    QByteArray block = pickup_data(message);
    tcpSocket->write(block);
}


void Client::on_withdraw_pushButton_clicked()
{
    QString message = format_message("7",tr("I WANT TO WITHDRAW MY ITEM"));
    QByteArray block = pickup_data(message);
    tcpSocket->write(block);

}

void Client::withdrawiteminfo(QString itemscode)
{
    QString message = format_message("71",itemscode);
    QByteArray block = pickup_data(message);
    tcpSocket->write(block);
}

void Client::on_deregist_pushButton_clicked()
{
    QString message = format_message("6",tr("I WANT TO DEREGISTER"));
    QByteArray block = pickup_data(message);
    tcpSocket->write(block);
}

void Client::serverdisconnect()
{
   // delete tcpSocket;
    name = "";
    uidnum = "NULL";
    ui->sendLineEdit->setText("");
    ui->uidnum_label->setText("");
    ui->namelabel->setText("");
    ui->sendLineEdit->setEnabled(false);
    ui->regist_pushButton->setEnabled(false);
    ui->bid_pushButton->setEnabled(false);
    ui->see_all_bid_pushButton->setEnabled(false);
    ui->see_all_your_bid_pushButton->setEnabled(false);
    ui->submit_pushButton->setEnabled(false);
    ui->deregist_pushButton->setEnabled(false);
    ui->withdraw_pushButton->setEnabled(false);
    ui->see_all_your_item_pushButton->setEnabled(false);
    ui->connectButton->setEnabled(true);
    ui->hostLineEdit->setEnabled(true);
    ui->portLineEdit->setEnabled(true);
    ui->messageLabel->setText("SERVER DISCONNECT\n");
}
