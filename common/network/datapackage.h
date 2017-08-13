#ifndef DATAPACKAGE_H
#define DATAPACKAGE_H

#include "netobject.h"

class DataPackage
{
    Q_GADGET
public:
    enum Type
    {
        Invalid,
        Ask_Heart, //要求 心跳包
        Rep_Heart, //回复 心跳包

        Ask_User,
        Rep_User,

        Ask_Connect, // 请求注册
        Rep_Connect, // 返回注册
    };
    Q_ENUM(Type)
public:
    DataPackage();

    bool isValid() const { return m_type != Invalid; }

    void add_netobject(const NetObject& netobj);

    bool get_netobject(NetObject& netobj) const;

    QByteArray toByte() const;
    void init_from(const QByteArray& buffer);

    Type type() const;
    void setType(const Type &type);
private:
    Type m_type;
    QJsonObject m_data;
};
QDebug& operator<<(QDebug& s, const DataPackage& p);

#endif // DATAPACKAGE_H
