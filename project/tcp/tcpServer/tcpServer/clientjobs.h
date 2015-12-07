#ifndef CLIENTJOBS_H
#define CLIENTJOBS_H

#include <QObject>
#include <QtNetwork>
#include "clientjobs.h"

class clientjobs : public QObject
{
    Q_OBJECT
public:
    explicit clientjobs(QObject *parent, QTcpSocket *client, QString strIPPort);

    //TCP LINK
    QTcpSocket *m_ClientSock;//socket
    QString m_strIPPort;//port

    quint16 blockSize;//send block
    QString message;//got message

signals:
    void CallMainWindowDeleteClient(QString m_strIPPort);//to delete
    void CallMainWindowReadData(QString strIPPort,QString data);//to read

public slots:
    void SendBytes(QByteArray &data);//emit send slot
    void LostConnection();//emit delete slot
    void ReadBytes();//read message

};

#endif // CLIENTJOBS_H
