#ifndef WDEVICES_H
#define WDEVICES_H
#include <QStringList>
#include <QProcess>
#include <QMessageBox>

class WDevices
{
public:
    WDevices();
    WDevices(QString ip,QString mac,QString hostname);
    QString ip() const;

    QString mac() const;

    QString hostname() const;

private:
    QString _ip;
    QString _mac;
    QString _hostname;

};

#endif // WDEVICES_H
