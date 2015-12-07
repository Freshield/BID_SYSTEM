#include "withdrawitemdialog.h"
#include "ui_withdrawitemdialog.h"
#include <QDebug>
#include <QMessageBox>

WithdrawItemDialog::WithdrawItemDialog(QWidget *parent,QString data,QString parentuid) :
    QDialog(parent),
    ui(new Ui::WithdrawItemDialog)
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


WithdrawItemDialog::~WithdrawItemDialog()
{
    delete ui;
}

void WithdrawItemDialog::on_listWidget_itemDoubleClicked(QListWidgetItem* item)
{
    QString itemtemp = item->text();
    QString theitembuyer = itemtemp.mid(itemtemp.indexOf(tr("BUYER:"))+6,itemtemp.indexOf(" OWNER:")-itemtemp.indexOf(tr("BUYER:"))-6);
    QString theitemcode = itemtemp.mid(itemtemp.indexOf(tr("ITEMCODE:"))+9,itemtemp.indexOf(";")-itemtemp.indexOf(tr("ITEMCODE:"))-9);
    m_itemscode = theitemcode;
    //figure out if the owner is the same

    if(theitembuyer != "NULL")
    {
        QMessageBox::warning(this,tr("Buyer"),tr("You can not withdraw an item having buyer"));
        return;
    }
    emit biditemsinfo(theitemcode);
    close();
}
