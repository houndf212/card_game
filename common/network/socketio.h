#ifndef SOCKETIO_H
#define SOCKETIO_H
#include <QtCore>
#include <QTcpSocket>
#include "datapackage.h"

namespace SocketIO
{
    void write(QTcpSocket* soc, const DataPackage& pkg);
    DataPackage read(QTcpSocket* soc);
}

#endif // SOCKETIO_H
