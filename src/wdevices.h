#ifndef WDEVICES_H
#define WDEVICES_H
#include <QStringList>
#include <QProcess>
#include <QMessageBox>
#include <QVector>
#include <QStringList>

#include "device.h"

class WDevices
{
public:
    WDevices();
    QVector<Device *> getDeviceList();

private:
    QStringList getDeviceListStr();
};

#endif // WDEVICES_H
