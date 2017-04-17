#ifndef HOSTANDPORT_H
#define HOSTANDPORT_H
#include <QtCore>
#include <QHostAddress>

class HostAndPort
{
public:
    QHostAddress host;
    quint16 port;

    HostAndPort();
};

bool operator ==(const HostAndPort& h1, const HostAndPort& h2);
bool operator !=(const HostAndPort& h1, const HostAndPort& h2);
uint qHash(const HostAndPort& h);
bool operator < (const HostAndPort& h1, const HostAndPort& h2);

namespace std{
template<>
struct hash<HostAndPort>
{
    size_t operator()(const HostAndPort& h) const
    {
        return qHash(h);
    }
};
}

#endif // HOSTANDPORT_H
