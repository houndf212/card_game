#include "user.h"

void User::gen_uuid()
{
    m_uuid = QUuid::createUuid();
}

QString User::key() const
{
    return "user_info";
}

bool User::isValid() const
{
    return !m_uuid.isNull() && !m_name.isEmpty();
}

void User::fromJson(const QJsonObject &obj)
{
    ::fromJson(this, obj);
}

QJsonObject User::toJson() const
{
    return ::toJson(this);
}

