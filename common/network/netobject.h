#ifndef NETOBJECT_H
#define NETOBJECT_H

#include <QtCore>

class NetObject
{
public:
    virtual ~NetObject() = default;

    virtual QString key() const = 0;
    virtual bool isValid() const { return false; }
    virtual QJsonObject toJson() const = 0;
    virtual void fromJson(const QJsonObject& obj) = 0;
protected:
    NetObject() = default;
};

template<class T>
void fromJson(T* t, const QJsonObject& obj)
{
    QMetaObject mo = T::staticMetaObject;
    for (int i=0; i<mo.propertyCount(); ++i)
    {
        QMetaProperty mp = mo.property(i);
        QString key = mp.name();
        mp.writeOnGadget(t, obj.value(key).toVariant());
    }
}

template<class T>
QJsonObject toJson(const T* t)
{
    QJsonObject obj;
    QMetaObject mo = T::staticMetaObject;
    for (int i=0; i<mo.propertyCount(); ++i)
    {
        QMetaProperty mp = mo.property(i);
        QString key = mp.name();
        QVariant v = mp.readOnGadget(t);
        switch (v.type()) {
        case QVariant::Bool:
            obj.insert(key, v.toBool());
            break;
        case QVariant::Int:
        case QVariant::UInt:
        case QVariant::LongLong:
        case QVariant::ULongLong:
        case QVariant::Double:
            obj.insert(key, v.toDouble());
            break;
        case QVariant::String:
            obj.insert(key, v.toString());
            break;
        case QVariant::Invalid:
        default:
            Q_ASSERT(false);
            break;
        }

    }
    return obj;
}

#endif // NETOBJECT_H
