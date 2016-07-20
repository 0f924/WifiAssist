#include "wdevices.h"
#include <QString>
#include <QStringList>
#include <QProcess>
WDevices::WDevices()
{

}

WDevices::WDevices(QString ip, QString mac,QString hostname)
{
    this->_hostname = hostname;
    this->_ip = ip;
    this->_mac = mac;
}

QString WDevices::ip() const
{
    return _ip;
}

QString WDevices::mac() const
{
    return _mac;
}

QString WDevices::hostname() const
{
    return _hostname;
}

