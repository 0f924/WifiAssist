#ifndef DEVICE_H
#define DEVICE_H

#include <QString>

class Device
{
public:
    Device();
    Device(QString mac,QString ip,QString hostname);

    QString ip() const;
    QString mac() const;
    QString hostname() const;
    QString limitSpeed() const;
    void setLimitSpeed(const QString &limitSpeed);
    QString logo() const;
    void setLogo(const QString &logo);

private:
    QString _ip;
    QString _mac;
    QString _hostname;
    QString _limitSpeed;
    QString _logo;

};

#endif // DEVICE_H
