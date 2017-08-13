#ifndef MYTIME_H
#define MYTIME_H
#include "netobject.h"

class Time : public NetObject
{
public:
    Time();
    QDateTime time() const;
    // NetObject interface
public:
    virtual QString key() const override;
    virtual bool isValid() const override;
    virtual QJsonObject toJson() const override;
    virtual void fromJson(const QJsonObject &obj) override;
private:
    QDateTime m_t;
};

#endif // MYTIME_H
