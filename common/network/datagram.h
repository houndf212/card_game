#ifndef DATAGRAM_H
#define DATAGRAM_H
#include <QtCore>

class Datagram
{
public:
    Datagram();

    bool isValid() const;

    void setData(const QByteArray& data);
    QByteArray toNetworkData() const;

    void setNetworkData(const QByteArray& networkdata);
    QByteArray getData() const;
private:
    QByteArray m_data;
    quint16 m_crc;
};

#endif // DATAGRAM_H
