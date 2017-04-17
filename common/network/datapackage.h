#ifndef DATAPACKAGE_H
#define DATAPACKAGE_H
#include <QtCore>

class DataPackage
{
    Q_GADGET
public:
    enum Type
    {
        Ask_Heart, //要求 心跳包
        Rep_Heart, //回复 心跳包

        Ask_Connect, // 请求注册
        Rep_Connect, // 返回注册
    };
    Q_ENUM(Type)
public:
    DataPackage();
};

#endif // DATAPACKAGE_H
