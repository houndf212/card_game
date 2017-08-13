#include "hostandport.h"

bool operator ==(const HostAndPort &h1, const HostAndPort &h2)
{
    return h1.host == h2.host && h1.port == h2.port;
}

bool operator !=(const HostAndPort &h1, const HostAndPort &h2)
{
    return h1.host != h2.host || h1.port != h2.port;
}

uint qHash(const HostAndPort &h)
{
    quint64 n = h.host.toIPv4Address();
    n <<= 32;
    n += h.port;
    return qHash(n);
}

bool operator <(const HostAndPort &h1, const HostAndPort &h2)
{
    return qHash(h1) < qHash(h2);
}


HostAndPort HostAndPort::peer(const QTcpSocket *sock)
{
    HostAndPort h;
    h.host = sock->peerAddress();
    h.port = sock->peerPort();
    return h;
}

HostAndPort HostAndPort::local(const QTcpSocket *sock)
{
    HostAndPort h;
    h.host = sock->localAddress();
    h.port = sock->localPort();
    return h;
}

QDebug &operator<<(QDebug &d, const HostAndPort &h)
{
    return d<<"["<<h.host<<", "<<h.port<<"]";
}
