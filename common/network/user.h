#ifndef USER_H
#define USER_H
#include "netobject.h"

class User : public NetObject
{
    Q_GADGET
public:
    void gen_uuid();
    Q_PROPERTY(QString name READ name WRITE setNamed)
    Q_PROPERTY(QUuid uuid READ uuid)

    virtual QString key() const override;
    virtual bool isValid() const override;
    virtual QJsonObject toJson() const override;
    virtual void fromJson(const QJsonObject &obj) override;

    QString name() const
    {
        return m_name;
    }

    QUuid uuid() const
    {
        return m_uuid;
    }

public:
    void setNamed(const QString& name)
    {
        m_name = name;
    }

private:
    QString m_name;
    QUuid m_uuid;
};

#endif // USER_H
