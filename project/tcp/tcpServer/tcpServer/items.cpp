#include "items.h"
#include <QTimer>

items::items(QObject *parent,QString name,QString buyer,QString owner,QString price,QString itemcode,QString show) :
    QObject(parent)
{
    m_name = name;
    m_buyer = buyer;
    m_owner = owner;
    m_itemcode = itemcode;
    m_price = price;
    m_show = show;

    QTimer *m_timer = new QTimer(this);
    thetimer = m_timer;
    m_timer->setSingleShot(true);

    connect(m_timer,SIGNAL(timeout()),this,SLOT(TimeoutProcess()));
    m_timer->start(300000);

}

void items::TimeoutProcess()
{

    emit CallMainWindowTimeout(m_itemcode);
}

void items::SetTimeagain()
{
    QTimer *m_timer = new QTimer(this);
    thetimer = m_timer;
    m_timer->setSingleShot(true);

    connect(m_timer,SIGNAL(timeout()),this,SLOT(TimeoutProcess()));
    m_timer->start(300000);
}

void items::StopTime()
{
    thetimer->stop();
}
