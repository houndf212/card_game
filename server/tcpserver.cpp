#include "tcpserver.h"

#include "socketio.h"
#include "datagram.h"

TcpServer::TcpServer()
{
    m_heart_timer = new QTimer(this);
    connect(m_heart_timer, &QTimer::timeout,
            this, &TcpServer::onHeartTime);
    m_heart_timer->start(30*1000);
}

void TcpServer::onNewSoc()
{
    while(m_server->hasPendingConnections())
    {
        QTcpSocket* sock = m_server->nextPendingConnection();
        connect(sock, &QTcpSocket::readyRead,
                this, &TcpServer::onData);
        connect(sock, &QTcpSocket::disconnected,
                this, &TcpServer::onSocClose);

        // insert into all
        m_soc_time.insert(sock, QDateTime::currentDateTime());

        ask_user(sock);
    }
}

void TcpServer::onData()
{
    QTcpSocket* sock = dynamic_cast<QTcpSocket*>(sender());
    Q_ASSERT(sock!=nullptr);

    QByteArray networkdata = sock->readAll();
    Datagram gram;
    gram.setNetworkData(networkdata);
    if (!gram.isValid())
    {
        qWarning() << "recv invalid data: " << networkdata;
        return;
    }
    QByteArray data = gram.getData();
    DataPackage pkg;
    pkg.init_from(data);
    if (!pkg.isValid())
    {
        qWarning() << "recv invalid package: "<<data;
        return;
    }
    hand_package(sock, pkg);
}

void TcpServer::onSocClose()
{

}

void TcpServer::onHeartTime()
{
    typedef QPair<QTcpSocket*, QDateTime> P;
    for (const P& p : m_soc_time)
    {

    }
}

void TcpServer::hand_package(QTcpSocket *sock, const DataPackage &pkg)
{
    Q_ASSERT(pkg.isValid());
    switch (pkg.type())
    {
    case DataPackage::Rep_Heart:
    {
        Q_ASSERT(m_soc_time.contains(sock));
        Time t;
        bool b = pkg.get_netobject(t);
        Q_ASSERT(b);
        hand_Rep_Heart(sock, t);
    }
        break;
    default:
        break;
    }
}

void TcpServer::hand_Rep_Heart(QTcpSocket *sock, const Time &t)
{
    QDateTime time = t.time();
    QDateTime cur = QDateTime::currentDateTime();
    if (qAbs(time.secsTo(cur)) > 1*60)
    {
        qDebug() << "time diff too big! "<< HostAndPort::peer(sock);
    }
    m_soc_time[sock] = QDateTime::currentDateTime();
}


void TcpServer::ask_user(QTcpSocket *sock)
{
    DataPackage d;
    d.setType(DataPackage::Ask_User);
    SocketIO::write(sock, d);
}
