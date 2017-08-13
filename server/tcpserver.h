#ifndef TCPSERVER_H
#define TCPSERVER_H
#include <QtCore>
#include <QTcpServer>
#include <QTcpSocket>
#include "datapackage.h"
#include "hostandport.h"
#include "mytime.h"

class TcpServer : public QObject
{
    Q_OBJECT
public:
    TcpServer();
private:
    Q_SLOT void onNewSoc();
    Q_SLOT void onData();
    Q_SLOT void onSocClose();
    Q_SLOT void onHeartTime();

    void ask_user(QTcpSocket* sock);
    void hand_package(QTcpSocket* sock, const DataPackage& pkg);
    void hand_Rep_Heart(QTcpSocket* sock, const Time& t);
private:
    QTimer* m_heart_timer;
    QTcpServer* m_server;
    QMap<QTcpSocket*, QDateTime> m_soc_time;

};

#endif // TCPSERVER_H
