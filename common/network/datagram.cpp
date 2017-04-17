#include "datagram.h"

Datagram::Datagram()
    :m_crc(0)
{

}

bool Datagram::isValid() const
{
    return m_crc == qChecksum(m_data.data(), m_data.size());
}

QByteArray Datagram::getData() const
{
    return m_data;
}

void Datagram::setData(const QByteArray &data)
{
    m_data = data;
    m_crc = qChecksum(data.data(), data.size());
}

void Datagram::setNetworkData(const QByteArray &networkdata)
{
    int size = networkdata.size();
    if (size<=2)
    {
        qWarning() << "recv len networkdata : " << size;
    }
    else
    {
        QByteArray crc = networkdata.right(2);
        m_data = networkdata.left(size - 2);
        m_crc = qFromBigEndian<quint16>(crc.data());
    }
}

QByteArray Datagram::toNetworkData() const
{
    QByteArray crc(2, 0);
    qToBigEndian(m_crc, crc.data());
    return m_data + crc;
}
