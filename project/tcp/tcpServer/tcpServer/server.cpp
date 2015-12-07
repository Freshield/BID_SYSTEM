#include "server.h"
#include "ui_server.h"
#include <QtNetwork>
#include <QMessageBox>
#include <QHostAddress>
#include <QByteArray>
#include <QDebug>
#include "clientjobs.h"
#include "items.h"
#include <QFile>


Server::Server(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Server)
{
    ui->setupUi(this);
    ui->PortLineEdit->setValidator(new QIntValidator(0, 65535, this));
    UID_NUM = 100;
    ITEM_NUM = 1000;
    //create new server

    m_server = new QTcpServer(this);
    //connect signal and slots
    connect(m_server,SIGNAL(newConnection()),this,SLOT(onNewConnection()));//new connect


}

Server::~Server()
{
    delete m_server;
    m_server = NULL;
    delete ui;
}
//send slot
void Server::on_pushButton_clicked()
{
    //find if there have client
    if(m_ClientList.count()<1)
    {
        return;
    }
    //figure out which client
    int m_Index = ui->listWidget->currentRow();
    if(m_Index<0)
    {
        return;
    }
    //process the block

    QByteArray block = pickup_data(ui->lineEdit->text());
    //send block

    m_ClientList[m_Index]->SendBytes(block);
}


//set port number slot
void Server::on_setButton_clicked()
{
    //if it is listening
    if(m_server->isListening())
    {
        return;
    }
    //if not
    int portnum = ui->PortLineEdit->text().toInt();
    bool listenreturn = m_server->listen(QHostAddress::Any, portnum);
    //find if listen is successing
    if(listenreturn)
    {
        QMessageBox::information(this,tr("Listen"),tr("Listen successed"));
        ui->setButton->setEnabled(false);
        ui->PortLineEdit->setEnabled(false);
        ui->lineEdit->setEnabled(true);
        ui->pushButton->setEnabled(true);
        ui->send_all_pushButton->setEnabled(true);

        return;
    }
    else
    {
        QMessageBox::warning(this,tr("Listen"),tr("Listen failed"));
        return;
    }

}
//new connect slot
void Server::onNewConnection()
{
    //find new connection socket
    QTcpSocket *socknewer = m_server->nextPendingConnection();
    //get IP PORT
    QString strIPandPort = socknewer->peerAddress().toString()+tr("_%1").arg(socknewer->peerPort());
    m_IPandPortList.append(strIPandPort);

    //begin constract new client
    clientjobs *newClientJobs = new clientjobs(this,socknewer,strIPandPort);
    //push in client list
    m_ClientList.append(newClientJobs);
    //begin constract uid
    UID newuid;
    newuid.number = QString::number(UID_NUM);
    UID_NUM++;
    newuid.registed = "no";
    newuid.sockets_value = socknewer;
    newuid.strIPandPort = strIPandPort;

    uidlist.append(newuid);
    //show in list
    ui->listWidget->addItem("Client:UID-"+newuid.number);
    //tell client the uid num
    QString message = "0-YOUR UID NUMBER IS:<uidnum>"+newuid.number;
    send_to_client(newuid.sockets_value,message);



    //connect delete slot
    connect(newClientJobs,SIGNAL(CallMainWindowDeleteClient(QString)),this,SLOT(DeleteOneClient(QString)));
    //connect read slot
    connect(newClientJobs,SIGNAL(CallMainWindowReadData(QString,QString)),this,SLOT(readMessage(QString,QString)));
    //output file
    QFile uidfile("uidlog.txt");
    uidfile.open(QIODevice::Text | QIODevice::WriteOnly);
    QDataStream outuid(&uidfile);
    QString uidstring = "ALL UID MEMBER IS BELOW\n";
    for(int i = 0;i<uidlist.size();i++)
    {
        uidstring = uidstring + tr("NAME:") + uidlist[i].name + tr(" NUMBER") + uidlist[i].number + tr(" REGISTED") + uidlist[i].registed + tr(" STRIPANDPORT") + uidlist[i].strIPandPort + tr("\n");
    }
    outuid << uidstring;

}

//delete slot
void Server::DeleteOneClient(QString strIPandPort)
{
    int m_Index = m_IPandPortList.indexOf(strIPandPort);
    QString clientuid = uidlist[m_Index].number;
    if(m_Index<0)
    {
        return;
    }
    //figure out this client's item

    for(int i = 0;i<itemlist.size();i++)
    {
        QString newitemtemp = tr("NAME:")+itemlist[i]->m_name+tr(" PRICE:")+itemlist[i]->m_price+tr(" BUYER:")+itemlist[i]->m_buyer+tr(" OWNER:")+itemlist[i]->m_owner+tr(" ITEMCODE:")+itemlist[i]->m_itemcode;

        //for the owner is this client
        if(itemlist[i]->m_owner == clientuid)
        {
            QString itembuyer = itemlist[i]->m_buyer;
            QByteArray block = pickup_data(tr("SERVER SEND:SORRY,ITEM ")+itemlist[i]->m_name+tr(" WAS CANCELLED CAUSE THE CLIENT SHUTDOWN\n")+newitemtemp);
            //find the buyer
            for(int j = 0;j<uidlist.size();j++)
            {
                if(uidlist[j].number == itembuyer)
                {
                    m_ClientList[j]->SendBytes(block);
                    break;
                }
            }
            //remove this item
            itemlist[i]->StopTime();
            delete itemlist[i];
            itemlist.removeAt(i);
            ui->ItemlistWidget->takeItem(i);
            continue;

        }

        //for the buyer is this client
        if(itemlist[i]->m_buyer == clientuid)
        {
            QString itemowner = itemlist[i]->m_owner;
            QByteArray block = pickup_data(tr("SERVER SEND:SORRY,ITEM ")+itemlist[i]->m_name+tr(" WAS REFRESH CAUSE THE BUYER SHUTDOWN\n")+newitemtemp);
            //find the owner
            for(int j = 0;j<uidlist.size();j++)
            {
                if(uidlist[j].number == itemowner)
                {
                    m_ClientList[j]->SendBytes(block);
                    break;
                }
            }
            //refresh the list
            itemlist[i]->StopTime();
            itemlist[i]->m_price = "0";
            itemlist[i]->m_buyer = "NULL";
            itemlist[i]->SetTimeagain();
            QString theitemtemp = tr("NAME:")+itemlist[i]->m_name+tr(" PRICE:")+itemlist[i]->m_price+tr(" BUYER:")+itemlist[i]->m_buyer+tr(" OWNER:")+itemlist[i]->m_owner+tr(" ITEMCODE:")+itemlist[i]->m_itemcode;
            ui->ItemlistWidget->item(i)->setText(theitemtemp);
        }

    }

    ui->listWidget->takeItem(m_Index);
    m_IPandPortList.removeAt(m_Index);
    delete m_ClientList[m_Index];
    m_ClientList.removeAt(m_Index);
    uidlist.removeAt(m_Index);

}

void Server::on_send_all_pushButton_clicked()
{
    //find if there have client
    if(m_ClientList.count()<1)
    {
        return;
    }

    //process the block

    QByteArray block = pickup_data(ui->lineEdit->text());
    //send block

    for(int i = 0;i<m_ClientList.size();i++)
    {
        m_ClientList[i]->SendBytes(block);

    }

}

QByteArray Server::pickup_data(QString data)
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

void Server::send_to_client(QTcpSocket *socket, QString data)
{
    QByteArray block = pickup_data(data);
    //send block

    socket->write(block);

}


//read slot
void Server::readMessage(QString strIPandPort,QString data)
{

    QString temp = tr("\n")+ui->label->text();
    QString uidtemp;
    int listnum;

    for(listnum = 0;listnum<uidlist.size();listnum++)
    {
        if(strIPandPort == uidlist[listnum].strIPandPort)
        {
            uidtemp = uidlist[listnum].number;
            break;
        }

    }
    //safe begin
    if(data[0] == 'C' && data[1] == 'L')
    {

        //--------------------------------------------------------------//
        //----------------FIGURE OUT THE MESSAGE------------------------//
        //--------------------------------------------------------------//
        //split the message
        QString message_uid;
        QString message_header;
        QString message_data;
        message_uid = data.mid(data.indexOf("<uidnum>")+8,data.indexOf("</uidnu>")-data.indexOf("<uidnum>")-8);
        message_header = data.mid(data.indexOf("<header>")+8,data.indexOf("</heade>")-data.indexOf("<header>")-8);
        message_data = data.mid(data.indexOf("<messag>")+8,data.indexOf("</messa>")-data.indexOf("<messag>")-8);
        //figure out the header
        //regist
        if(message_header == "0")
        {
            int listnum2;
            //get the list place
            for(listnum2 = 0;listnum2<uidlist.size();listnum2++)
            {
                if(message_uid == uidlist[listnum2].number)
                {
                    uidlist[listnum2].name = message_data;
                    uidlist[listnum2].registed = "yes";
                    QString listtemp = ui->listWidget->item(listnum2)->text();
                    ui->listWidget->item(listnum2)->setText(listtemp+tr(" name:")+message_data);
                    QByteArray block = pickup_data(tr("SERVER SEND:YOUR REGISTED SUCCESS"));
                    m_ClientList[listnum2]->SendBytes(block);
                    ui->label->setText(tr("UID")+message_uid+tr(" regist success\nthe name is ")+message_data+temp);
                    break;
                }

            }

        }
        //see all bid
        else if(message_header == "1")
        {
            int listnum2;
            //get the list place
            for(listnum2 = 0;listnum2<uidlist.size();listnum2++)
            {
                //find the uid
                if(message_uid == uidlist[listnum2].number)
                {
                    //figure out if it is registed
                    if(uidlist[listnum2].registed == "no")
                    {
                        QByteArray block = pickup_data(tr("SERVER SEND:YOU ARE NOT REGISTED"));
                        m_ClientList[listnum2]->SendBytes(block);
                    }
                    //registed then see items
                    else
                    {
                        //if not have items
                        if(itemlist.size() < 1)
                        {
                            QByteArray block = pickup_data(tr("SERVER SEND:THERE HAVE NO ITEMS NOW"));
                            m_ClientList[listnum2]->SendBytes(block);
                            ui->label->setText(tr("CLIENT UID")+message_uid+tr("ASK ALL BID BUT NO ITEMS")+temp);
                        }
                        //send all items information
                        else
                        {
                            QString iteminfotemp = tr("SERVER SEND:ALL BID IS BELOW\n<ITSZ>")+QString::number(itemlist.size())+tr("</ITS>");
                            for(int i = 0;i < itemlist.size();i++)
                            {
                                QString temp = iteminfotemp+tr("\n<ITN")+QString::number(i)+tr(">");
                                iteminfotemp = temp+tr("NAME:")+itemlist[i]->m_name+tr(" PRICE:")+itemlist[i]->m_price+tr(" BUYER:")+itemlist[i]->m_buyer+tr(" OWNER:")+itemlist[i]->m_owner+tr(" ITEMCODE:")+itemlist[i]->m_itemcode+tr("</IT")+QString::number(i)+tr(">");


                            }
                            QByteArray block = pickup_data(iteminfotemp);
                            m_ClientList[listnum2]->SendBytes(block);
                            ui->label->setText(tr("CLIENT UID")+message_uid+tr("ASK ALL BID")+temp);

                        }
                    }

                    break;
                }

            }

        }
        //submit an item
        else if(message_header == "2")
        {
            int listnum2;
            //get the list place
            for(listnum2 = 0;listnum2<uidlist.size();listnum2++)
            {
                //find the uid
                if(message_uid == uidlist[listnum2].number)
                {
                    //figure out if it is registed
                    if(uidlist[listnum2].registed == "no")
                    {
                        QByteArray block = pickup_data(tr("SERVER SEND:YOU ARE NOT REGISTED"));
                        m_ClientList[listnum2]->SendBytes(block);
                    }
                    //registed then see items
                    else
                    {
                    //TO DO
                    items *newitem = new items(this,message_data,tr("NULL"),message_uid,tr("0"),QString::number(ITEM_NUM),tr("NULL"));
                    ITEM_NUM++;
                    itemlist.append(newitem);
                    QString newitemtemp = tr("NAME:")+newitem->m_name+tr(" PRICE:")+newitem->m_price+tr(" BUYER:")+newitem->m_buyer+tr(" OWNER:")+newitem->m_owner+tr(" ITEMCODE:")+newitem->m_itemcode;

                    ui->ItemlistWidget->addItem(newitemtemp);
                    QByteArray block = pickup_data(tr("SERVER SEND:YOUR ITEM ")+newitem->m_name+tr("\nSUBMIT SUCCESSED"));
                    m_ClientList[listnum2]->SendBytes(block);
                    connect(newitem,SIGNAL(CallMainWindowTimeout(QString)),this,SLOT(itemtimeout(QString)));
                    for(int i = 0;i<uidlist.size();i++)
                    {
                        if(uidlist[i].registed == "yes" && uidlist[i].number != message_uid)
                        {
                            QByteArray block = pickup_data(tr("SERVER SEND:AN ITEM SUBMIT\n")+newitemtemp);
                            m_ClientList[i]->SendBytes(block);
                        }
                    }

                    }

                    break;
                }

            }

        }
        //bid an item
        else if(message_header == "3")
        {
            int listnum2;
            //get the list place
            for(listnum2 = 0;listnum2<uidlist.size();listnum2++)
            {
                //find the uid
                if(message_uid == uidlist[listnum2].number)
                {
                    //figure out if it is registed
                    if(uidlist[listnum2].registed == "no")
                    {
                        QByteArray block = pickup_data(tr("SERVER SEND:YOU ARE NOT REGISTED"));
                        m_ClientList[listnum2]->SendBytes(block);
                    }
                    //registed then see items
                    else
                    {
                    //TO DO
                        //if not have items
                        if(itemlist.size() < 1)
                        {
                            QByteArray block = pickup_data(tr("SERVER SEND:THERE HAVE NO ITEMS NOW"));
                            m_ClientList[listnum2]->SendBytes(block);
                            ui->label->setText(tr("CLIENT UID")+message_uid+tr("WANT A BID BUT NO ITEMS")+temp);
                        }
                        //send all items information
                        else
                        {
                            QString iteminfotemp = tr("SERVER SEND:ALL ITEM YOU CAN BID IS BELOW\n<ITSZ>")+QString::number(itemlist.size())+tr("</ITS>");
                            for(int i = 0;i < itemlist.size();i++)
                            {
                                QString temp = iteminfotemp+tr("\n<ITN")+QString::number(i)+tr(">");
                                iteminfotemp = temp+tr("NAME:")+itemlist[i]->m_name+tr(" PRICE:")+itemlist[i]->m_price+tr(" BUYER:")+itemlist[i]->m_buyer+tr(" OWNER:")+itemlist[i]->m_owner+tr(" ITEMCODE:")+itemlist[i]->m_itemcode+tr("</IT")+QString::number(i)+tr(">");


                            }
                            QByteArray block = pickup_data(iteminfotemp);
                            m_ClientList[listnum2]->SendBytes(block);
                            ui->label->setText(tr("CLIENT UID")+message_uid+tr("WANT A BID")+temp);

                        }



                    }

                    break;
                }

            }

        }
        //get the bid item
        else if(message_header == "31")
        {
            int listnum2;
            //get the list place
            for(listnum2 = 0;listnum2<uidlist.size();listnum2++)
            {
                //find the uid
                if(message_uid == uidlist[listnum2].number)
                {
                    //figure out if it is registed
                    if(uidlist[listnum2].registed == "no")
                    {
                        QByteArray block = pickup_data(tr("SERVER SEND:YOU ARE NOT REGISTED"));
                        m_ClientList[listnum2]->SendBytes(block);
                    }
                    //registed then see items
                    else
                    {
                    //TO DO
                        //if not have items
                        if(itemlist.size() < 1)
                        {
                            QByteArray block = pickup_data(tr("SERVER SEND:THERE HAVE NO ITEMS NOW"));
                            m_ClientList[listnum2]->SendBytes(block);
                            ui->label->setText(tr("CLIENT UID")+message_uid+tr("WANT A BID BUT NO ITEMS")+temp);
                        }
                        //send all items information
                        else
                        {
                        //TO DO
                            QString biditemcode = message_data.mid(message_data.indexOf("<itecod>")+8,message_data.indexOf("</iteco>")-message_data.indexOf("<itecod>")-8);
                            QString biditemprice = message_data.mid(message_data.indexOf("<itepri>")+8,message_data.indexOf("</itepr>")-message_data.indexOf("<itepri>")-8);
                            QString biditemowner;
                            QString itemtemp;
                            int ifgetitem = 0;
                            for(int i = 0;i < itemlist.size();i++)
                            {
                               if(itemlist[i]->m_itemcode == biditemcode)
                               {
                                   ifgetitem = 1;
                                   itemlist[i]->m_price = biditemprice;
                                   itemlist[i]->m_buyer = message_uid;
                                   biditemowner = itemlist[i]->m_owner;

                                   itemtemp = ui->ItemlistWidget->item(i)->text();
                                   QString firstpart = itemtemp.mid(0,itemtemp.indexOf(" PRICE:"));
                                   QString secondpart = itemtemp.mid(itemtemp.indexOf(" OWNER:"),itemtemp.size()-itemtemp.indexOf(" OWNER:"));
                                   itemtemp = firstpart+tr(" PRICE:")+biditemprice+tr(" BUYER:")+message_uid+secondpart;

                                   ui->ItemlistWidget->item(i)->setText(itemtemp);
                                   break;
                               }
                            }
                            //see if success get the item
                            if(ifgetitem == 0)
                            {
                                QByteArray block = pickup_data(tr("SERVER SEND:YOUR BID FAILED\nCAUSE NOT FIND THE ITEM"));
                                m_ClientList[listnum2]->SendBytes(block);
                                ui->label->setText(tr("CLIENT UID")+message_uid+tr("BID FAILED\nCAUSE NOT FIND THE ITEM")+temp);
                            }
                            else
                            {
                                QByteArray block = pickup_data(tr("SERVER SEND:YOUR BID SUCCESS"));
                                m_ClientList[listnum2]->SendBytes(block);
                                //find the owner
                                int listowner;
                                for(int i = 0;i < uidlist.size();i++)
                                {
                                    if(uidlist[i].number == biditemowner)
                                    {
                                        listowner = i;
                                        break;
                                    }
                                }
                                block = pickup_data(tr("SERVER SEND:YOUR ITEM HAVE BID\n")+itemtemp);
                                m_ClientList[listowner]->SendBytes(block);
                                for(int i = 0;i<uidlist.size();i++)
                                {
                                    if(uidlist[i].registed == "yes" && uidlist[i].number != message_uid && uidlist[i].number != biditemowner)
                                    {
                                        QByteArray block = pickup_data(tr("SERVER SEND:AN ITEM PRICE CHANGED\n")+itemtemp);
                                        m_ClientList[i]->SendBytes(block);
                                    }
                                }
                                ui->label->setText(tr("CLIENT UID")+message_uid+tr("BID SUCCESS")+temp);
                            }
                        }
                    }
                    break;
                }
            }
        }
        //see all the client's bid
        else if(message_header == "4")
        {
            int listnum2;
            //get the list place
            for(listnum2 = 0;listnum2<uidlist.size();listnum2++)
            {
                //find the uid
                if(message_uid == uidlist[listnum2].number)
                {
                    //figure out if it is registed
                    if(uidlist[listnum2].registed == "no")
                    {
                        QByteArray block = pickup_data(tr("SERVER SEND:YOU ARE NOT REGISTED"));
                        m_ClientList[listnum2]->SendBytes(block);
                    }
                    //registed then see items
                    else
                    {
                    //TO DO
                        //if not have items
                        if(itemlist.size() < 1)
                        {
                            QByteArray block = pickup_data(tr("SERVER SEND:THERE HAVE NO ITEMS NOW"));
                            m_ClientList[listnum2]->SendBytes(block);
                            ui->label->setText(tr("CLIENT UID")+message_uid+tr("WANT A BID BUT NO ITEMS")+temp);
                        }
                        //send all items information
                        else
                        {
                            //figure out if there have client's bid
                            int ifhaveclientbid = 0;
                            QString iteminfotemp = tr("SERVER SEND:ALL ITEM YOUR BID IS BELOW\n");

                            for(int i = 0;i < itemlist.size();i++)
                            {
                                if(itemlist[i]->m_buyer == message_uid)
                                {
                                    QString tempITEM = iteminfotemp+tr("\n<ITN")+QString::number(ifhaveclientbid)+tr(">");
                                    iteminfotemp = tempITEM+tr("NAME:")+itemlist[i]->m_name+tr(" PRICE:")+itemlist[i]->m_price+tr(" BUYER:")+itemlist[i]->m_buyer+tr(" OWNER:")+itemlist[i]->m_owner+tr(" ITEMCODE:")+itemlist[i]->m_itemcode+tr("</IT")+QString::number(ifhaveclientbid)+tr(">");

                                    ifhaveclientbid ++;
                                }

                            }
                            //see if have client bid
                            if(ifhaveclientbid == 0)
                            {
                                QByteArray block = pickup_data(tr("SERVER SEND:THERE HAVE NO YOUR BID NOW"));
                                m_ClientList[listnum2]->SendBytes(block);
                                ui->label->setText(tr("CLIENT UID")+message_uid+tr("WANT SEE ITS BID BUT DO NOT HAVE")+temp);
                            }
                            //if have
                            else
                            {
                                iteminfotemp = iteminfotemp + tr("<ITSZ>")+QString::number(ifhaveclientbid)+tr("</ITS>");
                                QByteArray block = pickup_data(iteminfotemp);
                                m_ClientList[listnum2]->SendBytes(block);
                                ui->label->setText(tr("CLIENT UID")+message_uid+tr("ASK ALL ITS BID")+temp);
                            }


                        }



                    }

                    break;
                }

            }

        }
        //see all the client's item
        else if(message_header == "5")
        {
            int listnum2;
            //get the list place
            for(listnum2 = 0;listnum2<uidlist.size();listnum2++)
            {
                //find the uid
                if(message_uid == uidlist[listnum2].number)
                {
                    //figure out if it is registed
                    if(uidlist[listnum2].registed == "no")
                    {
                        QByteArray block = pickup_data(tr("SERVER SEND:YOU ARE NOT REGISTED"));
                        m_ClientList[listnum2]->SendBytes(block);
                    }
                    //registed then see items
                    else
                    {
                    //TO DO
                        //if not have items
                        if(itemlist.size() < 1)
                        {
                            QByteArray block = pickup_data(tr("SERVER SEND:THERE HAVE NO ITEMS NOW"));
                            m_ClientList[listnum2]->SendBytes(block);
                            ui->label->setText(tr("CLIENT UID")+message_uid+tr("WANT SEE ITEM BELONG TO ITSELF BUT NO ITEMS")+temp);
                        }
                        //send all items information
                        else
                        {
                            //figure out if there have client's item
                            int ifhaveclientbid = 0;
                            QString iteminfotemp = tr("SERVER SEND:ALL ITEM BELONG TO YOU IS BELOW\n");

                            for(int i = 0;i < itemlist.size();i++)
                            {
                                if(itemlist[i]->m_owner == message_uid)
                                {
                                    QString tempITEM = iteminfotemp+tr("\n<ITN")+QString::number(ifhaveclientbid)+tr(">");
                                    iteminfotemp = tempITEM+tr("NAME:")+itemlist[i]->m_name+tr(" PRICE:")+itemlist[i]->m_price+tr(" BUYER:")+itemlist[i]->m_buyer+tr(" OWNER:")+itemlist[i]->m_owner+tr(" ITEMCODE:")+itemlist[i]->m_itemcode+tr("</IT")+QString::number(ifhaveclientbid)+tr(">");

                                    ifhaveclientbid ++;
                                }

                            }
                            //see if have client bid
                            if(ifhaveclientbid == 0)
                            {
                                QByteArray block = pickup_data(tr("SERVER SEND:THERE HAVE NO YOUR ITEM NOW"));
                                m_ClientList[listnum2]->SendBytes(block);
                                ui->label->setText(tr("CLIENT UID")+message_uid+tr("WANT SEE ITS ITEM BUT DO NOT HAVE")+temp);
                            }
                            //if have
                            else
                            {
                                iteminfotemp = iteminfotemp + tr("<ITSZ>")+QString::number(ifhaveclientbid)+tr("</ITS>");
                                QByteArray block = pickup_data(iteminfotemp);
                                m_ClientList[listnum2]->SendBytes(block);
                                ui->label->setText(tr("CLIENT UID")+message_uid+tr("ASK ALL ITS ITEM")+temp);
                            }


                        }



                    }

                    break;
                }

            }

        }
        //withdraw an item
        else if(message_header == "7")
        {
            int listnum2;
            //get the list place
            for(listnum2 = 0;listnum2<uidlist.size();listnum2++)
            {
                //find the uid
                if(message_uid == uidlist[listnum2].number)
                {
                    //figure out if it is registed
                    if(uidlist[listnum2].registed == "no")
                    {
                        QByteArray block = pickup_data(tr("SERVER SEND:YOU ARE NOT REGISTED"));
                        m_ClientList[listnum2]->SendBytes(block);
                    }
                    //registed then see items
                    else
                    {
                    //TO DO
                        //if not have items
                        if(itemlist.size() < 1)
                        {
                            QByteArray block = pickup_data(tr("SERVER SEND:THERE HAVE NO ITEMS NOW"));
                            m_ClientList[listnum2]->SendBytes(block);
                            ui->label->setText(tr("CLIENT UID")+message_uid+tr("WANT WITHDRAW AN ITEM BUT NO ITEMS")+temp);
                        }
                        //send all items information
                        else
                        {
                            //figure out if there have client's item
                            int ifhaveclientbid = 0;
                            QString iteminfotemp = tr("SERVER SEND:ALL YOUR ITEM IS BELOW\n");

                            for(int i = 0;i < itemlist.size();i++)
                            {
                                if(itemlist[i]->m_owner == message_uid)
                                {
                                    QString tempITEM = iteminfotemp+tr("\n<ITN")+QString::number(ifhaveclientbid)+tr(">");
                                    iteminfotemp = tempITEM+tr("NAME:")+itemlist[i]->m_name+tr(" PRICE:")+itemlist[i]->m_price+tr(" BUYER:")+itemlist[i]->m_buyer+tr(" OWNER:")+itemlist[i]->m_owner+tr(" ITEMCODE:")+itemlist[i]->m_itemcode+tr("</IT")+QString::number(ifhaveclientbid)+tr(">");

                                    ifhaveclientbid ++;
                                }

                            }
                            //see if have client bid
                            if(ifhaveclientbid == 0)
                            {
                                QByteArray block = pickup_data(tr("SERVER SEND:THERE HAVE NO YOUR ITEM NOW"));
                                m_ClientList[listnum2]->SendBytes(block);
                                ui->label->setText(tr("CLIENT UID")+message_uid+tr("WANT WITHDRAW ITS ITEM BUT DO NOT HAVE")+temp);
                            }
                            //if have
                            else
                            {
                                iteminfotemp = iteminfotemp + tr("<ITSZ>")+QString::number(ifhaveclientbid)+tr("</ITS>");
                                QByteArray block = pickup_data(iteminfotemp);
                                m_ClientList[listnum2]->SendBytes(block);
                                ui->label->setText(tr("CLIENT UID")+message_uid+tr("ASK ALL ITS ITEM")+temp);
                            }


                        }



                    }

                    break;
                }

            }

        }
        //get the withdraw item
        else if(message_header == "71")
        {
            int listnum2;
            //get the list place
            for(listnum2 = 0;listnum2<uidlist.size();listnum2++)
            {
                //find the uid
                if(message_uid == uidlist[listnum2].number)
                {
                    //figure out if it is registed
                    if(uidlist[listnum2].registed == "no")
                    {
                        QByteArray block = pickup_data(tr("SERVER SEND:YOU ARE NOT REGISTED"));
                        m_ClientList[listnum2]->SendBytes(block);
                    }
                    //registed then see items
                    else
                    {
                    //TO DO
                        //if not have items
                        if(itemlist.size() < 1)
                        {
                            QByteArray block = pickup_data(tr("SERVER SEND:THERE HAVE NO ITEMS NOW"));
                            m_ClientList[listnum2]->SendBytes(block);
                            ui->label->setText(tr("CLIENT UID")+message_uid+tr("WANT WITHDRAW BUT NO ITEMS")+temp);
                        }
                        //send all items information
                        else
                        {
                        //TO DO
                            QString biditemcode = message_data;
                            int ifgetitem = 0;
                            for(int i = 0;i < itemlist.size();i++)
                            {
                               if(itemlist[i]->m_itemcode == biditemcode)
                               {
                                   ifgetitem = 1;

                                   ui->ItemlistWidget->takeItem(i);
                                   itemlist[i]->StopTime();
                                   delete itemlist[i];
                                   itemlist.removeAt(i);


                                   break;
                               }
                            }
                            //see if success get the item
                            if(ifgetitem == 0)
                            {
                                QByteArray block = pickup_data(tr("SERVER SEND:YOUR WITHDRAW FAILED\nCAUSE NOT FIND THE ITEM"));
                                m_ClientList[listnum2]->SendBytes(block);
                                ui->label->setText(tr("CLIENT UID")+message_uid+tr("WITHDRAW FAILED\nCAUSE NOT FIND THE ITEM")+temp);
                            }
                            else
                            {
                                QByteArray block = pickup_data(tr("SERVER SEND:YOUR WITHDRAW SUCCESS"));
                                m_ClientList[listnum2]->SendBytes(block);
                                ui->label->setText(tr("CLIENT UID")+message_uid+tr("WITHDRAW SUCCESS")+temp);
                            }
                        }
                    }
                    break;
                }
            }
        }
        //client want to deregist
        else if(message_header == "6")
        {
            int listnum2;
            //get the list place
            for(listnum2 = 0;listnum2<uidlist.size();listnum2++)
            {
                //find the uid
                if(message_uid == uidlist[listnum2].number)
                {
                    //figure out if it is registed
                    if(uidlist[listnum2].registed == "no")
                    {
                        QByteArray block = pickup_data(tr("SERVER SEND:YOU ARE NOT REGISTED"));
                        m_ClientList[listnum2]->SendBytes(block);
                        break;
                    }
                    //registed then see items
                    else
                    {
                    //TO DO
                        //if not have items
                        if(itemlist.size() < 1)
                        {

                            QByteArray block = pickup_data(tr("SERVER SEND:YOUR DEREGIST SUCCESS\n"));
                            m_ClientList[listnum2]->SendBytes(block);

                            delete m_ClientList[listnum2];
                            m_ClientList.removeAt(listnum2);
                            uidlist.removeAt(listnum2);
                            ui->listWidget->takeItem(listnum2);
                            m_IPandPortList.removeAt(listnum2);
                            ui->label->setText(tr("CLIENT UID")+message_uid+tr("DEREGIST SUCCESS")+temp);
                            break;

                        }
                        //figure out the item
                        else
                        {
                            //figure out if there have client's item
                            int ifhaveclientbid = 0;
                            for(int i = 0;i < itemlist.size();i++)
                            {
                                if(itemlist[i]->m_owner == message_uid)
                                {

                                    ifhaveclientbid ++;
                                }
                                if(itemlist[i]->m_buyer == message_uid)
                                {
                                    ifhaveclientbid ++;

                                }

                            }
                            //see if client have bid or item
                            if(ifhaveclientbid == 0)
                            {
                                QByteArray block = pickup_data(tr("SERVER SEND:YOUR DEREGIST SUCCESS\n"));

                                m_ClientList[listnum2]->SendBytes(block);
                                delete m_ClientList[listnum2];
                                m_ClientList.removeAt(listnum2);
                                uidlist.removeAt(listnum2);
                                ui->listWidget->takeItem(listnum2);
                                m_IPandPortList.removeAt(listnum2);
                                ui->label->setText(tr("CLIENT UID")+message_uid+tr("DEREGIST SUCCESS")+temp);
                            }
                            //if have
                            else
                            {

                                QByteArray block = pickup_data(tr("SERVER SEND:YOU DEREGIST FAILED\nCAUSE YOU HAVE BID OR ITEM NOW\n"));
                                m_ClientList[listnum2]->SendBytes(block);
                                ui->label->setText(tr("CLIENT UID")+message_uid+tr("DEREGIST FAILED\nCAUSE YOU HAVE BID OR ITEM NOW\n")+temp);
                            }


                        }



                    }

                    break;
                }

            }

        }
        else
        {
            ui->label->setText(data+temp);

        }


    }
    else
    {

        ui->label->setText(data+temp);

    }
    //output file
    QFile uidfile("uidlog.txt");
    QFile itemfile("itemlog.txt");
    uidfile.open(QIODevice::Text | QIODevice::WriteOnly);
    itemfile.open(QIODevice::Text | QIODevice::WriteOnly);
    QDataStream outuid(&uidfile);
    QDataStream outitem(&itemfile);
    QString uidstring = "ALL UID MEMBER IS BELOW\n";
    QString itemstring= "ALL ITEM MEMBER IS BELOW\n";
    for(int i = 0;i<uidlist.size();i++)
    {
        uidstring = uidstring + tr("NAME:") + uidlist[i].name + tr(" NUMBER") + uidlist[i].number + tr(" REGISTED") + uidlist[i].registed + tr(" STRIPANDPORT") + uidlist[i].strIPandPort + tr("\n");
    }
    for(int i = 0;i<itemlist.size();i++)
    {
        itemstring = itemstring + tr("NAME:")+itemlist[i]->m_name+tr(" PRICE:")+itemlist[i]->m_price+tr(" BUYER:")+itemlist[i]->m_buyer+tr(" OWNER:")+itemlist[i]->m_owner+tr(" ITEMCODE:")+itemlist[i]->m_itemcode + tr("\n");

    }
    outuid << uidstring;
    outitem << itemstring;



}

void Server::itemtimeout(QString itemcode)
{
    //find the item listnum
    int itemlistnum;
    QString itemowner;
    QString itembuyer;
    QString temp = tr("\n")+ui->label->text();
    for(itemlistnum = 0;itemlistnum < itemlist.size();itemlistnum++)
    {
        if(itemlist[itemlistnum]->m_itemcode == itemcode)
        {
            itemowner = itemlist[itemlistnum]->m_owner;
            itembuyer = itemlist[itemlistnum]->m_buyer;
            break;
        }
    }
    //figure out if there have a buyer
    //if not
    if(itemlist[itemlistnum]->m_buyer == "NULL")
    {

        itemlist[itemlistnum]->SetTimeagain();
        //find the owner
        for(int i = 0;i<uidlist.size();i++)
        {
            if(uidlist[i].number == itemowner)
            {
                QByteArray block = pickup_data(tr("SERVER SEND:YOU ITEM ")+itemlist[itemlistnum]->m_name+tr(" TIMEOUT\nBUT DO NOT HAVE BUYER\nTIME REFRESH AGAIN"));
                m_ClientList[i]->SendBytes(block);
            }
        }
        ui->label->setText(tr("Item ")+itemcode+tr(" timeout and refresh again")+temp);

    }
    else
    {
        QString newitemtemp = tr("NAME:")+itemlist[itemlistnum]->m_name+tr(" PRICE:")+itemlist[itemlistnum]->m_price+tr(" BUYER:")+itemlist[itemlistnum]->m_buyer+tr(" OWNER:")+itemlist[itemlistnum]->m_owner+tr(" ITEMCODE:")+itemlist[itemlistnum]->m_itemcode;

        //find the owner
        for(int i = 0;i<uidlist.size();i++)
        {
            if(uidlist[i].number == itemowner)
            {
                QByteArray block = pickup_data(tr("SERVER SEND:YOU ITEM ")+itemlist[itemlistnum]->m_name+tr(" TRADE SUCCESS\n")+newitemtemp);
                m_ClientList[i]->SendBytes(block);
            }
            if(uidlist[i].number == itembuyer)
            {
                QByteArray block = pickup_data(tr("SERVER SEND:YOU ITEM ")+itemlist[itemlistnum]->m_name+tr(" BID SUCCESS\n")+newitemtemp);
                m_ClientList[i]->SendBytes(block);
            }
        }

        ui->ItemlistWidget->takeItem(itemlistnum);
        itemlist[itemlistnum]->StopTime();
        delete itemlist[itemlistnum];
        itemlist.removeAt(itemlistnum);
        ui->label->setText(tr("Item ")+itemcode+tr(" trade finished")+temp);
    }
}

/*
void Server::on_TestpushButton_clicked()
{
    items *newitem = new items(this,"NULL","NULL","NULL","NULL","NULL","NULL");
    testitem = newitem;
    connect(newitem,SIGNAL(CallMainWindowTimeout(QString)),this,SLOT(OneItemTimeout(QString)));

}

void Server::OneItemTimeout(QString itemcode)
{
    QMessageBox::information(this,tr("ItemTimeout"),tr("ItemCode")+itemcode+tr("Timeout"));
}

void Server::on_TestpushButton_2_clicked()
{
    testitem->SetTimeagain();
}
*/
/*
void Server::on_testpushButton_clicked()
{
    TestDialog *testdialog = new TestDialog(this);
    testdialog->show();
}
*/
