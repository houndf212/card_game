#include "socketio.h"
#include "datagram.h"

void SocketIO::write(QTcpSocket *soc, const DataPackage &pkg)
{
    QByteArray buffer = pkg.toByte();
    Datagram dat;
    dat.setData(buffer);
    QByteArray netdata = dat.toNetworkData();
    soc->write(netdata);
}

DataPackage SocketIO::read(QTcpSocket *soc)
{
    Datagram dat;
    dat.setNetworkData(soc->readAll());
    DataPackage pkg;
    if (dat.isValid())
    {
        QByteArray buffer = dat.getData();
        pkg.init_from(buffer);
    }
    return pkg;
}
