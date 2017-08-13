#include "datapackage.h"

DataPackage::DataPackage()
    :m_type(Invalid)
{

}

void DataPackage::add_netobject(const NetObject &netobj)
{
    m_data.insert(netobj.key(), netobj.toJson());
}

bool DataPackage::get_netobject(NetObject &netobj) const
{
    if (m_data.contains(netobj.key()))
    {
        QJsonObject obj = m_data.value(netobj.key()).toObject();
        netobj.fromJson(obj);
        return true;
    }
    else
        return false;
}

// e.g {"type_id":1, "type":"ask_heart",data:{..}}
QByteArray DataPackage::toByte() const
{
    QJsonObject all;
    all.insert("type_id", int(m_type));
    QMetaEnum en = QMetaEnum::fromType<Type>();
    QString type = en.valueToKey(int(m_type));
    all.insert("type", type);
    all.insert("data", m_data);
    QJsonDocument doc;
    doc.setObject(all);
    return doc.toJson();
}

void DataPackage::init_from(const QByteArray &buffer)
{
    QJsonParseError err;
    QJsonDocument doc = QJsonDocument::fromJson(buffer, &err);
    if (err.error!=QJsonParseError::NoError)
    {
        m_type = Invalid;
        return;
    }
    QJsonObject all = doc.object();
    Q_ASSERT(!all.isEmpty());
    m_type = Type(all.value("type_id").toInt());
    m_data = all.value("data").toObject();
#ifdef QT_DEBUG
    QMetaEnum en = QMetaEnum::fromType<Type>();
    QString type = all.value("type").toString();
    Q_ASSERT(type == en.valueToKey(m_type));
#endif
}

DataPackage::Type DataPackage::type() const
{
    return m_type;
}

void DataPackage::setType(const Type &type)
{
    m_type = type;
}

QDebug& operator<<(QDebug& s, const DataPackage& p)
{
    return s<<p.toByte();
}
