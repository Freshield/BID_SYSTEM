#include "biditemdialog.h"
#include "ui_biditemdialog.h"

#include "bidpricedialog.h"
#include <QDebug>
#include <QMessageBox>

BidItemDialog::BidItemDialog(QWidget *parent,QString data,QString parentuid) :
    QDialog(parent),
    ui(new Ui::BidItemDialog)
{
    ui->setupUi(this);
    biditeminfo = data;
    m_parentuid = parentuid;
        int count = data.mid(data.indexOf("<ITSZ>")+6,data.indexOf("</ITS>")-data.indexOf("<ITSZ>")-6).toInt();
        for(int i = 0;i<count;i++)
        {
            QString tempbegin = tr("<ITN")+QString::number(i)+tr(">");
            QString tempend = tr("</IT")+QString::number(i)+tr(">");
            QString tempinfo;
            if(i<=9)
            {
            tempinfo = data.mid(data.indexOf(tempbegin)+6,data.indexOf(tempend)-data.indexOf(tempbegin)-6)+";";
            }
            else
            {
                tempinfo = data.mid(data.indexOf(tempbegin)+7,data.indexOf(tempend)-data.indexOf(tempbegin)-7)+";";
            }

            ui->listWidget->addItem(tempinfo);

        }

        connect(this,SIGNAL(itemDoubleClicked(QListWidgetItem*)),this,SLOT(on_listWidget_itemDoubleClicked(QListWidgetItem*)),Qt::QueuedConnection);
}

BidItemDialog::~BidItemDialog()
{
    delete ui;
}


void BidItemDialog::itempricegot(QString price)
{
    if(price.toInt() <= m_itemprice.toInt())
    {
        QMessageBox::warning(this,tr("Price"),tr("Your price is equal or lower than the item's price"));
    }
    else
    {
        emit biditemsinfo(m_itemscode,price);
        close();

    }

}


void BidItemDialog::on_listWidget_itemDoubleClicked(QListWidgetItem* item)
{
    QString itemtemp = item->text();
    QString theitemowner = itemtemp.mid(itemtemp.indexOf(tr("OWNER:"))+6,itemtemp.indexOf(" ITEMCODE:")-itemtemp.indexOf(tr("OWNER:"))-6);
    m_itemprice = itemtemp.mid(itemtemp.indexOf(tr("PRICE:"))+6,itemtemp.indexOf(tr(" BUYER:"))-itemtemp.indexOf(tr("PRICE:"))-6);
    QString theitemcode = itemtemp.mid(itemtemp.indexOf(tr("ITEMCODE:"))+9,itemtemp.indexOf(";")-itemtemp.indexOf(tr("ITEMCODE:"))-9);
    m_itemscode = theitemcode;
    //figure out if the owner is the same

    if(theitemowner == m_parentuid)
    {
        QMessageBox::warning(this,tr("Owner"),tr("You can not bid item belong yourself"));
        return;
    }

    BidPriceDialog *newbidprice = new BidPriceDialog(this,m_parentuid);
    connect(newbidprice,SIGNAL(itempriceget(QString)),this,SLOT(itempricegot(QString)),Qt::QueuedConnection);
    newbidprice->show();
}
