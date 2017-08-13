#include "mytime.h"

Time::Time()
    :m_t(QDateTime::currentDateTime())
{

}

QDateTime Time::time() const
{
    return m_t;
}

QString Time::key() const
{
    return "time";
}

bool Time::isValid() const
{
    return m_t.isValid();
}

QJsonObject Time::toJson() const
{
    QJsonObject o;
    o.insert("time", m_t.toString(Qt::ISODateWithMs));
}

void Time::fromJson(const QJsonObject &obj)
{
    QString s = obj.value("time").toString();
    m_t.fromString(s, Qt::ISODateWithMs);
}
