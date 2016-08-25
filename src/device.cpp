#include "device.h"

Device::Device()
{

}

Device::Device(QString mac,QString ip,QString hostname)
{
    _mac = mac;
    _ip = ip;
    _hostname = hostname;
}

QString Device::ip() const
{
    return _ip;
}

QString Device::mac() const
{
    return _mac;
}

QString Device::hostname() const
{
    return _hostname;
}

QString Device::limitSpeed() const
{
    return _limitSpeed;
}

void Device::setLimitSpeed(const QString &limitSpeed)
{
    _limitSpeed = limitSpeed;
}

QString Device::logo() const
{
    return _logo;
}

void Device::setLogo(const QString &logo)
{
    _logo = logo;
}

