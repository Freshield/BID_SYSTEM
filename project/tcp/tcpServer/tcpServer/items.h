#ifndef ITEMS_H
#define ITEMS_H

#include <QObject>
#include <QTimer>

class items : public QObject
{
    Q_OBJECT
public:
    explicit items(QObject *parent,QString name,QString buyer,QString owner,QString price,QString itemcode,QString show);
    QString m_name;
    QString m_buyer;
    QString m_owner;
    QString m_price;
    QString m_itemcode;
    QString m_show;
    QTimer *thetimer;
    void SetTimeagain();
    void StopTime();

signals:
    void CallMainWindowTimeout(QString itemcode);

public slots:
    void TimeoutProcess();


};

#endif // ITEMS_H
