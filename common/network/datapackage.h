#ifndef DATAPACKAGE_H
#define DATAPACKAGE_H
#include <QtCore>


class DataPackage
{
    Q_GADGET
public:
    enum Type
    {
        Invalid,
        Ask_Heart, //要求 心跳包
        Rep_Heart, //回复 心跳包

        Ask_Connect, // 请求注册
        Rep_Connect, // 返回注册
    };
    Q_ENUM(Type)
public:
    DataPackage();

    bool isValid() const { return m_type != Invalid; }

    void setType(Type type) { m_type = type; }
    Type type() const { return m_type; }

    void add_data(const QString& key, const QJsonObject& obj);
    QByteArray toByte() const;
    void init_from(const QByteArray& buffer);
private:
    Type m_type;
    QJsonObject m_data;
};

#endif // DATAPACKAGE_H
